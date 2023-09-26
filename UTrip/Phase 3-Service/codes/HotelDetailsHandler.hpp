#ifndef HOTEL_DETAILS_HANDLER_HPP
#define HOTEL_DETAILS_HANDLER_HPP

#include "../server/server.hpp"
#include "UTrip.hpp"

class ShowHotelDetails : public RequestHandler
{
public:
    ShowHotelDetails(UTrip* trip_) : RequestHandler() { trip = trip_; }
    Response *callback(Request *);
private:
    UTrip* trip;
};

#endif