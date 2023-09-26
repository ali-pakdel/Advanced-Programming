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
#include "InsufficientRatings.hpp"

using namespace std;

void UTrip::read_infos(string hotels_path, string ratings_path)
{
    read_hotels_info(hotels_path);
    read_ratings_info(ratings_path);
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
        find_hotel_by_id(separated_infos[ID__])->add_old_rating(separated_infos);
    }
}

vector<string> UTrip::get_command_infos(stringstream& line, const vector<string> labels)
{
    string word1, word2;
    vector<string> infos(labels.size(),EMPTY_);

    for (int i = 0; i < labels.size(); i++)
    { 
        line >> word1 >> word2;
        for (int j = 0; j < labels.size(); j++)
        {
            if (word1 == labels[j])
                infos[j] = word2;
        }
    }
    check_bad_request(infos);
    return infos;
}

Hotel* UTrip::find_hotel_by_id(string id)
{
    auto hotel = find_if(hotels_info.begin(), hotels_info.end(), [id](Hotel* a)
    {
        if (a->get_id() == id)
            return a;
    });
    if (hotel != hotels_info.end())
        return *hotel;
    return NULL;
}

void UTrip::check_bad_request(vector<string> infos)
{

    if (infos[ZERO] == FALSE)
        return;
    for (int i = 0; i < infos.size(); i++)
        if (infos[i].size() == 0)
            throw(BadRequest());
}
void UTrip::check_duplication(vector<string> infos)
{
    for (int i = 0; i < users_info.size(); i++)
        if (users_info[i]->get_email() == infos[0] ||
                users_info[i]->get_username() == infos[1])
            throw(BadRequest());
}
void UTrip::check_permission(string command)
{
    if (command != SIGNUP && command != LOGIN && logged_in_user == NULL)
        throw(PermissionDenied());
    if ((command == SIGNUP || command == LOGIN) && logged_in_user != NULL)
        throw(BadRequest());
}

void UTrip::check_not_found(string id_)
{
    Hotel* hotel = find_hotel_by_id(id_);
    if (hotel == NULL)
        throw(NotFound());
}

void UTrip::sign_up(stringstream& line)
{
    vector<string> infos = get_command_infos(line, signup_labels);
    check_duplication(infos);
    set_new_user(infos);
}
void UTrip::set_new_user(vector<string> infos)
{
    User* user = new User(infos[0], infos[1], infos[2]);
    users_info.push_back(user);
    logged_in_user = user;
    cout << OK << endl;
}
void UTrip::login(stringstream& line)
{
    vector<string> infos = get_command_infos(line, login_labels);
    check_login_info(infos[0], infos[1]);
    cout << OK << endl;
}
void UTrip::check_login_info(string email, string password)
{
    hash<string> hash_password;
    for (int i = 0; i < users_info.size(); i++)
        if (email == users_info[i]->get_email() 
                && hash_password(password) == users_info[i]->get_password())
        {
            logged_in_user = users_info[i];
            return;
        }
    throw(BadRequest());
}
void UTrip::logout()
{
    default_price_filter = ON;
    logged_in_user = NULL;
    delete_manual_weights();
    delete_filters();
    sort_by_id();
}

void UTrip::increase_wallet(stringstream& line)
{
    vector<string> infos = get_command_infos(line, increase_wallet_labels);
    if (stod(infos[0]) <= 0)
        throw(BadRequest());
    logged_in_user->increase_wallet(stod(infos[0]));
    cout << OK << endl;
}
void UTrip::get_wallet_transactions(stringstream& line)
{
    vector<string> infos = get_command_infos(line, transaction_labels);
    logged_in_user->print_transactions(stoi(infos[0]));
}

void UTrip::get_reserve_infos(stringstream& line)
{
    vector<string> infos = get_command_infos(line, reserve_labels);
    ReserveRequest req = make_reserve_request_struct(infos);
    check_not_found(req.hotel_id);
    vector<Room*> rooms = find_hotel_by_id(req.hotel_id)->check_rooms(req);
    
    if (rooms.size() == req.quantity)
        reserve_rooms(req, rooms);
    else 
        throw(NotEnoughRoom());
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
    logged_in_user->set_reserve_info(info, rooms);
    for (int i = 0; i < rooms.size(); i++)
        rooms[i]->set_reserve_date(info.reserve_date);
    cout << endl;
}
void UTrip::show_user_reserves()
{
    logged_in_user->print_reserves_info();
}
void UTrip::delete_reserves(stringstream& line)
{
    vector<string> infos = get_command_infos(line, id_labels);
    logged_in_user->delete_reserve(stoi(infos[0]));
    cout << OK << endl;
}

