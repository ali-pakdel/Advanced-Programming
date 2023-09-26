#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "UTrip.hpp"
#include "CityFilter.hpp"
#include "RoomFilter.hpp"
#include "AvgPriceFilter.hpp"
#include "StarPeriodFilter.hpp"

#include "BadRequest.hpp"
#include "NotFound.hpp"
#include "PermissionDenied.hpp"
#include "NotEnoughRoom.hpp"

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
        VALUE_FOR_MOENY, OVERALL_RATING};
const vector<string> show_rating_lables{HOTEL};
const vector<string> room_filter_lables{TYPE, QUANTITY, CHECK_IN, CHECK_OUT};
const vector<string> star_filter_lables{MIN_STAR, MAX_STAR};
const vector<string> price_filter_lables{MIN_PRICE, MAX_PRICE};

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

void UTrip::sign_up(stringstream& line)
{
    vector<string> infos = get_command_infos(line, signup_lables);
    check_duplication(infos);
    set_new_user(infos);
}
void UTrip::check_duplication(vector<string> infos)
{
    for (int i = 0; i < users_info.size(); i++)
        if (users_info[i]->get_email() == infos[0] ||
                users_info[i]->get_username() == infos[1])
            throw(BadRequest());
}
void UTrip::set_new_user(vector<string> infos)
{
    User* user = new User(infos[0], infos[1], infos[2]);
    users_info.push_back(user);
    logged_in_user = user;
    cout << OK << endl;
}

void UTrip::check_permission(string command)
{
    if (command != SIGNUP && command != LOGIN && logged_in_user == NULL)
        throw(PermissionDenied());
    if ((command == SIGNUP || command == LOGIN) && logged_in_user != NULL)
        throw(BadRequest());
}

void UTrip::login(stringstream& line)
{
    vector<string> infos = get_command_infos(line, login_lables);
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
    logged_in_user = NULL;
    delete_filters();
}

void UTrip::increase_wallet(stringstream& line)
{
    vector<string> infos = get_command_infos(line, increase_wallet_lables);
    if (stod(infos[0]) <= 0)
        throw(BadRequest());
    logged_in_user->increase_wallet(stod(infos[0]));
    cout << OK << endl;
}

void UTrip::get_wallet_transactions(stringstream& line)
{
    vector<string> infos = get_command_infos(line, transaction_lables);
    logged_in_user->print_transactions(stoi(infos[0]));
}

void UTrip::get_reserve_infos(stringstream& line)
{
    vector<string> infos = get_command_infos(line, reserve_lables);
    ReserveRequest req = make_reserve_request_struct(infos);
    check_hotel_id(req.hotel_id);
    vector<Room*> rooms = hotels_info[find_hotel_by_id(req.hotel_id)]->check_rooms(req);
    
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
    logged_in_user->set_reserve_info(info, rooms);
    rooms[0]->set_reserve_date(info.reserve_date);
    for (int i = 1; i < rooms.size(); i++)
    {
        cout << WHITE_SPACE;
        rooms[i]->set_reserve_date(info.reserve_date);
    }
    cout << endl;
}

void UTrip::show_user_reserves()
{
    logged_in_user->print_reserves_info();
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
    HotelVec filterd_hotels = apply_filters();

    if (filterd_hotels.size() == 0)
        cout << EMPTY << endl;
    for (int i = 0; i < filterd_hotels.size(); i++)
        filterd_hotels[i]->short_print_info();
}

HotelVec UTrip::apply_filters()
{
    HotelVec filterd_hotels = hotels_info;
    for (int i = 0; i < FILTERS_SIZE; i++)
        if (filters[i] != NULL)
            filterd_hotels = filters[i]->filterList(filterd_hotels);
    return filterd_hotels;
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
    logged_in_user->delete_reserve(stoi(infos[0]));
    cout << OK << endl;
}

void UTrip::add_comment(stringstream& line)
{
    vector<string> infos = get_command_infos(line, comment_lables);
    check_hotel_id(infos[0]);

    hotels_info[find_hotel_by_id(infos[0])]->
            add_new_comment(logged_in_user->get_username(), infos[1]);
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
            ->add_new_rating(ratings, logged_in_user->get_username());
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

void UTrip::add_star_period_filter(stringstream& line)
{
    vector<string> infos = get_command_infos(line, star_filter_lables);
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
    vector<string> infos = get_command_infos(line, price_filter_lables);
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

