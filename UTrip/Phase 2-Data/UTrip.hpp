#ifndef UTRIP_HPP
#define UTRIP_HPP

#include <sstream>

#include "Hotel.hpp"
#include "User.hpp"
#include "Filter.hpp"

class UTrip
{
public:
    void read_infos(std::string hotels_path, std::string ratings_path);

    void sign_up(std::stringstream& line);
    void login(std::stringstream& line);
    void logout();

    void increase_wallet(std::stringstream& line);
    void get_wallet_transactions(std::stringstream& line);

    void get_reserve_infos(std::stringstream& line);
    void show_user_reserves();
    void delete_reserves(std::stringstream& line);

    void show_hotels_info();
    void show_hotel_info(std::stringstream& line);
    
    void add_filter(std::stringstream& line);
    void delete_filters();

    void add_comment(std::stringstream& line);
    void show_hotel_comments(std::stringstream& line);
    void add_rating(std::stringstream& line);
    void show_hotel_ratings(std::stringstream& line);

    void reset_default_price_filter(std::stringstream& line);
    void sort_hotels(std::stringstream& line);
    void reset_rating_weights(std::stringstream& line);
    void show_manual_weights();
    void show_estimated_weights();

    void check_permission(std::string command);

private:
    void read_hotels_info(std::string file_path);
    void read_ratings_info(std::string file_path);

    std::vector<std::string> separate_line(std::string line);
    RoomsInfo separate_rooms_info(std::vector<std::string> separated_infos);
    std::vector<std::string> get_command_infos(std::stringstream& line, 
            std::vector<std::string> lables);

    void set_new_user(std::vector<std::string> infos);
    void set_login_info(std::vector<std::string> infos);
    void check_login_info(std::string email, std::string password);
    void check_not_found(std::string id_);

    ReserveRequest make_reserve_request_struct(std::vector<std::string> infos);
    void reserve_rooms(ReserveRequest info, std::vector<Room*> rooms);

    void add_city_filter(std::stringstream& line);
    std::string get_filter_city(std::stringstream& line);
    void add_room_filter(std::stringstream& line);
    void add_star_period_filter(std::stringstream& line);
    void add_price_filter(std::stringstream& line);
    void check_starts_period(std::vector<std::string> infos);
    void check_price_period(std::vector<std::string> infos);
    HotelVec apply_filters();

    void check_ratings(std::vector<std::string> ratings);

    void check_default_price_filter();
    
    void which_sort();
    void check_sort();
    void sort_by_id();
    void sort_by_name();
    void sort_by_star(std::string order);
    void sort_by_city(std::string order);
    void sort_by_standard_room(std::string order);
    void sort_by_deluxe_room(std::string order);
    void sort_by_luxury_room(std::string order);
    void sort_by_premium_room(std::string order);
    void sort_by_avg_price(std::string order);
    void sort_by_ratings(std::string order);
    
    void active_weights(std::vector<std::string> infos);
    void check_weights(std::vector<std::string> infos);
    void deactivate_weights();

    void manual_or_estimated_sort();
    RatingVec set_user_ratings();
    void set_public_ratings(std::vector<double> manual_weights_);


    std::vector<double> calculate_estimated_weights(RatingVec user_ratings);

    std::vector<double> calculate_new_derivatives(std::vector<double> guessed_weights, 
            std::vector<double> derivatives, RatingVec user_ratings_);

    std::vector<double> check_weight_limits(std::vector<double> weights_, 
            std::vector<double> derivative);

    std::vector<double> generate_random_weights();
    double random_number();
    double overall_satisfaction(Rating* rating, std::vector<double> weights);
    std::vector<double> make_vector_of_rating(Rating* rating);
    double error_function(Rating* rating, std::vector<double> weights);
    double derivative_error_function(Rating* rating, std::vector<double> weights, int i);
    void delete_manual_weights();

    Hotel* find_hotel_by_id(std::string id);
    void check_bad_request(std::vector<std::string> infos);
    void check_duplication(std::vector<std::string> infos);

    int default_price_filter = ON;
    std::vector<std::string> sort_type{EMPTY_, EMPTY_};
    User* logged_in_user = NULL;
    HotelVec hotels_info;
    UserVec users_info;
    FilterVec filters{NULL, NULL, NULL, NULL, NULL};
    std::vector<double> manual_weights{ZERO, ZERO, ZERO, ZERO, ZERO};
};

#endif