void UTrip::show_hotels_info()
{    
    check_default_price_filter();
    which_sort();
    HotelVec filtered_hotels = apply_filters();

    if (filtered_hotels.size() == 0)
        cout << EMPTY << endl;
    for (int i = 0; i < filtered_hotels.size(); i++)
        filtered_hotels[i]->short_print_info();
}
void UTrip::show_hotel_info(stringstream& line)
{
    vector<string> infos = get_command_infos(line, id_labels);
    check_not_found(infos[ID__]);
    find_hotel_by_id(infos[ID__])->full_print_info();
}

HotelVec UTrip::apply_filters()
{
    HotelVec filtered_hotels = hotels_info;
    for (int i = 0; i < FILTERS_SIZE; i++)
        if (filters[i] != NULL)
            filtered_hotels = filters[i]->filterList(filtered_hotels);
    return filtered_hotels;
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
    else if (word == MIN_STAR || word == MAX_STAR)
        add_star_period_filter(temp2);
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
    vector<string> infos = get_command_infos(line, room_filter_labels);
    if (filters[ROOM_FILTER_] == NULL)
    {
        Filter* room_filter = new RoomFilter(infos);
        filters[ROOM_FILTER_] = room_filter;   
    }
    else
        filters[ROOM_FILTER_]->replace_filters(infos);

    cout << OK << endl; 
}
void UTrip::add_star_period_filter(stringstream& line)
{
    vector<string> infos = get_command_infos(line, star_filter_labels);
    check_starts_period(infos);

    if (filters[STAR_FILTER_] == NULL)
    {    
        Filter* star_period_filter = new StarPeriodFilter(infos);
        filters[STAR_FILTER_] =  star_period_filter;
    }
    else 
        filters[STAR_FILTER_]->replace_filters(infos);

    cout << OK << endl;
}
void UTrip::check_starts_period(vector<string> infos)
{
    if (stod(infos[MIN_STAR_]) < ONE || stod(infos[MAX_STAR_]) > FIVE || 
            stod(infos[MIN_STAR_]) > stod(infos[MAX_STAR_]))
        throw(BadRequest());
}
void UTrip::add_price_filter(stringstream& line)
{
    vector<string> infos = get_command_infos(line, price_filter_labels);
    check_price_period(infos);
    if (filters[PRICE_FILTER_] == NULL)
    {
        Filter* price_filter = new AvgPriceFilter(infos);
        filters[PRICE_FILTER_] = price_filter;
    }
    else
        filters[PRICE_FILTER_]->replace_filters(infos);
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

void UTrip::add_comment(stringstream& line)
{
    vector<string> infos = get_command_infos(line, comment_labels);
    check_not_found(infos[ID__]);
    find_hotel_by_id(infos[ID__])->add_new_comment(logged_in_user->get_username(), infos[1]);
    cout << OK << endl;
}
void UTrip::show_hotel_comments(stringstream& line)
{
    vector<string> infos = get_command_infos(line, show_comment_labels);
    check_not_found(infos[ID__]);
    find_hotel_by_id(infos[ID__])->print_comments();
}
void UTrip::add_rating(stringstream& line)
{
    vector<string> ratings = get_command_infos(line, rating_labels);
    check_ratings(ratings);
    check_not_found(ratings[ID__]);
    find_hotel_by_id(ratings[ID__])->add_new_rating(ratings, logged_in_user->get_username());
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
    vector<string> infos = get_command_infos(line, show_rating_labels);
    check_not_found(infos[ID__]);
    find_hotel_by_id(infos[ID__])->print_ratings();
}

void UTrip::reset_default_price_filter(stringstream& line)
{
    vector<string> infos = get_command_infos(line, active_labels);
    if (infos[0] == TRUE)
        default_price_filter = ON;
    else if(infos[0] == FALSE)
        default_price_filter = OFF;
    else
        throw(BadRequest());
    cout << OK << endl;
}
void UTrip::check_default_price_filter()
{
    if (default_price_filter == ON && 
            logged_in_user->get_no_reserves() >= TEN &&
                    filters[PRICE_FILTER_] == NULL)
    {
        Filter* default_price_filter_ = new DefaultPriceFilter(logged_in_user->
                calculate_standard_deviation(), 
                logged_in_user->calculate_rooms_avg_price());
        filters[DEFAULT_FILTER] = default_price_filter_;
        cout << FILTER_ATTENTION << endl;
    }
}

void UTrip::sort_hotels(stringstream& line)
{
    vector<string> infos = get_command_infos(line, sort_labels);
    sort_type = infos;
    check_sort();
}

void UTrip::check_sort()
{
    for (int i = 0; i < sort_labels_.size(); i++)
        if (sort_type[SORT_TYPE] == sort_labels_[i] &&
                 (sort_type[ORDER_] == ASCENDING || sort_type[ORDER_] == DESCENDING))
        {
            cout << OK << endl;
            return;
        }
    throw(BadRequest());
}
void UTrip::which_sort()
{
    if (sort_type[SORT_TYPE] == EMPTY_)
        return;
    if (sort_type[SORT_TYPE] == ID_)
        sort_by_id();
    else if (sort_type[SORT_TYPE] == NAME)
        sort_by_name();
    else if (sort_type[SORT_TYPE] == STAR_RATING_)
        sort_by_star(sort_type[ORDER_]);
    else if (sort_type[SORT_TYPE] == CITY_)
        sort_by_city(sort_type[ORDER_]);
    else if (sort_type[SORT_TYPE] == STANDARD_ROOM_PRICE)
        sort_by_standard_room(sort_type[ORDER_]);
    else if (sort_type[SORT_TYPE] == DELUXE_ROOM_PRICE)
        sort_by_deluxe_room(sort_type[ORDER_]);
    else if (sort_type[SORT_TYPE] == LUXURY_ROOM_PRICE)
        sort_by_luxury_room(sort_type[ORDER_]);
    else if (sort_type[SORT_TYPE] == PREMIUM_ROOM_PRICE)
        sort_by_premium_room(sort_type[ORDER_]);
    else if (sort_type[SORT_TYPE] == AVERAGE_ROOM_PRICE)
        sort_by_avg_price(sort_type[ORDER_]);
    else if (sort_type[SORT_TYPE] == RATING_PERSONAL)
        sort_by_ratings(sort_type[ORDER_]);

    if (sort_type[ORDER_] == DESCENDING)
        reverse(hotels_info.begin(), hotels_info.end());
}
void UTrip::sort_by_id()
{
    sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
    { 
        return a->get_id() < b->get_id(); 
    });
}

