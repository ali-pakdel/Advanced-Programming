#ifndef PERMISSION_DENIED_HPP
#define PERMISSION_DENIED_HPP

#include <exception>
#include "Defines.hpp"

class PermissionDenied : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return PERMISSION_DENIED;
    }  
};

#endif