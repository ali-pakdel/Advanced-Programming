#include "StarPeriodFilter.hpp"

using namespace std;

StarPeriodFilter::StarPeriodFilter(vector<string> stars_) 
        : Filter()
{
    stars.first = stod(stars_[MIN_STAR_]);
    stars.second = stod(stars_[MAX_STAR_]);
}

HotelVec StarPeriodFilter::filterList(HotelVec hotels_info_)
{
    HotelVec temp;
    for (int i = 0; i < hotels_info_.size(); i++)
        if (hotels_info_[i]->get_star() >= stars.first &&
            hotels_info_[i]->get_star() <= stars.second)
            temp.push_back(hotels_info_[i]);
    return temp;
}

void StarPeriodFilter::replace_filters(vector<string> infos)
{
    stars.first = stod(infos[MIN_STAR_]);
    stars.second = stod(infos[MAX_STAR_]);
}