void UTrip::sort_by_name()
{
    sort(hotels_info.begin(), hotels_info.end(), [](Hotel* a, Hotel* b) 
    { 
        return a->get_name() < b->get_name(); 
    });
}

void UTrip::sort_by_star(string order)
{
    sort(hotels_info.begin(), hotels_info.end(), [order](Hotel* a, Hotel* b) 
    {   
        if (a->get_star() == b->get_star() && order == ASCENDING)
           return a->get_id() < b->get_id();

        if (a->get_star() == b->get_star() && order == DESCENDING)
            return a->get_id() > b->get_id();

        return a->get_star() < b->get_star(); 
    });
}

void UTrip::sort_by_city(string order)
{
    sort(hotels_info.begin(), hotels_info.end(), [order](Hotel* a, Hotel* b) 
    { 
        if (a->get_city_name() == b->get_city_name() && order == ASCENDING)
            return a->get_id() < b->get_id();

        if (a->get_city_name() == b->get_city_name() && order == DESCENDING)
            return a->get_id() > b->get_id();

        return a->get_city_name() < b->get_city_name(); 
    });    
}

void UTrip::sort_by_standard_room(string order)
{
    sort(hotels_info.begin(), hotels_info.end(), [order](Hotel* a, Hotel* b) 
    {   
        if (a->get_room_details().price_of_each_room[STANDARD_] ==
                b->get_room_details().price_of_each_room[STANDARD_] && order == ASCENDING)
            return a->get_id() < b->get_id();

        if (a->get_room_details().price_of_each_room[STANDARD_] ==
                b->get_room_details().price_of_each_room[STANDARD_] && order == DESCENDING)
            return a->get_id() > b->get_id();

        return a->get_room_details().price_of_each_room[STANDARD_] <
                b->get_room_details().price_of_each_room[STANDARD_]; 
    });
}

