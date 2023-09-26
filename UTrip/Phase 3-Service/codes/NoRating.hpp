#ifndef NO_RATING_HPP
#define NO_RATING_HPP

#include <exception>
#include "Defines.hpp"

class NoRating : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return NO_RATING;
    }   
};
#endif