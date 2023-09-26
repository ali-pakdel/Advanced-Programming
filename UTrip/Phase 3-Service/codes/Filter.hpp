#ifndef FILTER_HPP
#define FILTER_HPP

#include "Hotel.hpp"

class Filter
{
public:
    virtual HotelVec filterList(HotelVec hotels_info_) = 0;
    virtual void replace_filters(std::vector<std::string> info) = 0;
private:
    //int on_or_off = OFF;
};

typedef std::vector<Filter*> FilterVec;

#endif