void UTrip::sort_by_deluxe_room(string order)
{
    sort(hotels_info.begin(), hotels_info.end(), [order](Hotel* a, Hotel* b) 
    {   
        if (a->get_room_details().price_of_each_room[DELUXE_] ==
                b->get_room_details().price_of_each_room[DELUXE_] && order == ASCENDING)
            return a->get_id() < b->get_id();

        if (a->get_room_details().price_of_each_room[DELUXE_] ==
                b->get_room_details().price_of_each_room[DELUXE_] && order == DESCENDING)
            return a->get_id() > b->get_id();

        return a->get_room_details().price_of_each_room[DELUXE_] <
                b->get_room_details().price_of_each_room[DELUXE_]; 
    });
}

void UTrip::sort_by_luxury_room(string order)
{
    sort(hotels_info.begin(), hotels_info.end(), [order](Hotel* a, Hotel* b) 
    {   
        if (a->get_room_details().price_of_each_room[LUXURY_] ==
                b->get_room_details().price_of_each_room[LUXURY_] && order == ASCENDING)
            return a->get_id() < b->get_id();

        if (a->get_room_details().price_of_each_room[LUXURY_] ==
                b->get_room_details().price_of_each_room[LUXURY_] && order == DESCENDING)
            return a->get_id() > b->get_id();

        return a->get_room_details().price_of_each_room[LUXURY_] <
                b->get_room_details().price_of_each_room[LUXURY_]; 
    });
}

void UTrip::sort_by_premium_room(string order)
{
    sort(hotels_info.begin(), hotels_info.end(), [order](Hotel* a, Hotel* b) 
    {   
        if (a->get_room_details().price_of_each_room[PREMIUM_] ==
                b->get_room_details().price_of_each_room[PREMIUM_] && order == ASCENDING)
            return a->get_id() < b->get_id();

        if (a->get_room_details().price_of_each_room[PREMIUM_] ==
                b->get_room_details().price_of_each_room[PREMIUM_] && order == DESCENDING)
            return a->get_id() > b->get_id();

        return a->get_room_details().price_of_each_room[PREMIUM_] <
                b->get_room_details().price_of_each_room[PREMIUM_]; 
    });    
}

void UTrip::sort_by_avg_price(string order)
{
    sort(hotels_info.begin(), hotels_info.end(), [order](Hotel* a, Hotel* b) 
    {   
        if (a->calculate_avg_price() == b->calculate_avg_price() && order == ASCENDING)
            return a->get_id() < b->get_id();

        if (a->calculate_avg_price() == b->calculate_avg_price() && order == DESCENDING)
            return a->get_id() > b->get_id();

        return a->calculate_avg_price() < b->calculate_avg_price(); 
    });
}

void UTrip::sort_by_ratings(string order)
{
    manual_or_estimated_sort();
    sort(hotels_info.begin(), hotels_info.end(), [order](Hotel* a, Hotel* b) 
    {   
        if (a->get_overall_rating() == b->get_overall_rating() && order == ASCENDING)
            return a->get_id() < b->get_id();

        if (a->get_overall_rating() == b->get_overall_rating() && order == DESCENDING)
            return a->get_id() > b->get_id();

        return a->get_overall_rating() < b->get_overall_rating(); 
    });
}

