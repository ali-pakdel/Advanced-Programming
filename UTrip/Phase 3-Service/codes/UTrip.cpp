#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <random>

#include "UTrip.hpp"
#include "CityFilter.hpp"
#include "RoomFilter.hpp"
#include "AvgPriceFilter.hpp"
#include "StarPeriodFilter.hpp"
#include "DefaultPriceFilter.hpp"

#include "BadRequest.hpp"
#include "NotFound.hpp"
#include "PermissionDenied.hpp"
#include "NotEnoughRoom.hpp"
#include "../server/server.hpp"

using namespace std;

const vector<string> signup_lables{EMAIL, USERNAME, PASSWORD};
const vector<string> login_lables{EMAIL, PASSWORD};
const vector<string> id_lables{ID_};
const vector<string> increase_wallet_lables{AMOUNT};
const vector<string> transaction_lables{COUNT};
const vector<string> reserve_lables{HOTEL, TYPE, QUANTITY, CHECK_IN, CHECK_OUT};
const vector<string> comment_lables{HOTEL, COMMENT};
const vector<string> show_comment_lables{HOTEL};
const vector<string> rating_lables{HOTEL, LOCATION, CLEANLINESS, STAFF, FACILITIES,
        VALUE_FOR_MONEY, OVERALL_RATING};
const vector<string> show_rating_lables{HOTEL};
const vector<string> room_filter_lables{TYPE, QUANTITY, CHECK_IN, CHECK_OUT};
const vector<string> star_filter_lables{MIN_STAR, MAX_STAR};
const vector<string> price_filter_lables{MIN_PRICE, MAX_PRICE};
const vector<string> sort_lables{PROPERTY, ORDER};
const vector<string> active_weights_lables{ACTIVE};
const vector<string> weights_lables{LOCATION, CLEANLINESS, STAFF, 
        FACILITIES, VALUE_FOR_MONEY};

UTrip::UTrip(string hotels_path)
{
    read_infos(hotels_path);
}
void UTrip::read_infos(string hotels_path)
{
    read_hotels_info(hotels_path);
}

void UTrip::read_hotels_info(string file_path)
{
    ifstream input_file(file_path);
    vector<string> separated_infos;
    RoomsInfo rooms_info;
    string line;
    getline(input_file, line);
    for (int i = 0; getline(input_file, line); i++)
    {
        separated_infos = separate_line(line);
        rooms_info = separate_rooms_info(separated_infos);
        Hotel* hotel = new Hotel(separated_infos[UNIQUE_ID], separated_infos[PROPERTY_NAME],
                stoi(separated_infos[STAR_RATING]), separated_infos[OVERVIEW], 
                separated_infos[AMENITIES], separated_infos[CITY], separated_infos[LATITUDE],
                separated_infos[LONGITUDE], separated_infos[IMAGE_URL], rooms_info);
        hotels_info.push_back(hotel);
    }

	sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
        { return a->get_id() < b->get_id(); });
}
vector<string> UTrip::separate_line(string line)
{
    string word;
    stringstream temp(line);
    vector<string> separated_infos;

    while (getline(temp, word, COMMA))
        separated_infos.push_back(word);

    return separated_infos;
}

RoomsInfo UTrip::separate_rooms_info(vector<string> separated_infos)
{
    RoomsInfo rooms_info;
    for (int i = 0; i < NUM_OF_ROOMS; i++)
    {
        rooms_info.num_of_each_room.push_back(stoi(separated_infos[i + FIRST_ROOM])); 
        rooms_info.price_of_each_room.push_back(stoi(separated_infos[i + FIRST_PRICE]));
    }
    return rooms_info;
}

void UTrip::read_ratings_info(string ratings_path)
{
    ifstream ratings_file(ratings_path);
    vector<string> separated_infos;
    string line;

    getline(ratings_file, line);
    for (int i = 0; getline(ratings_file, line); i++)
    {
        separated_infos = separate_line(line);
        hotels_info[find_hotel_by_id(separated_infos[0])]->
                add_old_rating(separated_infos);
    }
}

