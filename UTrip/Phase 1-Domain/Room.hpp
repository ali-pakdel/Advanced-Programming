#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>
#include <string>

#include "Defines.hpp"

class Room
{
public:
    Room(std::string room_id_, int price_);
    std::string get_id() { return room_id; }
    bool is_avaiable(ReserveDate date);
    bool is_interference(ReserveDate date1, ReserveDate date2);
    void set_reserve_date(ReserveDate date);
    void delete_reserve_date(ReserveDate date);
    int calculate_cost(int count, ReserveDate date);
private:
    std::string room_id;
    int price;
    std::vector<ReserveDate> reserve_dates;
};

typedef struct
{
    std::string hotel_id;
    std::string room_type;
    std::vector<Room*> rooms;
    ReserveDate date;
    int cost;
}ReserveInfo;

typedef std::vector<Room*> RoomsVec;

#endif