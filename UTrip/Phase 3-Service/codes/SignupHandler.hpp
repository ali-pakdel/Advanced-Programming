#ifndef SIGN_UP_HANDLER_HPP
#define SIGN_UP_HANDLER_HPP

#include "../server/server.hpp"
#include "UTrip.hpp"
#include <iostream>

class ShowSignupPage : public  RequestHandler
{
public:
    ShowSignupPage(std::string signup_file_path_, UTrip* trip_) : RequestHandler() 
            { signup_file_path = signup_file_path_; trip = trip_; }
    Response *callback(Request *);
private:
    std::string signup_file_path;
    UTrip* trip;
};

class SignUp : public RequestHandler
{
public:
    SignUp(UTrip* trip_) : RequestHandler() { trip = trip_; }
    Response *callback(Request *);
private:
    UTrip* trip;
};

#endif