vector<string> UTrip::get_command_infos(stringstream& line, const vector<string> lables)
{
    string word1, word2;
    string temp1, temp2;
    vector<string> infos(lables.size(),EMPTY_);

    for (int i = 0; i < lables.size(); i++)
    { 
        line >> word1 >> word2;
        for (int j = 0; j < lables.size(); j++)
        {
            if (word1 == lables[j])
                infos[j] = word2;
        }
    }
    check_bad_request(infos);
    return infos;
}

void UTrip::check_bad_request(vector<string> infos)
{
    for (int i = 0; i < infos.size(); i++)
        if (infos[i].size() == 0)
            throw(BadRequest());
}

void UTrip::sign_up(vector<string> signup_infos)
{
    check_duplication(signup_infos);
    set_new_user(signup_infos);
}
void UTrip::check_duplication(vector<string> infos)
{
    if (infos[PASSWORD_] != infos[CONFIRM_PASSWORD_])
        throw(Server::Exception(DIFFRENT_PASSWORD));
    for (int i = 0; i < users_info.size(); i++)
    {
        if (users_info[i]->get_email() == infos[EMAIL_])
            throw(Server::Exception(USED_EMAIL));
        if (users_info[i]->get_username() == infos[USERNAME_])
            throw(Server::Exception(TAKEN_USERNAME));
    }
}

void UTrip::set_new_user(vector<string> infos)
{
    User* user = new User(infos[EMAIL_], infos[USERNAME_], infos[PASSWORD_]);
    users_info.push_back(user);
}

void UTrip::check_permission(string command)
{
    if (command != SIGNUP && command != LOGIN && logged_in_users.size() == ZERO)
        throw(PermissionDenied());
    if ((command == SIGNUP || command == LOGIN) && logged_in_users.size() != ZERO)
        throw(BadRequest());
}

void UTrip::login(string username, string password)
{
    check_login_info(username, password);
}

void UTrip::check_login_info(string username, string password)
{
    hash<string> hash_password;
    for (int i = 0; i < users_info.size(); i++)
        if (username == users_info[i]->get_username() 
                && hash_password(password) == users_info[i]->get_password())
        {
            logged_in_users.push_back(users_info[i]);
            return;
        }
    throw(Server::Exception(INVALID_USERNAME_PASSWORD));
}

void UTrip::logout(string username)
{
    int index = find_user(username);
    logged_in_users.erase(logged_in_users.begin() + index);
}

int UTrip::find_user(string username)
{
    for (int i = 0; i < logged_in_users.size(); i++)
        if (logged_in_users[i]->get_username() == username)
            return i;
    return NOT_FOUND_;
}

void UTrip::increase_wallet(stringstream& line)
{
    vector<string> infos = get_command_infos(line, increase_wallet_lables);
    if (stod(infos[0]) <= 0)
        throw(BadRequest());
    cout << OK << endl;
}

void UTrip::get_wallet_transactions(stringstream& line)
{
    vector<string> infos = get_command_infos(line, transaction_lables);
}

void UTrip::get_reserve_infos(stringstream& line)
{
    vector<string> infos = get_command_infos(line, reserve_lables);
    ReserveRequest req = make_reserve_request_struct(infos);
    check_hotel_id(req.hotel_id);
    vector<Room*> rooms = hotels_info[find_hotel_by_id(req.hotel_id)]
                ->check_rooms(req);
    
    if (rooms.size() == req.quantity)
        reserve_rooms(req, rooms);
    else 
        throw(NotEnoughRoom());
}
void UTrip::check_hotel_id(string id)
{
    if (find_hotel_by_id(id) == NOT_FOUND_)
        throw(NotFound());
}
ReserveRequest UTrip::make_reserve_request_struct(vector<string> infos)
{
    ReserveRequest req;
    req.hotel_id = infos[0];
    req.room_type = infos[1];
    req.quantity = stoi(infos[2]);
    req.reserve_date.check_in = stoi(infos[3]);
    req.reserve_date.check_out = stoi(infos[4]);
    return req;
}

