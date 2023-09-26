#ifndef HOME_PAGE_HANDLER_HPP
#define HOME_PAGE_HANDLER_HPP

#include "../server/server.hpp"
#include "UTrip.hpp"

class FilterHotels : public RequestHandler
{
public:
    FilterHotels(UTrip* trip_) : RequestHandler() { trip = trip_; }
	Response *callback(Request *);
private:
    UTrip* trip;
};

class ShowHomePage : public RequestHandler
{
public:
    ShowHomePage(UTrip* trip_) : RequestHandler() { trip = trip_; }
    Response *callback(Request *);
private:
    UTrip* trip;
};
#endif