#include "Echo.hpp"
#include "Channel.hpp"

using namespace std;

Echo::Echo(int _type, channels _source_channels, Channel* _destination_channel) 
        : Observer(_type)
{
    source_channels = _source_channels;
    destination_channel = _destination_channel;
}

void Echo::update(std::string message)
{
    destination_channel->tell_new_message(message);
}