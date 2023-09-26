#ifndef DEFINES_HPP
#define DEFINES_HPP



#include <vector>
#include <string>

#define COMMA ','
#define STRAIGHT_LINE '|'

#define UNFILTERED 0
#define FILTERED 1
#define UNIQUE_ID 0
#define PROPERTY_NAME 1
#define STAR_RATING 2
#define OVERVIEW 3
#define AMENITIES 4
#define CITY 5
#define LATITUDE 6
#define LONGITUDE 7
#define IMAGE_URL 8
#define FIRST_ROOM 9
#define FIRST_PRICE 13

#define STAR_ "star: "
#define OVERVIEW_ "overview: "
#define AMENITIES_ "amenities: "
#define CITY__ "city: "
#define LATITUDE_ "latitude: "
#define LONGITUDE_ "longitude: "
#define ROOMS_ "#rooms: "
#define PRICE_ "price: "

#define COLON ": "
#define QUESTION_MARK "?"


#define NUM_OF_ROOMS 4

#define STANDARD_S 's'
#define DELUXE_D 'd'
#define LUXURY_L 'l'
#define PREMIUM_P 'p'

#define STANDARD "standard"
#define DELUXE "deluxe"
#define LUXURY "luxury"
#define PREMIUM "premium"

#define STANDARD_ 0
#define DELUXE_ 1
#define LUXURY_ 2
#define PREMIUM_ 3

#define POST_ "POST"
#define GET_ "GET"
#define DELETE "DELETE"
#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define CONFIRM_PASSWORD "confirm_password"
#define HOTEL "hotel"
#define TYPE "type"
#define QUANTITY "quantity"
#define CHECK_IN "check_in"
#define CHECK_OUT "check_out"
#define SIGNUP "signup"
#define LOGIN "login"
#define LOGOUT "logout"
#define WALLET "wallet"
#define RESERVES "reserves"
#define HOTELS "hotels"
#define FILTERS "filters"
#define COMMENTS "comments"
#define RATINGS "ratings"
#define DEFAULT_PRICE_FILTER "default_price_filter"

#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value_for_money"
#define VALUE_FOR_MONEY_ "value for money"
#define OVERALL_RATING "overall_rating"
#define OVERALL_RATING_ "overall rating"
 
#define MIN_STAR "min_star"
#define MAX_STAR "max_star"
#define MIN_STAR_ 0
#define MAX_STAR_ 1

#define MIN_PRICE "min_price"
#define MAX_PRICE "max_price"
#define MIN_PRICE_ 0
#define MAX_PRICE_ 1

#define CITY_ "city"
#define FILTER_ATTENTION "* Results have been filtered by the default price filter."

#define BAD_REQUEST "Bad Request\n"
#define NOT_FOUND "Not Found\n"
#define PERMISSION_DENIED "Permission Denied\n"
#define OK "OK"
#define EMPTY "Empty"
#define EMPTY_ ""
#define NOT_ENOUGH_CREDIT "Not Enough Credit\n"
#define NOT_ENOUGH_ROOM "Not Enough Room\n"
#define NO_RATING "No Rating\n"
#define AMOUNT "amount"
#define COUNT "count"
#define COMMENT "comment"
#define WHITE_SPACE ' '
#define ROOM "room"
#define COST "cost"
#define ID_ "id"

#define HOTELS_FILE_PATH 1
#define RATINGS_FILE_PATH 2
#define WEIGHTS_ 5
#define HUNDRED 100

#define CITY_FILTER_ 0
#define STAR_FILTER_ 1
#define PRICE_FILTER_ 2
#define ROOM_FILTER_ 3
#define DEFAULT_FILTER 4

#define OFF 0
#define ON 1
#define FILTERS_SIZE 5
#define NOT_FOUND_ -1
#define ONE 1.0
#define FIVE 5.0
#define ZERO 0
#define TEN 10
#define TWO 2.0

#define TRUE "true"
#define FALSE "false"
#define SORT "sort"
#define PROPERTY "property"
#define ORDER "order"
#define MANUAL_WEIGHTS "manual_weights"
#define ACTIVE "active"

#define ASCENDING "ascending"
#define DESCENDING "descending"

#define NAME "name"
#define STAR_RATING_ "star_rating"
#define STANDARD_ROOM_PRICE "standard_room_price"
#define DELUXE_ROOM_PRICE "deluxe_room_price"
#define LUXURY_ROOM_PRICE "luxury_room_price"
#define PREMIUM_ROOM_PRICE "premium_room_price"
#define AVERAGE_ROOM_PRICE "average_room_price"
#define RATING_PERSONAL "rating_personal"

#define INSUFFICIENT_RATINGS "Insufficient Ratings"
#define ESTIMATED_WEIGHTS "estimated_weights"
#define RATINGS_ 6

#define USERNAME_ 0
#define EMAIL_ 1
#define PASSWORD_ 2
#define CONFIRM_PASSWORD_ 3
#define EOF_ '\0'
#define LOGIN_PAGE "/"
#define SIGN_UP_PAGE "/signup"
#define HOME_PAGE "/home"
#define HOTEL_DETAILS_PAGE "/hotelDetails"
#define FINANCIAL_PAGE "/financial"
#define LOG_OUT_PAGE "/logout"
#define LOGIN_PAGE_CODE_PATH "html_codes/LoginPage.html"
#define SIGN_UP_PAGE_CODE_PATH "html_codes/SignupPage.html"
#define CONTENT_TYPE "Content-Type"
#define TEXT_TYPE "text/html"
#define INVALID_USERNAME_PASSWORD "Username and password is invalid!"
#define DIFFRENT_PASSWORD "Sorry, Passowrds are diffrent!"
#define USED_EMAIL "Sorry, This email is already have an account!"
#define TAKEN_USERNAME "Sorry, This username is already taken!"

const std::vector<std::string> rooms_lables{STANDARD, DELUXE, LUXURY, PREMIUM};


typedef struct
{
    int check_in;
    int check_out;
}ReserveDate;

typedef struct
{
    std::vector<int> num_of_each_room;
    std::vector<int> price_of_each_room;
}RoomsInfo;

typedef struct
{ 
    std::string hotel_id, room_type; 
    int quantity;
    ReserveDate reserve_date;
}ReserveRequest;



#endif
