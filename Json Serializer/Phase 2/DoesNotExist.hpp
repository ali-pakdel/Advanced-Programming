#ifndef DOES_NOT_EXIST_HPP
#define DOES_NOT_EXIST_HPP

#include <exception>

#include "Defines.hpp"

class DoesNotExist : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return DOES_NOT_EXIST_ERROR;
    }
};

#endif