#include "LoginAndLogoutHandler.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Response *ShowLoginPage::callback(Request *request)
{
    if (trip->find_user(request->getSessionId()) >= ZERO)
        return Response::redirect(HOME_PAGE);

    Response *response = new Response;
    response->setHeader(CONTENT_TYPE, TEXT_TYPE);
    
    fstream login_file(login_file_path);
    string text;
    getline(login_file, text, EOF_);

    response->setBody(text);
    return response;   
}

Response *Login::callback(Request *request) 
{
    trip->login(request->getBodyParam(USERNAME), request->getBodyParam(PASSWORD));
    Response *response = Response::redirect(HOME_PAGE);
    response->setSessionId(request->getBodyParam(USERNAME));
    return response;
}

Response *Logout::callback(Request *request)
{
    Response *response = new Response;
    trip->logout(request->getSessionId());
    response->setSessionId(EMPTY_);
    return Response::redirect(LOGIN_PAGE);
}