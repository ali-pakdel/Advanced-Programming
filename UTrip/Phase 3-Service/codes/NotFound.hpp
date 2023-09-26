#ifndef NOT_FOUND_HPP
#define NOT_FOUND_HPP

#include <exception>
#include "Defines.hpp"

class NotFound : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return NOT_FOUND;
    }   
};
#endif