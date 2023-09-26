#ifndef STAR_PERIOD_FILTER_HPP
#define STAR_PERIOD_FILTER_HPP

#include "Filter.hpp"

class StarPeriodFilter : public Filter
{
public:
    StarPeriodFilter(std::vector<std::string> stars_);
    
    HotelVec filterList(HotelVec hotels_info_);
    void replace_filters(std::vector<std::string> infos);
private:
    std::pair<int, int> stars;
};

#endif