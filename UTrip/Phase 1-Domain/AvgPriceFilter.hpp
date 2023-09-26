#ifndef AVG_PRICE_FILTER_HPP
#define AVG_PRICE_FILTER_HPP

#include "Filter.hpp"

class AvgPriceFilter : public Filter
{
public:
    AvgPriceFilter(std::vector<std::string> prices_);

    HotelVec filterList(HotelVec hotels_info_);
    void replace_filters(std::vector<std::string> infos);
    
private:
    std::pair<double, double> prices;
};

#endif