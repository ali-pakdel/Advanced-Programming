#include "FinancialHandler.hpp"

using namespace std;

Response *ShowFinancialPage::callback(Request *request)
{
    if (trip->find_user(request->getSessionId()) == NOT_FOUND_)
        return Response::redirect(LOGIN_PAGE);

    Response *response = new Response;
    response->setHeader(CONTENT_TYPE, TEXT_TYPE);
    
    User* user = trip->get_user(request->getSessionId());
    ostringstream body;
    body
        << "<html>" << endl
        << "    <body>" << endl
        << "        <a href='home'>Home</a> <a href='financial'>Financial</a> <a href='logout'>Logout</a> <br/> <br/>" << endl
        << "        <h3>Financial Account</h3> <br/>" << endl
        << "        <p><b>Wallet Credit: </b>" << user->get_credit() << "</p><br/><br/>" << endl
        << "        <strong>Increase Wallet</strong><br/><br/>"
        << "        <form action='financial' method='POST'>" << endl
        << "            <label for='amount_'><b>Amount</b></label>" << endl
        << "            <input type='text' placeholder='Enter Amount' name='amount'> <br/>" << endl
        << "            <button type='save'>Submit</button>"
        << "        </from>" << endl
        << "    </body>" << endl
        << "</html>" << endl;
    response->setBody(body.str());
    return response;
}

Response *IncreaseWallet::callback(Request *request)
{
    double amount = stod(request->getBodyParam(AMOUNT));
    trip->get_user(request->getSessionId())->increase_wallet(amount);
    return Response::redirect(FINANCIAL_PAGE);
}