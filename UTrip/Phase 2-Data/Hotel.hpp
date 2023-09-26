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
    void add_old_rating(std::vector<std::string> ratings);
    void add_new_rating(std::vector<std::string> ratings, 
            std::string username);
    void print_comments();
    void print_ratings();
    std::vector<Room*> find_rooms(ReserveRequest infos);
    double calculate_avg_price();

    std::string get_id() { return unique_id; }
    std::string get_city_name() { return city_name; }
    std::string get_name() { return property_name; }
    int get_star() { return star_rating; }
    RoomsInfo get_room_details() { return room_details; }
    double get_overall_rating() { return overall_rating; }

    Rating* find_user_rating(std::string username);
    void set_overall_ratings(std::vector<double> user_weights);

private:
    void set_rooms_info(RoomsInfo rooms_info_);
    void set_which_rooms(int count, int price, char room_id);
    char which_room(std::string type);
    Rating* find_rating_by_username(std::string username);
    double calculate_ratings_sum(std::vector<double> weights);
    double calculate_weights_sum(std::vector<double> weights);
    
    void print_hotel_info();
    void print_num_of_each_room();
    void print_price_of_each_room();
    
    int star_rating;
    double overall_rating = 0;
    std::string unique_id;
    std::string property_name;
    std::string hotel_overview;
    std::string property_amenities;
    std::string city_name;
    std::pair<double, double> coordinates;
    std::string image_url;
    RoomsInfo room_details;
    RoomsVec rooms_info;
    CommentsVec comments_info;
    RatingVec new_ratings;
    Rating* old_rating;
};

typedef std::vector<Hotel*> HotelVec;

#endif