#ifndef INVALID_HPP
#define INVALID_HPP

#include <exception>

#include "Defines.hpp"

class Invalid : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return SAME_INVALID;
    }
};

#endif