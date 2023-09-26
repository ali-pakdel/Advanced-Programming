#include "Fred.hpp"
#include "Channel.hpp"

using namespace std;

Fred::Fred(int _type, channels _source_channels) : Observer(_type) 
{
    source_channels = _source_channels;
}

void Fred::update(std::string message)
{
    if (message == HI)
        source_channels[0]->tell_new_message(HELLO);
}