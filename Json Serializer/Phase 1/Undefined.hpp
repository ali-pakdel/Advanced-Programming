#ifndef UNDEFINED_HPP
#define UNDEFINED_HPP

#include <exception>

#include "Defines.hpp"

class Undefined : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return UNDEFINED_ERROR;
    }
};

#endif