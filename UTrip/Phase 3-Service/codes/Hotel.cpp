#include <iostream>
#include <iomanip>

#include "Hotel.hpp"
#include "NoRating.hpp"

using namespace std;

Hotel::Hotel(string unique_id_, string property_name_,
        int star_rating_, string hotel_overview_,
        string property_amenities_, string city_name_, 
        string latitude, string longitude, string image_url_,
        RoomsInfo rooms_info_)
{
    unique_id = unique_id_;
    property_name = property_name_;
    star_rating = star_rating_;
    hotel_overview = hotel_overview_;
    property_amenities = property_amenities_;
    city_name = city_name_;
    coordinates.first = stod(latitude);
    coordinates.second = stod(longitude);
    image_url = image_url_;
    room_details = rooms_info_;
	set_rooms_info(rooms_info_);
}

void Hotel::set_rooms_info(RoomsInfo rooms_info_)
{
	set_which_rooms(rooms_info_.num_of_each_room[STANDARD_], 
            rooms_info_.price_of_each_room[STANDARD_], STANDARD_S);
	set_which_rooms(rooms_info_.num_of_each_room[DELUXE_], 
            rooms_info_.price_of_each_room[DELUXE_], DELUXE_D);
	set_which_rooms(rooms_info_.num_of_each_room[LUXURY_], 
            rooms_info_.price_of_each_room[LUXURY_], LUXURY_L);
	set_which_rooms(rooms_info_.num_of_each_room[PREMIUM_], 
            rooms_info_.price_of_each_room[PREMIUM_], PREMIUM_P);
}

void Hotel::set_which_rooms(int count, int price, char room_id)
{
	for (int i = 1; i <= count; i++)
	{
		string id = room_id + to_string(i);
		Room* room = new Room(id, price);
		rooms_info.push_back(room);
	}
}

void Hotel::short_print_info()
{
    cout << unique_id << WHITE_SPACE << property_name << WHITE_SPACE << star_rating
         << WHITE_SPACE << city_name << WHITE_SPACE << rooms_info.size() << WHITE_SPACE 
         << fixed << setprecision(2) << calculate_avg_price() << WHITE_SPACE << endl;
}

void Hotel::full_print_info()
{
    print_hotel_info();
    print_num_of_each_room();
    print_price_of_each_room();
}

void Hotel::print_hotel_info()
{
    cout << unique_id << endl << property_name << endl 
         << STAR_ << star_rating << endl << OVERVIEW_
         << hotel_overview << endl << AMENITIES_ << property_amenities
         << endl << CITY__ << city_name << endl << LATITUDE_ << fixed << setprecision(2)
         << coordinates.first << endl << LONGITUDE_ << fixed << setprecision(2)
         << coordinates.second << endl;
}
void Hotel::print_num_of_each_room()
{
    cout << ROOMS_ << room_details.num_of_each_room[0];
    for (int i = 1; i < room_details.num_of_each_room.size(); i++)
        cout << WHITE_SPACE << room_details.num_of_each_room[i];
}

void Hotel::print_price_of_each_room()
{
    cout << endl << PRICE_ << room_details.price_of_each_room[0];
    for (int i = 1; i < room_details.price_of_each_room.size(); i++)
        cout << WHITE_SPACE << room_details.price_of_each_room[i];
    cout << endl; 
}

double Hotel::calculate_avg_price()
{
    double price_sum = 0;
    int count = 0;
    for (int i = 0; i < room_details.num_of_each_room.size(); i++)
        if (room_details.price_of_each_room[i] != 0)
        {
            price_sum += room_details.price_of_each_room[i];
            count++;
        }
    if (count == 0)
        return 0;
    return price_sum / count;
}

vector<Room*> Hotel::check_rooms(ReserveRequest req)
{
    char id_ = which_room(req.room_type);
    vector<Room*> reserved_rooms;
    for (int i = 0; i < rooms_info.size(); i++)
    {
        if (reserved_rooms.size() == req.quantity)
            break;
        if (id_ == rooms_info[i]->get_id()[0] && rooms_info[i]->is_available(req.reserve_date))
            reserved_rooms.push_back(rooms_info[i]);
    }
    return reserved_rooms;
}

char Hotel::which_room(string type)
{
    if (type == STANDARD)
        return STANDARD_S;
    else if (type == DELUXE)
        return DELUXE_D;
    else if (type == LUXURY)
        return LUXURY_L;
    else if (type == PREMIUM)
        return PREMIUM_P;
}

