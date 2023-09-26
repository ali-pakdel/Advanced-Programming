#ifndef USER_HPP
#define USER_HPP

#include <vector>
#include <string>
#include <iostream>

#include "Room.hpp"
#include "NotEnoughCredit.hpp"
#include "NotFound.hpp"

class User
{
public:
    User(std::string email_, std::string username_, std::string password_);

    void increase_wallet(double cash_) { cash.insert(cash.begin(), (cash[0] + cash_)); }
    void print_transactions(int count);
    void set_reserve_info(ReserveRequest reserve_info_, std::vector<Room*> rooms);
    void delete_reserve(int id);
    void print_reserves_info();

    std::string get_email() { return email; }
    unsigned long long int get_password() { return password; }
    std::string get_username() { return username; }
private:

    int find_reserve_by_id(int id);
    void check_id(int id);
    std::string email;
    std::string username;
    unsigned long long int password;
    std::vector<double> cash;
    std::vector<std::pair<ReserveInfo, int>> reserves_info;
    int total_reserves = 0;
};

typedef std::vector<User*> UserVec;

#endif