void UTrip::reset_rating_weights(std::stringstream& line)
{
    vector<string> infos = get_command_infos(line, weights_labels);
    if (infos[ZERO] == TRUE)
    {   
        check_weights(infos);
        active_weights(infos);
    }
    else if (infos[ZERO] == FALSE)
        deactivate_weights();
    cout << OK << endl;
}
void UTrip::check_weights(vector<string> infos)
{
    for (int i = 1; i < infos.size(); i++)
        if (ONE > stod(infos[i]) || stod(infos[i]) > FIVE)
            throw(BadRequest());
}
void UTrip::active_weights(vector<string> infos)
{
    infos.erase(infos.begin());
    for (int i = 0; i < infos.size(); i++)
        manual_weights[i] = stod(infos[i]);
}
void UTrip::deactivate_weights()
{
    for (int i = 0; i < manual_weights.size(); i++)
        manual_weights[i] = ZERO;
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
        throw(InsufficientRatings());
    set_user_ratings();
}
RatingVec UTrip::set_user_ratings()
{
    RatingVec user_ratings;
    Rating* rating;
    for (int i = 0; i < hotels_info.size(); i++)
        if (rating = hotels_info[i]->find_user_rating(logged_in_user->get_username()))
            user_ratings.push_back(rating);
    return user_ratings;
}
void UTrip::set_public_ratings(vector<double> manual_weights_)
{
    for (int i = 0; i < hotels_info.size(); i++)
        hotels_info[i]->set_overall_ratings(manual_weights_);
}

vector<double> UTrip::calculate_estimated_weights(RatingVec user_ratings)
{
    vector<double> guessed_weights = generate_random_weights();
    for (int i = 0; i < TWO_THOUSAND; i++)
    {
        vector<double> derivatives(FIVE,ZERO);
        derivatives = calculate_new_derivatives(guessed_weights, derivatives, user_ratings);
        guessed_weights = check_weight_limits(guessed_weights, derivatives);
    }
    logged_in_user->set_estimated_ratings(guessed_weights);
    return guessed_weights;
}
vector<double> UTrip::calculate_new_derivatives(vector<double> guessed_weights,
         vector<double> derivatives, RatingVec user_ratings_)
{
    for (int j = 0; j < user_ratings_.size(); j++)
        for (int k = 0; k < FIVE; k++)
            derivatives[k] += derivative_error_function(user_ratings_[j], guessed_weights, k);
    return derivatives;
}
vector<double> UTrip::check_weight_limits(vector<double> guessed_weights, vector<double> derivatives)
{
    for (int i = 0; i < guessed_weights.size(); i++)
    {
        guessed_weights[i] -= derivatives[i];
        if (guessed_weights[i] < ONE)
            guessed_weights[i] = ONE;
        else if (guessed_weights[i] > FIVE)
            guessed_weights[i] = FIVE;
    }
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
    return pow((overall_satisfaction(rating, weights) - rating->get_overall()), TWO_);
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
    rating_[LOCATION_] = rating->get_location();
    rating_[CLEANLINESS_] = rating->get_cleanliness();
    rating_[STAFF_] = rating->get_staff();
    rating_[FACILITIES_] = rating->get_facilities();
    rating_[VALUE_FOR_MONEY__] = rating->get_value_for_money();
    rating_[OVERALL_] = rating->get_overall();
    return rating_;
}
double UTrip::derivative_error_function(Rating* rating, vector<double> weights, int i)
{
    vector<double> temp_weights = weights;
    temp_weights[i] += EPSILON;
    return (error_function(rating, temp_weights) - error_function(rating, weights)) / EPSILON;
}

void UTrip::show_manual_weights()
{
    if (manual_weights[ZERO] == ZERO)
        cout << ACTIVE << WHITE_SPACE << FALSE << endl;
    else
    {
        cout << ACTIVE << WHITE_SPACE << TRUE << WHITE_SPACE; 
        for (int i = 0; i < manual_weights.size(); i++)
        {
            cout << weights_labels[i + 1] << WHITE_SPACE << fixed << setprecision(TWO_) 
            << floor(manual_weights[i] * HUNDRED) / HUNDRED << WHITE_SPACE;
        }
            cout << endl;
    }
}

void UTrip::show_estimated_weights()
{
    if (sort_type[SORT_TYPE] == RATING_PERSONAL)
        which_sort();
    vector<double> estimated_weights = logged_in_user->get_estimated_weights();
    if (estimated_weights[ZERO] == ZERO)
        throw(InsufficientRatings());
    for (int i = 0; i < estimated_weights.size(); i++)
        cout << rating_labels[i + 1] << WHITE_SPACE << estimated_weights[i] << WHITE_SPACE;
    cout << endl;
}

void UTrip::delete_manual_weights()
{
    for (int i = 0; i < WEIGHTS_; i++)
        manual_weights[i] = ZERO;
}