void Hotel::add_new_comment(string username, string comment)
{
    comments_info.push_back(Comment(username, comment));
}

void Hotel::print_comments()
{
    for (int i = 0; i < comments_info.size(); i++)
        cout << comments_info[i].get_username() << COLON
             << comments_info[i].get_comment() << endl;
}

void Hotel::add_new_rating(vector<string> ratings, string username)
{
    int index = find_rating_by_username(username);
    if (index >= 0)
        new_ratings[index]->replace_ratings(ratings);
    else
        {
            ratings.insert(ratings.begin(), username);
            Rating* rating = new Rating(ratings);
            new_ratings.push_back(rating);
        }
}

void Hotel::add_old_rating(vector<string> ratings)
{
    ratings.insert(ratings.begin(), EMPTY_);
    Rating* rating = new Rating(ratings);
    old_ratings.push_back(rating);
}

int Hotel::find_rating_by_username(string username)
{
    for (int i = 0; i < new_ratings.size(); i++)
        if (new_ratings[i]->get_username() == username)
            return i;
    return NOT_FOUND_;
}

void Hotel::print_ratings()
{
    if (old_ratings.size() == 0)
        throw(NoRating());

    cout << LOCATION << COLON << fixed << setprecision(2) 
         << old_ratings[0]->get_location() << endl 
         << CLEANLINESS << COLON << fixed << setprecision(2) 
         << old_ratings[0]->get_cleanliness() << endl
         << STAFF << COLON << fixed << setprecision(2) 
         << old_ratings[0]->get_staff() << endl << FACILITIES 
         << COLON << fixed << setprecision(2) 
         << old_ratings[0]->get_facilities() << endl 
         << VALUE_FOR_MONEY << COLON << fixed << setprecision(2) 
         << old_ratings[0]->get_value_for_money() << endl
         << OVERALL_RATING << COLON << fixed << setprecision(2) 
         << old_ratings[0]->get_overall() << endl;
}

double Hotel::calculate_location_avg()
{
    double sum = 0;
    for (int i = 0; i < old_ratings.size(); i++)
        sum += old_ratings[i]->get_location();
    return sum / old_ratings.size();
}

double Hotel::calculate_cleanliness_avg()
{
    double sum = 0;
    for (int i = 0; i < old_ratings.size(); i++)
        sum += old_ratings[i]->get_cleanliness();
    return sum / old_ratings.size();
}

double Hotel::calculate_staff_avg()
{
    double sum = 0;
    for (int i = 0; i < old_ratings.size(); i++)
        sum += old_ratings[i]->get_staff();
    return sum / old_ratings.size();
}

double Hotel::calculate_facilities_avg()
{
    double sum = 0;
    for (int i = 0; i < old_ratings.size(); i++)
        sum += old_ratings[i]->get_facilities();
    return sum / old_ratings.size();
}

double Hotel::calculate_value_for_money_avg()
{
    double sum = 0;
    for (int i = 0; i < old_ratings.size(); i++)
        sum += old_ratings[i]->get_value_for_money();
    return sum / old_ratings.size();
}

double Hotel::calculate_overall_avg()
{
    double sum = 0;
    for (int i = 0; i < old_ratings.size(); i++)
        sum += old_ratings[i]->get_overall();
    return sum / old_ratings.size();
}

Rating* Hotel::find_user_rating(string username)
{
    for (int i = 0; i < new_ratings.size(); i++)
        if (new_ratings[i]->get_username() == username)
        {
            overall_rating = new_ratings[i]->get_overall();
            return new_ratings[i];
        }
    return NULL;
}

void Hotel::set_overall_ratings(vector<double> weights)
{
    double sum = 0;
    double count = 0;
    for (int i = 0; i < old_ratings.size(); i++)
    {
        sum += calculate_ratings_sum(weights);
        count += calculate_weights_sum(weights);
    }
    overall_rating = sum / count;
}

double Hotel::calculate_ratings_sum(vector<double> weights)
{
    return (old_ratings[0]->get_location() * weights[0]) +
           (old_ratings[0]->get_cleanliness() * weights[1]) +
           (old_ratings[0]->get_staff() * weights[2]) +
           (old_ratings[0]->get_facilities() * weights[3]) +
           (old_ratings[0]->get_value_for_money() * weights[4]);
}

double Hotel::calculate_weights_sum(vector<double> weights)
{
    double weights_sum = 0;
    for (int i = 0; i < WEIGHTS_; i++)
        weights_sum += weights[i];
    return weights_sum;
}
