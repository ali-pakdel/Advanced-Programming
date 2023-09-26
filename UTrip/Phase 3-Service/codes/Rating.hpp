#ifndef RATING_HPP
#define RATING_HPP

#include <vector>
#include <string>

#include "Defines.hpp"

class Rating
{
public:
    Rating(std::vector<std::string> ratings);

    void replace_ratings(std::vector<std::string> ratings);

    std::string get_username() { return username; }
    double get_location() { return location; }
    double get_cleanliness() { return cleanliness; }
    double get_staff() { return staff; }
    double get_facilities() { return facilities; }
    double get_value_for_money() { return value_for_money; }
    double get_overall() { return overall; }

private:

    std::string username;
    double location;
    double cleanliness;
    double staff;
    double facilities;
    double value_for_money;
    double overall;
};

typedef std::vector<Rating*> RatingVec;
#endif