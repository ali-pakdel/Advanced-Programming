#include "HotelDetailsHandler.hpp"

using namespace std;

Response *ShowHotelDetails::callback(Request *request)
{
    if (trip->find_user(request->getSessionId()) == NOT_FOUND_)
        return Response::redirect(LOGIN_PAGE);
    
    Response *response = new Response;
    response->setHeader(CONTENT_TYPE, TEXT_TYPE);
    
    Hotel* hotel = trip->get_hotel(request->getQueryParam(ID_));
    ostringstream body;
    body
        << "<html>" << endl
        << "    <head><title>Hotel Details</title></head>" << endl
        << "    <body>" << endl
        << "        <a href='home'>Home</a> <a href='financial'>Financial</a> <a href='logout'>Logout</a> <br/> <br/>" << endl
        << "        <img src=" <<hotel->get_img_url() << " width='200' height='150'>" << endl
        << "        <p><b>Name: </b>" << hotel->get_name() << "</p>" << endl
        << "        <p><b>Overview: </b>" << hotel->get_overview() << "</p>" << endl
        << "        <p><b>Amenities: </b>" << hotel->get_amenities() << "</p>" << endl
        << "        <p><b>Star Rating: </b>" << hotel->get_star() << "</p>" << endl
        << "        <p><b>City: </b>" << hotel->get_city_name() << "</p>" << endl
        << "        <table border='3'>" << endl
        << "            <tr>" << endl
        << "                <th>Room Type</th>" << endl
        << "                <th>Price</th>" << endl
        << "                <th>Number</th>" << endl
        << "            </tr>" << endl;
    for (int i = 0; i < NUM_OF_ROOMS; i++)
    {
        body
            << "            <tr>" << endl
            << "                <td>" << rooms_lables[i] << "</td>" << endl
            << "                <td>" << hotel->get_room_details().price_of_each_room[i] << "</td>" << endl
            << "                <td>" << hotel->get_room_details().num_of_each_room[i] << "</td" << endl
            << "            </tr>" << endl;
    }
    body
        << "        </table>" << endl
        << "    </body>" << endl
        << "</html>" << endl;

    response->setBody(body.str());
    return response;
} 