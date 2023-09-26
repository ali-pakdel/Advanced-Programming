#include "Room.hpp"
#include <iostream>

using namespace std;

Room::Room(string room_id_, int price_)
{
    room_id = room_id_;
    price = price_;
}

bool Room::is_available(ReserveDate date)
{
    for (int i = 0; i < reserve_dates.size(); i++)
        if (is_interference(reserve_dates[i], date))
            return false;
    return true;
}

bool Room::is_interference(ReserveDate date1, ReserveDate date2)
{
    if (date1.check_in > date2.check_out || date1.check_out < date2.check_in)
        return false;
    return true;
}

void Room::set_reserve_date(ReserveDate date)
{
    reserve_dates.push_back(date);
    cout << room_id << WHITE_SPACE;
}

void Room::delete_reserve_date(ReserveDate date)
{
    for (int i = 0; i < reserve_dates.size(); i++)
        if (date.check_in == reserve_dates[i].check_in && 
                date.check_out == reserve_dates[i].check_out)
                reserve_dates.erase(reserve_dates.begin() + i);
}

int Room::calculate_cost(int count, ReserveDate date)
{
    return price * count * (date.check_out - date.check_in + 1);
}
