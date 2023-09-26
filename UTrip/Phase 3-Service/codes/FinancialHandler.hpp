#ifndef FINANCIAL_HANDLER_HPP
#define FINANCIAL_HANDLER_HPP

#include "../server/server.hpp"
#include "UTrip.hpp"

class ShowFinancialPage : public RequestHandler
{
public:
    ShowFinancialPage(UTrip* trip_) : RequestHandler() { trip = trip_; }
    Response *callback(Request *);
private:
    UTrip* trip;
};

class IncreaseWallet : public RequestHandler
{
public:
    IncreaseWallet(UTrip* trip_) : RequestHandler() { trip = trip_; }
    Response *callback(Request *);
private:
    UTrip* trip;
};

#endif