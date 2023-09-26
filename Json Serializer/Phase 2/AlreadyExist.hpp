#ifndef ALREADY_EXIST_HPP
#define ALREADY_EXIST_HPP

#include <exception>

#include "Defines.hpp"

class AlreadyExist : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return ALREADY_EXIST_ERROR;
    }
};

#endif