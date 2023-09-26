#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <string>

#include "Defines.hpp"
#include "Observer.hpp"

class Channel
{
public:
    Channel(std::string _name);

    std::string get_channel_name() { return name; }
    void add_bot(Observer* observor) { observers_info.push_back(observor); }

    void tell_new_message(std::string message);

private:
    void notify(std::string message);
    void notify_loggers(std::string message);
    
    std::string name;
    std::vector<Observer*> observers_info;
};
typedef std::vector<Channel*> channels;


#endif
