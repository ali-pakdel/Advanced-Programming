#ifndef DEFAULT_PRICE_FILTER_HPP
#define DEFAULT_PRICE_FILTER_HPP

#include "Filter.hpp"

class DefaultPriceFilter : public Filter
{
public:
    DefaultPriceFilter(double standard_deviation_, double user_rooms_avg_);
    HotelVec filterList(HotelVec hotels_info_);
    void replace_filters(std::vector<std::string> info) {}
private:
    double standard_deviation;
    double user_rooms_avg;
};

#endif