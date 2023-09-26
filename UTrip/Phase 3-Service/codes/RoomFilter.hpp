#ifndef ROOM_FILTER_HPP
#define ROOM_FILTER_HPP

#include "Filter.hpp"

class RoomFilter : public Filter
{
public:
    RoomFilter(std::vector<std::string> infos);

    HotelVec filterList(HotelVec hotels_info_);
    void replace_filters(std::vector<std::string> infos);
private:
    ReserveRequest req;
};

#endif