void UTrip::reserve_rooms(ReserveRequest info, vector<Room*> rooms)
{
    for (int i = 0; i < rooms.size(); i++)
        rooms[i]->set_reserve_date(info.reserve_date);
    cout << endl;
}

void UTrip::show_user_reserves()
{
    logged_in_users[ZERO]->print_reserves_info();
}

int UTrip::find_hotel_by_id(string id)
{
    for (int i = 0; i < hotels_info.size(); i++)
        if (id == hotels_info[i]->get_id())
            return i;
    return NOT_FOUND_;
}

void UTrip::show_hotels_info()
{    
    check_default_price_filter();
    HotelVec filtered_hotels = apply_filters();

    if (filtered_hotels.size() == 0)
        cout << EMPTY << endl;
    for (int i = 0; i < filtered_hotels.size(); i++)
        filtered_hotels[i]->short_print_info();
}

void UTrip::check_default_price_filter()
{
    if (default_price_filter == ONE && filters[PRICE_FILTER_] == NULL 
            && logged_in_users[ZERO]->get_no_reserves() >= TEN)
    {
        Filter* default_price_filter_ = new DefaultPriceFilter(logged_in_users[ZERO]->
                calculate_standard_deviation(), 
                logged_in_users[ZERO]->calculate_rooms_avg_price());
        filters[DEFAULT_FILTER] = default_price_filter_;
        cout << FILTER_ATTENTION << endl;
    }
}

HotelVec UTrip::apply_filters()
{
    HotelVec filtered_hotels = hotels_info;
    for (int i = 0; i < FILTERS_SIZE; i++)
        if (filters[i] != NULL)
            filtered_hotels = filters[i]->filterList(filtered_hotels);
    return filtered_hotels;
}

void UTrip::show_hotel_info(stringstream& line)
{
    vector<string> infos = get_command_infos(line, id_lables);
    check_hotel_id(infos[0]);

    hotels_info[find_hotel_by_id(infos[0])]->full_print_info();
}

void UTrip::delete_reserves(stringstream& line)
{
    vector<string> infos = get_command_infos(line, id_lables);
    logged_in_users[ZERO]->delete_reserve(stoi(infos[0]));
    cout << OK << endl;
}

void UTrip::add_comment(stringstream& line)
{
    vector<string> infos = get_command_infos(line, comment_lables);
    check_hotel_id(infos[0]);

    hotels_info[find_hotel_by_id(infos[0])]->
            add_new_comment(logged_in_users[ZERO]->get_username(), infos[1]);
    cout << OK << endl;
}

void UTrip::show_hotel_comments(stringstream& line)
{
    vector<string> infos = get_command_infos(line, show_comment_lables);
    check_hotel_id(infos[0]);

    hotels_info[find_hotel_by_id(infos[0])]->print_comments();
}

void UTrip::add_rating(stringstream& line)
{
    vector<string> ratings = get_command_infos(line, rating_lables);
    check_hotel_id(ratings[0]);
    check_ratings(ratings);

    hotels_info[find_hotel_by_id(ratings[0])]
            ->add_new_rating(ratings, logged_in_users[ZERO]->get_username());
    cout << OK << endl;
}

void UTrip::check_ratings(vector<string> ratings)
{
    for (int i = 1; i < ratings.size(); i++)
        if ((stod(ratings[i]) < ONE) || (stod(ratings[i]) > FIVE))    
            throw(BadRequest());
}

void UTrip::show_hotel_ratings(std::stringstream& line)
{
    vector<string> infos = get_command_infos(line, show_rating_lables);
    check_hotel_id(infos[0]);

    hotels_info[find_hotel_by_id(infos[0])]->print_ratings();
}

void UTrip::add_filter(stringstream& line)
{
    string temp, word;
    getline(line, temp);
    stringstream temp1(temp);
    stringstream temp2(temp);
    temp1 >> word;
    if (word == CITY_)
        add_city_filter(temp1);
    else if (word == MIN_PRICE || word == MAX_PRICE)
        add_price_filter(temp2);
    else if (word == TYPE || word == QUANTITY ||
            word == CHECK_IN || word == CHECK_OUT)
        add_room_filter(temp2);
    else 
        throw(BadRequest());
}

