#ifndef NOT_ENOUGH_ROOM_HPP
#define NOT_ENOUGH_ROOM_HPP

#include <exception>
#include "Defines.hpp"

class NotEnoughRoom : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return NOT_ENOUGH_ROOM;
    }  
};

#endif