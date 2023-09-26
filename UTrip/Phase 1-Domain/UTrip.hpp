#ifndef UTRIP_HPP
#define UTRIP_HPP

#include <sstream>

#include "Hotel.hpp"
#include "User.hpp"
#include "Filter.hpp"

class UTrip
{
public:
    void read_hotels_info(std::string file_path);

    void sign_up(std::stringstream& line);
    void login(std::stringstream& line);
    void logout();
    void increase_wallet(std::stringstream& line);
    void get_wallet_transactions(std::stringstream& line);
    void get_reserve_infos(std::stringstream& line);
    void show_hotels_info();
    void show_hotel_info(std::stringstream& line);
    void delete_reserves(std::stringstream& line);
    void delete_filters();
    void add_comment(std::stringstream& line);
    void show_hotel_comments(std::stringstream& line);
    void add_rating(std::stringstream& line);
    void show_hotel_ratings(std::stringstream& line);
    void add_filter(std::stringstream& line);
    void show_user_reserves();

    void check_permission(std::string command);

private:
    std::vector<std::string> separate_line(std::string line);
    RoomsInfo separate_rooms_info(std::vector<std::string> separated_infos);
    std::vector<std::string> get_command_infos(std::stringstream& line, 
            std::vector<std::string> lables);

    void set_new_user(std::vector<std::string> infos);

    void set_login_info(std::vector<std::string> infos);
    void check_login_info(std::string email, std::string password);

    ReserveRequest make_reserve_request_struct(std::vector<std::string> infos);
    void reserve_rooms(ReserveRequest info, std::vector<Room*> rooms);

    void add_city_filter(std::stringstream& line);
    std::string get_filter_city(std::stringstream& line);
    void add_room_filter(std::stringstream& line);
    void add_star_period_filter(std::stringstream& line);
    void add_price_filter(std::stringstream& line);

    HotelVec apply_filters();

    std::vector<std::string> sort_ratings(std::vector<std::pair<std::string, std::string>> infos);
    int find_hotel_by_id(std::string id);
    void check_bad_request(std::vector<std::string> infos);
    void check_duplication(std::vector<std::string> infos);
    void check_ratings(std::vector<std::string> ratings);
    void check_hotel_id(std::string id);
    void check_starts_period(std::vector<std::string> infos);
    void check_price_period(std::vector<std::string> infos);
    
    User* logged_in_user = NULL;
    HotelVec hotels_info;
    UserVec users_info;
    FilterVec filters{NULL, NULL, NULL, NULL};
};

#endif