void UTrip::add_city_filter(stringstream& line)
{
    string city_name = get_filter_city(line);
    vector<string> infos{city_name};
    if (filters[CITY_FILTER_] == NULL)
    {
        Filter* city_filter = new CityFilter(city_name);
        filters[CITY_FILTER_] = city_filter;
    }
    else
        filters[CITY_FILTER_]->replace_filters(infos);

    cout << OK << endl;
}

string UTrip::get_filter_city(stringstream& line)
{
    string city_name;
    getline(line >> ws, city_name);
    if (city_name.size() == ZERO)
        throw(BadRequest());
    return city_name;
}
void UTrip::add_room_filter(stringstream& line)
{
    vector<string> infos = get_command_infos(line, room_filter_lables);
    if (filters[ROOM_FILTER_] == NULL)
    {
        Filter* room_filter = new RoomFilter(infos);
        filters[ROOM_FILTER_] = room_filter;   
    }
    else
        filters[ROOM_FILTER_]->replace_filters(infos);

    cout << OK << endl; 
}

void UTrip::add_star_filter(string min, string max)
{
    vector<string> infos{min, max};

    if (filters[STAR_FILTER_] == NULL)
    {    
        Filter* star_period_filter = new StarPeriodFilter(infos);
        filters[STAR_FILTER_] =  star_period_filter;
    }
    else 
        filters[STAR_FILTER_]->replace_filters(infos);
}

void UTrip::check_starts_period(vector<string> infos)
{
    if (stod(infos[MIN_STAR_]) < ONE || stod(infos[MAX_STAR_]) > FIVE || 
            stod(infos[MIN_STAR_]) > stod(infos[MAX_STAR_]))
        throw(BadRequest());
}

void UTrip::add_price_filter(stringstream& line)
{
    vector<string> infos = get_command_infos(line, price_filter_lables);
    check_price_period(infos);
    if (filters[PRICE_FILTER_] == NULL)
    {
        Filter* price_filter = new AvgPriceFilter(infos);
        filters[PRICE_FILTER_] = price_filter;
    }
    else
        filters[PRICE_FILTER_]->replace_filters(infos);
    default_price_filter = OFF;
    cout << OK << endl;
}

void UTrip::check_price_period(vector<string> infos)
{
    if (stod(infos[MIN_PRICE_]) < ZERO ||
             stod(infos[MAX_PRICE_]) < stod(infos[MIN_PRICE_]))
        throw(BadRequest());
}

void UTrip::delete_filters()
{
    for (int i = 0; i < FILTERS_SIZE; i++)
    {    
        delete filters[i];
        filters[i] = NULL;
    }
    cout << OK << endl;
}


void UTrip::reset_default_price_filter(stringstream& line)
{
    vector<string> infos = get_command_infos(line, active_weights_lables);
    if (infos[0] == TRUE)
        default_price_filter = ON;
    else if(infos[0] == FALSE)
        default_price_filter = OFF;
    else
        throw(BadRequest());
    cout << OK << endl;
}

void UTrip::sort_hotels(stringstream& line)
{
    vector<string> infos = get_command_infos(line, sort_lables);
    which_sort(infos);
}

