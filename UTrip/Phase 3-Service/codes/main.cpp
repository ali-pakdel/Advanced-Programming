#include <iostream>
#include "Functions.hpp"
#include "LoginAndLogoutHandler.hpp"
#include "SignupHandler.hpp"
#include "HomePageHandler.hpp"
#include "HotelDetailsHandler.hpp"
#include "FinancialHandler.hpp"

#include "../server/server.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    try {
        Server server(8080);
        UTrip trip(argv[HOTELS_FILE_PATH]);
        server.get(LOGIN_PAGE, new ShowLoginPage(LOGIN_PAGE_CODE_PATH, &trip));
        server.post(LOGIN_PAGE, new Login(&trip));

        server.get(SIGN_UP_PAGE, new ShowSignupPage(SIGN_UP_PAGE_CODE_PATH, &trip));
        server.post(SIGN_UP_PAGE, new SignUp(&trip));

        server.get(HOME_PAGE, new ShowHomePage(&trip));
        server.post(HOME_PAGE, new FilterHotels(&trip));
        
        server.get(HOTEL_DETAILS_PAGE, new ShowHotelDetails(&trip));

        server.get(FINANCIAL_PAGE, new ShowFinancialPage(&trip));
        server.post(FINANCIAL_PAGE, new IncreaseWallet(&trip));

        server.get(LOG_OUT_PAGE, new Logout(&trip));
        
        server.run();
    } catch (Server::Exception error) {
        cerr << error.getMessage() << endl;
    }
}

