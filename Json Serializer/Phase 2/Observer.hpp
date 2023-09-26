#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
#include <string>

#include "Defines.hpp"

class Channel;

class Observer
{
public:
    Observer(int _type)
    {
        type = _type;
    }
    int get_type() { return type; }

    virtual void update(std::string message) = 0;

protected:
    int type;
    std::vector<Channel*> source_channels;
};

typedef std::vector<Observer*> observers;

#endif
