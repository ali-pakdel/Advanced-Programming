#include "RoomFilter.hpp"

using namespace std;

RoomFilter::RoomFilter(std::vector<std::string> infos) : Filter()
{
    req.hotel_id = EMPTY_;
    req.room_type = infos[0];
    req.quantity = stoi(infos[1]);
    req.reserve_date.check_in = stoi(infos[2]);
    req.reserve_date.check_out = stoi(infos[3]);
}

HotelVec RoomFilter::filterList(HotelVec hotels_info_)
{
    HotelVec temp;
    for (int i = 0; i < hotels_info_.size(); i++)
        if (hotels_info_[i]->check_rooms(req).size() == req.quantity)
            temp.push_back(hotels_info_[i]);
    return temp;
}

void RoomFilter::replace_filters(vector<string> infos)
{
    req.hotel_id = EMPTY_;
    req.room_type = infos[0];
    req.quantity = stoi(infos[1]);
    req.reserve_date.check_in = stoi(infos[2]);
    req.reserve_date.check_out = stoi(infos[3]);
}