void UTrip::which_sort(vector<string> infos)
{
    if (infos[0] == ID_)
        sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
                { return a->get_id() < b->get_id(); });
    else if (infos[0] == NAME)
    	sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
                { return a->get_name() < b->get_name(); });
    else if (infos[0] == STAR_RATING_)
    	sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
                {   if (a->get_star() == b->get_star())
                        return a->get_id() < b->get_id();
                    return a->get_star() < b->get_star(); });
    else if (infos[0] == CITY_)
    	sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
                {   if (a->get_city_name() == b->get_city_name())
                        return a->get_id() < b->get_id();
                    return a->get_city_name() < b->get_city_name(); });
    else if (infos[0] == STANDARD_ROOM_PRICE)
    	sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
                {   if (a->get_room_details().price_of_each_room[0] ==
                         b->get_room_details().price_of_each_room[0])
                        return a->get_id() < b->get_id();
                    return a->get_room_details().price_of_each_room[0] <
                         b->get_room_details().price_of_each_room[0]; });
    else if (infos[0] == DELUXE_ROOM_PRICE)
    	sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
                {   if (a->get_room_details().price_of_each_room[1] ==
                         b->get_room_details().price_of_each_room[1])
                         return a->get_id() < b->get_id();
                    return a->get_room_details().price_of_each_room[1] <
                         b->get_room_details().price_of_each_room[1]; });
    else if (infos[0] == LUXURY_ROOM_PRICE)
    	sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
                {   if (a->get_room_details().price_of_each_room[2] ==
                         b->get_room_details().price_of_each_room[2])
                        return a->get_id() < b->get_id();
                    return a->get_room_details().price_of_each_room[2] <
                         b->get_room_details().price_of_each_room[2]; });
    else if (infos[0] == PREMIUM_ROOM_PRICE)
    	sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
                {   if (a->get_room_details().price_of_each_room[3] ==
                         b->get_room_details().price_of_each_room[3])
                         return a->get_id() < b->get_id();
                    return a->get_room_details().price_of_each_room[3] <
                         b->get_room_details().price_of_each_room[3]; });
    else if (infos[0] == AVERAGE_ROOM_PRICE)
    	sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
                {   if (a->calculate_avg_price() == b->calculate_avg_price())
                        return a->get_id() < b->get_id();
                    return a->calculate_avg_price() < b->calculate_avg_price(); });
    else if (infos[0] == RATING_PERSONAL)
        sort_by_ratings();
    else
        throw(BadRequest());
    if (infos[1] == DESCENDING)
        reverse(hotels_info.begin(), hotels_info.end());
    cout << OK << endl;
}

void UTrip::sort_by_ratings()
{
    manual_or_estimated_sort();
    sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
                {   if (a->get_overall_rating() == b->get_overall_rating())
                        return a->get_id() < b->get_id();
                    return a->get_overall_rating() < b->get_overall_rating(); });
}

void UTrip::manual_or_estimated_sort()
{
    RatingVec user_ratings = set_user_ratings();
    if (manual_weights[ZERO] != ZERO)
        set_public_ratings(manual_weights);
    else if (user_ratings.size() >= FIVE)
    {
        vector<double> estimated_weights = calculate_estimated_weights(user_ratings);
        set_public_ratings(estimated_weights);
    }
    else
        cout << INSUFFICIENT_RATINGS << endl;
    set_user_ratings();
}

RatingVec UTrip::set_user_ratings()
{
    RatingVec user_ratings;
    Rating* rating;
    for (int i = 0; i < hotels_info.size(); i++)
        if (rating = hotels_info[i]->find_user_rating(logged_in_users[ZERO]->get_username()))
            user_ratings.push_back(rating);
    return user_ratings;
}

void UTrip::set_public_ratings(vector<double> manual_weights_)
{
    for (int i = 0; i < hotels_info.size(); i++)
        hotels_info[i]->set_overall_ratings(manual_weights_);
}

void UTrip::reset_rating_weights(std::stringstream& line)
{
    vector<string> infos = get_command_infos(line, active_weights_lables);
    if (infos[ZERO] == TRUE)
    {   
        infos = get_command_infos(line, weights_lables);
        check_weights(infos);
        active_weights(infos);
    }
    else if (infos[ZERO] == FALSE)
        deactivate_weights();
    cout << OK << endl;
}

void UTrip::check_weights(vector<string> infos)
{
    for (int i = 0; i < infos.size(); i++)
        if (ONE > stod(infos[i]) || stod(infos[i]) > FIVE)
            throw(BadRequest());
}

void UTrip::active_weights(vector<string> infos)
{
    for (int i = 0; i < FIVE; i++)
        manual_weights[i] = stod(infos[i]);
}

void UTrip::deactivate_weights()
{
    for (int i = 0; i < manual_weights.size(); i++)
        manual_weights[i] = ZERO;
}

