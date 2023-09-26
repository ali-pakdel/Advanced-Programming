#ifndef MASSENGER_HPP
#define MASSENGER_HPP

#include "Channel.hpp"

class Messenger
{
public:
    void add_channel(std::string channel_name);
    void add_echo(std::string source_channel, std::string destination_channel);
    void add_logger(std::string file_name);
    void add_fred(std::string source_channel);
    void add_librarian(std::string source_channel);
    void tell_message(std::string source_channe, std::string message);


private:
    void is_exist(std::string channel_name);
    void is_not_exist(std::string channel_name);
    void is_source_and_destination_same(std::string source, std::string destinaion);

    int find_channel(std::string channel_name);
    channels channels_info;
};
#endif