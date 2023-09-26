#include <algorithm>

#include "CityFilter.hpp"

using namespace std;

CityFilter::CityFilter(std::string city_name_) : Filter()
{
    city_name = city_name_;
}
bool is_same_city()
{

}
HotelVec CityFilter::filterList(HotelVec hotels_info_)
{
    HotelVec filtered_list; 
    for (int i = 0; i < hotels_info_.size(); i++)
        if (hotels_info_[i]->get_city_name() == city_name)
            filtered_list.push_back(hotels_info_[i]);
    
    return filtered_list;
}

void CityFilter::replace_filters(vector<string> infos)
{
    city_name = infos[0];   
}