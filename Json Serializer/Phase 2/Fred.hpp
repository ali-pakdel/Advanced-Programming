#ifndef FRED_HPP
#define FRED_HPP

#include "Observer.hpp"

class Fred : public Observer
{
public:
    Fred(int _type, std::vector<Channel*> _source_channels);
    void update(std::string message);
};

#endif
