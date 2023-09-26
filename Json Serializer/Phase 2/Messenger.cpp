#include "Messenger.hpp"
#include "Echo.hpp"
#include "Logger.hpp"
#include "Fred.hpp"
#include "Librarian.hpp"
#include "AlreadyExist.hpp"
#include "DoesNotExist.hpp"
#include "Invalid.hpp"

using namespace std;


void Messenger::add_channel(string channel_name)
{
    is_exist(channel_name);
    Channel* channel = new Channel(channel_name);
    channels_info.push_back(channel);
}

void Messenger::add_echo(string source_channel, string destionation_channel)
{
    is_not_exist(source_channel);
    is_not_exist(destionation_channel);
    is_source_and_destination_same(source_channel, destionation_channel);
    vector<Channel*> source_channels{channels_info[find_channel(source_channel)]};
    Echo* echo = new Echo(ECHO_BOT, source_channels, channels_info[find_channel(destionation_channel)]);
    channels_info[find_channel(source_channel)]->add_bot(echo);
}

void Messenger::add_logger(string file_name)
{
    Logger* logger = new Logger(LOGGER_BOT, file_name);
    for (int i = 0; i < channels_info.size(); i++)
        channels_info[i]->add_bot(logger);
}

void Messenger::add_fred(string source_channel)
{
    is_not_exist(source_channel);
    vector<Channel*> source_channels{channels_info[find_channel(source_channel)]};
    Fred* fred = new Fred(FRED_BOT, source_channels);
    channels_info[find_channel(source_channel)]->add_bot(fred);
}

void Messenger::add_librarian(string source_channel)
{
    is_not_exist(source_channel);
    vector<Channel*> source_channels{channels_info[find_channel(source_channel)]};
    Librarian* librarian = new Librarian(LIBRARIAN_BOT, source_channels);
    channels_info[find_channel(source_channel)]->add_bot(librarian);
}

void Messenger::tell_message(string source_channel, string message)
{
    is_not_exist(source_channel);
    channels_info[find_channel(source_channel)]->tell_new_message(message);
}

int Messenger::find_channel(string channel_name)
{
    for (int i = 0; i < channels_info.size(); i++)
        if (channels_info[i]->get_channel_name() == channel_name)
            return i;
    return NOT_FOUND;
}

void Messenger::is_exist(string channel_name)
{    
    if (!(find_channel(channel_name) == NOT_FOUND))
        throw(AlreadyExist());
}
void Messenger::is_not_exist(string channel_name)
{
    if (find_channel(channel_name) == NOT_FOUND)
        throw(DoesNotExist());
}
void Messenger::is_source_and_destination_same(string source, string destination)
{
    if (source == destination)
        throw(Invalid());
}