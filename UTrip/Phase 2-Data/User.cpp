#include "User.hpp"

#include <cmath>
#include <iomanip>

using namespace std;

User::User(string email_, string username_, string password_)
{
    hash<string> hash_password;
    email = email_;
    username = username_;
    password = hash_password(password_);
    cash.push_back(ZERO);
}

void User::print_transactions(int count)
{
    for (int i = 0; i < count; i++)
    {
        if (i == cash.size())
            break;
        cout << int(round(cash[i])) << endl;
    }
}

void User::set_reserve_info(ReserveRequest reserve_info_, vector<Room*> rooms)
{      
    int cost = rooms[0]->calculate_cost(rooms.size(), reserve_info_.reserve_date);
    if (cash[0] < cost)
        throw(NotEnoughCredit());
    increase_wallet(-1 * cost);
    ReserveInfo info;
    info.room_type = reserve_info_.room_type;
    info.date = reserve_info_.reserve_date;
    info.hotel_id = reserve_info_.hotel_id;
    info.cost = cost;
    info.rooms = rooms;
    reserves_info.push_back(std::make_pair(info, total_reserves + 1));
    total_reserves++;
}

void User::delete_reserve(int id)
{
    check_id(id);
    for (int i = 0; i < reserves_info[find_reserve_by_id(id)].first.rooms.size(); i++)
    reserves_info[find_reserve_by_id(id)].first.rooms[i]->
                delete_reserve_date(reserves_info[find_reserve_by_id(id)].first.date);
    increase_wallet(reserves_info[find_reserve_by_id(id)].first.cost / 2);
    reserves_info.erase(reserves_info.begin() + id - 1);
}

int User::find_reserve_by_id(int id)
{
    for (int i = 0; i < reserves_info.size(); i++)
        if (reserves_info[i].second == id)
            return i;
    return NOT_FOUND_;
}

void User::check_id(int id)
{
    for (int i = 0; i < reserves_info.size(); i++)
        if (reserves_info[i].second == id)
            return;
    throw(NotFound());
}

void User::print_reserves_info()
{
    if (reserves_info.size() == 0)
        cout << EMPTY << endl;
    for (int i = reserves_info.size() - 1; i >= 0; i--)
        cout << ID_ << COLON << reserves_info[i].second << WHITE_SPACE << HOTEL << COLON
             << reserves_info[i].first.hotel_id << WHITE_SPACE << ROOM << COLON
             << reserves_info[i].first.room_type << WHITE_SPACE << QUANTITY << COLON 
             << reserves_info[i].first.rooms.size() << WHITE_SPACE << COST << COLON
             << reserves_info[i].first.cost << WHITE_SPACE << CHECK_IN << WHITE_SPACE
             << reserves_info[i].first.date.check_in << WHITE_SPACE << CHECK_OUT << WHITE_SPACE
             << reserves_info[i].first.date.check_out << endl;
}

double User::calculate_rooms_avg_price()
{
    double sum = 0;
    int count = 0;
    for (int i = 0; i < reserves_info.size(); i++)
    {
       sum += (reserves_info[i].first.cost / 
            (reserves_info[i].first.date.check_out - 
                    reserves_info[i].first.date.check_in + 1));
       count += reserves_info[i].first.rooms.size();
    }
    return sum / count;
}

double User::calculate_standard_deviation()
{
    double sum = 0;
    double count = 0;
    double avg_price = calculate_rooms_avg_price();
    
    for (int i = 0; i < reserves_info.size(); i++)
        for (int j = 0; j < reserves_info[i].first.rooms.size(); j++)
        {
            sum += pow(reserves_info[i].first.rooms[j]->get_price() - avg_price, 2);
            count++;
        }
    return sqrt(sum / (count - 1));
}