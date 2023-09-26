#include "DefaultPriceFilter.hpp"

#include <cmath>
#include <iostream>
using namespace std;

DefaultPriceFilter::DefaultPriceFilter(double standard_deviation_, double user_rooms_avg_)
{
    standard_deviation = standard_deviation_;
    user_rooms_avg = user_rooms_avg_;
}

HotelVec DefaultPriceFilter::filterList(HotelVec hotels_info_)
{
    HotelVec temp;
    for (int i = 0; i < hotels_info_.size(); i++)
        if (abs(hotels_info_[i]->calculate_avg_price() - user_rooms_avg) <= TWO * standard_deviation)
            temp.push_back(hotels_info_[i]);
    return temp;
}