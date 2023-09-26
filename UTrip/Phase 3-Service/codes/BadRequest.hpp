#ifndef BAD_REQUEST_HPP
#define BAD_REQUEST_HPP

#include <exception>
#include "Defines.hpp"

class BadRequest : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return BAD_REQUEST;
    }
};

#endif