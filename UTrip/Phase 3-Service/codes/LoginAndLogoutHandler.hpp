#ifndef LOGIN_AND_LOGOUT_HANDLER_HPP
#define LOGIN_AND_LOGOUT_HANDLER_HPP

#include "../server/server.hpp"
#include "UTrip.hpp"
#include <iostream>

class ShowLoginPage : public RequestHandler
{
public:
    ShowLoginPage(std::string login_file_path_, UTrip* trip_) : RequestHandler() 
            { login_file_path = login_file_path_; trip = trip_; };
    Response *callback(Request *);
private:
    std::string login_file_path;
    UTrip* trip;
};

class Login : public RequestHandler 
{
public:
    Login(UTrip* trip_) : RequestHandler() { trip = trip_; }
	Response *callback(Request *);
private:
    UTrip* trip;
};

class Logout : public RequestHandler
{
public:
    Logout(UTrip* trip_) : RequestHandler() { trip = trip_; }
    Response *callback(Request *);
private:
    UTrip* trip;
};

#endif
