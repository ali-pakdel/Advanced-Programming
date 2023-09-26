#include "HomePageHandler.hpp"
#include <sstream>

using namespace std;

Response *ShowHomePage::callback(Request *request)
{  
    if (trip->find_user(request->getSessionId()) == NOT_FOUND_)
        return Response::redirect(LOGIN_PAGE);

    Response *response = new Response;
    response->setHeader(CONTENT_TYPE, TEXT_TYPE);
    
    HotelVec hotels_info = trip->apply_filters();
    ostringstream body;
    body
        << "<html>" << endl
        << "    <head><title>UTrip</title></head>" << endl
        << "    <body>" << endl
        << "        <a href='home'>Home</a> <a href='financial'>Financial</a> <a href='logout'>Logout</a> <br/> <br/>" << endl
        << "        <form action='home' method='POST'>" << endl
        << "            <label for='min'><b>Min Star</b></label>" << endl
        << "            <input type='number' placeholder='Enter Min Star' name='min_star' step='any'>" << endl
        << "            <label for='max'><b>Max Star</b></label>" << endl
        << "            <input type='number' placeholder='Enter Max Star' name='max_star' step='any'>" << endl
        << "            <button type='submit'>Filter</button> </br>" << endl
        << "        </form> </br>" << endl
        << "        <table border='2'>" << endl
        << "            <tr>" << endl
        << "                <th>&nbsp;</th>" << endl
        << "                <th>Name</th>" << endl
        << "                <th>City</th>" << endl
        << "                <th>Star Rating</th>" << endl
        << "                <th>Image</th>" << endl
        << "                <th>&nbsp;</th>" << endl
        << "            </tr>" << endl;

    for (int i = 0; i < hotels_info.size(); i++)
     {
        body
            << "            <tr>" << endl
            << "                <td>" << i + 1 << "</th>" << endl
            << "                <td>" << hotels_info[i]->get_name() << "</td>" << endl
            << "                <td>" << hotels_info[i]->get_city_name() << "</td>" << endl
            << "                <td>" << hotels_info[i]->get_star() << "</td>" << endl
            << "                <td><img src=" << hotels_info[i]->get_img_url() << " width='200' height='150'></td>" << endl
            << "                <td><a href='hotelDetails?id=" << hotels_info[i]->get_id() << "'>Details</a></td>" << endl
            << "            </tr>" << endl;
    }
    body
        << "        </table>" << endl
        << "    </body>" << endl
        << "</html>" << endl;

    response->setBody(body.str());
    return response;    
}


Response *FilterHotels::callback(Request *request)
{
    if (request->getBodyParam(MIN_STAR).size() != ZERO && 
            request->getBodyParam(MAX_STAR).size() != ZERO)
        trip->add_star_filter(request->getBodyParam(MIN_STAR), request->getBodyParam(MAX_STAR));
    return Response::redirect(HOME_PAGE);
}
