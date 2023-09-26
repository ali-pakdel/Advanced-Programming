#include "SignupHandler.hpp"

#include <sstream>
#include <fstream>

using namespace std;

Response *ShowSignupPage::callback(Request *request)
{
    if (trip->find_user(request->getSessionId()) >= ZERO)
        return Response::redirect(HOME_PAGE);

    Response *response = new Response;
    response->setHeader(CONTENT_TYPE, TEXT_TYPE);
    
    fstream signup_file(signup_file_path);
    string text;
    getline(signup_file, text, EOF_);
    
    response->setBody(text);
    return response;       
}

Response *SignUp::callback(Request *request)
{
    vector<string> signup_infos{request->getBodyParam(USERNAME),
            request->getBodyParam(EMAIL), request->getBodyParam(PASSWORD),
            request->getBodyParam(CONFIRM_PASSWORD)};
    trip->sign_up(signup_infos);

    return Response::redirect(LOGIN_PAGE);
}