vector<double> UTrip::calculate_estimated_weights(RatingVec user_ratings)
{
    vector<double> guessed_weights = generate_random_weights();
    for (int i = 0; i < 10000; i++)
    {
        vector<double> d(5,0);
        for (int j = 0; j < user_ratings.size(); j++)
            for (int k = 0; k < 5; k++)
                d[k] += derivative_error_function(user_ratings[j], guessed_weights, k);
        for (int j = 0; j < 5; j++)
        {
            guessed_weights[j] -= d[j];
            if (guessed_weights[j] < ONE)
                guessed_weights[j] = ONE;
            else if (guessed_weights[j] > FIVE)
                guessed_weights[j] = FIVE;
        }
    }
    logged_in_users[ZERO]->set_estimated_ratings(guessed_weights);
    return guessed_weights;
}

vector<double> UTrip::generate_random_weights()
{
    vector<double> weights;
    srand(time(0));
    for (int i = 0; i < FIVE; i++)
        weights.push_back(random_number());
    return weights;
}

double UTrip::random_number()
{
    return ONE + (rand() / (RAND_MAX / (FIVE - ONE)));
}

double UTrip::error_function(Rating* rating, vector<double> weights)
{
    return pow((overall_satisfaction(rating, weights) - rating->get_overall()), 2);
}

double UTrip::overall_satisfaction(Rating* rating, vector<double> weights)
{
    double ratings_x_weights = 0;
    double weights_sum = 0;
    vector<double> rating_ = make_vector_of_rating(rating);
    for (int i = 0; i < FIVE; i++)
    {
        ratings_x_weights += (rating_[i] * weights[i]);
        weights_sum += weights[i];
    }
    return ratings_x_weights / weights_sum;
}

vector<double> UTrip::make_vector_of_rating(Rating* rating)
{
    vector<double> rating_(RATINGS_, ZERO);
    rating_[0] = rating->get_location();
    rating_[1] = rating->get_cleanliness();
    rating_[2] = rating->get_staff();
    rating_[3] = rating->get_facilities();
    rating_[4] = rating->get_value_for_money();
    rating_[5] = rating->get_overall();
    return rating_;
}

double UTrip::derivative_error_function(Rating* rating, vector<double> weights, int i)
{
    vector<double> temp_weights = weights;
    temp_weights[i] += 0.00001;
    return (error_function(rating, temp_weights) - error_function(rating, weights)) / 0.00001;
}

void UTrip::show_manual_weights()
{
    if (manual_weights[ZERO] == ZERO)
        cout << ACTIVE << WHITE_SPACE << FALSE << endl;
    else
        cout << ACTIVE << WHITE_SPACE << TRUE << WHITE_SPACE << LOCATION << WHITE_SPACE 
        << fixed << setprecision(2) << manual_weights[0] << WHITE_SPACE 
        << CLEANLINESS << WHITE_SPACE << floor(manual_weights[1] * HUNDRED) / HUNDRED 
        << WHITE_SPACE << STAFF << WHITE_SPACE << fixed 
        << floor(manual_weights[2] * HUNDRED) / HUNDRED << WHITE_SPACE << FACILITIES 
        << WHITE_SPACE << floor(manual_weights[3] * HUNDRED) / HUNDRED 
        << WHITE_SPACE << VALUE_FOR_MONEY << WHITE_SPACE
        << floor(manual_weights[4] * HUNDRED) / HUNDRED << WHITE_SPACE << endl;
}

void UTrip::show_estimated_weights()
{
    vector<double> estimated_weights = logged_in_users[ZERO]->get_estimated_weights();
    if (estimated_weights[0] == ZERO)
        cout << INSUFFICIENT_RATINGS << endl;
    for (int i = 0; i < estimated_weights.size(); i++)
        cout << rating_lables[i + 1] << WHITE_SPACE << estimated_weights[i] << WHITE_SPACE;
    cout << endl;
}

User* UTrip::get_user(string username)
{
    for (int i = 0; i < users_info.size(); i++)
        if (users_info[i]->get_username() == username)
            return users_info[i];
}