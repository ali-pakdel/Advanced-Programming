#include "Channel.hpp"

using namespace std;

Channel::Channel(string _name)
{
    name = _name;
}

void Channel::tell_new_message(string message) 
{
    notify_loggers(message);
    notify(message);
}

void Channel::notify(string message)
{
    for (int i = 0; i < observers_info.size(); i++)
        if (observers_info[i]->get_type() != LOGGER_BOT)
            observers_info[i]->update(message);
}

void Channel::notify_loggers(string message)
{
    for (int i = 0; i < observers_info.size(); i++)
        if (observers_info[i]->get_type() == LOGGER_BOT)
            observers_info[i]->update(message);
}
