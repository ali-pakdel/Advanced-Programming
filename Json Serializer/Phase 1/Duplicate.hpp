#ifndef DUPLICATE_HPP
#define DUPLICATE_HPP

#include <exception>

#include "Defines.hpp"

class Duplicate : std::exception
{
public:
    virtual const char* what() const throw()
    {
        return DUPLICATE_ERROR;
    }
};

#endif