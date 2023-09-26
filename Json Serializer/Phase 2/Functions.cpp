#include <iostream>

#include "Functions.hpp"

using namespace std;

void do_command(Messenger& messenger)
{
    string command;
    while (cin >> command)
    {
        try
        {
            which_command(messenger, command);
        } catch (exception& error)
        {
            cerr << error.what();
        }
    }
}

void which_command(Messenger& messenger, string command)
{
    if (command == ADD_CHANNEL)
        add_channel(messenger);
    else if (command == ADD_BOT)
        which_bot(messenger);
    else if (command == TELL)
       tell_message(messenger);
}

void which_bot(Messenger& messenger)
{
    string bot_type;
    cin >> bot_type;
    if (bot_type == ECHO)
        add_echo(messenger);
    else if (bot_type == LOGGER)
        add_logger(messenger);
    else if (bot_type == FRED)
        add_fred(messenger);
    else if (bot_type == LIBRARIAN)
        add_librarian(messenger);
}

void add_channel(Messenger& messenger)
{
    
    string channel_name;
    cin >> channel_name;
    messenger.add_channel(channel_name);
}

void add_echo(Messenger& messenger)
{
    string source_channel, destination_channel;
    cin >> source_channel >> destination_channel;
    messenger.add_echo(source_channel, destination_channel);
}

void add_logger(Messenger& messenger)
{
    string file_name;
    cin >> file_name;
    messenger.add_logger(file_name);
}

void add_fred(Messenger& messenger)
{
    string source_channel;
    cin >> source_channel;
    messenger.add_fred(source_channel);
}

void add_librarian(Messenger& messenger)
{
    string source_channel;
    cin >> source_channel;
    messenger.add_librarian(source_channel);
}

void tell_message(Messenger& messenger)
{
    string source_channel, message;
    cin >> source_channel;
    getline(cin >> ws, message);
    messenger.tell_message(source_channel, message);
}
