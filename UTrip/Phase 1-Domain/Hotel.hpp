#ifndef HOTEL_HPP
#define HOTEL_HPP

#include "Room.hpp"
#include "Comment.hpp"
#include "Rating.hpp"

#include <vector>
#include <string>

class Hotel 
{
public:
    Hotel(std::string unique_id_, std::string property_name_, 
            int star_rating_, std::string hotel_overview, 
            std::string property_amenities_,
            std::string city_, std::string latitude,
            std::string longitude, std::string image_url_, 
            RoomsInfo rooms_info_);

    void short_print_info();
    void full_print_info();
    std::vector<Room*> check_rooms(ReserveRequest req);
    int check_cost(ReserveRequest req);
    void add_new_comment(std::string username, std::string comment);
    void add_new_rating(std::vector<std::string> ratings, std::string username);
    void print_comments();
    void print_ratings();
    std::vector<Room*> find_rooms(ReserveRequest infos);
    double calculate_average_price();

    std::string get_id() { return unique_id; }
    std::string get_city_name() { return city_name; }
    int get_star() { return star_rating; }

private:
    void set_rooms_info(RoomsInfo rooms_info_);
    void set_which_rooms(int count, int price, char room_id);
    char which_room(std::string type);
    int find_rating_by_username(std::string username);
    double calculate_location_avg();
    double calculate_cleanliness_avg();
    double calculate_staff_avg();
    double calculate_facilities_avg();
    double calculate_value_for_money_avg();
    double calculate_overall_avg();
    
    void print_hotel_info();
    void print_num_of_each_room();
    void print_price_of_each_room();
    
    std::string unique_id;
    std::string property_name;
    int star_rating;
    std::string hotel_overview;
    std::string property_amenities;
    std::string city_name;
    std::pair<double, double> coordinates;
    std::string image_url;
    RoomsInfo room_details;
    RoomsVec rooms_info;
    CommentsVec comments_info;
    RatingVec ratings_info;
};

typedef std::vector<Hotel*> HotelVec;

#endif