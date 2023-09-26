#ifndef CITY_FILTER_HPP
#define CITY_FILTER_HPP

#include "Filter.hpp"

#include <iostream>
class CityFilter : public Filter
{
public:
    CityFilter(std::string city_name_);
    
    HotelVec filterList(HotelVec hotels_info_);
    void replace_filters(std::vector<std::string> infos);
private:
    std::string city_name;
};

#endif
