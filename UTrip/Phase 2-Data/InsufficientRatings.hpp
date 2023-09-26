#ifndef INSUFFICIENT_RATINGS_HPP
#define INSUFFICIENT_RATINGS_HPP

#include <exception>
#include "Defines.hpp"

class InsufficientRatings : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return INSUFFICIENT_RATINGS;
    }   
};
#endif