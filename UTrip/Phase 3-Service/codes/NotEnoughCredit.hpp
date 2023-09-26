#ifndef NOT_ENOUGH_CREDIT_HPP
#define NOT_ENOUGH_CREDIT_HPP

#include <exception>
#include "Defines.hpp"

class NotEnoughCredit : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return NOT_ENOUGH_CREDIT;
    }  
};

#endif