#ifndef ECHO_HPP
#define ECHO_HPP

#include "Observer.hpp"

class Echo : public Observer
{
public:
    Echo(int _type, std::vector<Channel*> _source_channels, Channel* _destination_channel);

    void update(std::string message);
private:
    Channel* destination_channel;
};

#endif
