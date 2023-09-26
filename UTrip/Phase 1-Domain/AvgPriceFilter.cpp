#include "AvgPriceFilter.hpp"

using namespace std;

AvgPriceFilter::AvgPriceFilter(std::vector<std::string> prices_) 
        : Filter() 
{
    prices.first = stod(prices_[0]);
    prices.second = stod(prices_[1]);
}

HotelVec AvgPriceFilter::filterList(HotelVec hotels_info_)
{
    HotelVec temp;
    for (int i = 0; i < hotels_info_.size(); i++)
        if (hotels_info_[i]->calculate_average_price() >= prices.first &&
                hotels_info_[i]->calculate_average_price() <= prices.second)
            temp.push_back(hotels_info_[i]);
    return temp;
}

void AvgPriceFilter::replace_filters(vector<string> infos)
{
    prices.first = stod(infos[MIN_PRICE_]);
    prices.second = stod(infos[MAX_PRICE_]);
}