#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>

#include "Messenger.hpp"

struct Info
{
    std::string command;

};

void do_command(Messenger& messenger);
void which_command(Messenger& messenger, std::string command);
void which_bot(Messenger& messenger);
void add_channel(Messenger& messenger);
void add_echo(Messenger& messenger);
void add_logger(Messenger& messenger);
void add_fred(Messenger& messenger);
void add_librarian(Messenger& messenger);
void tell_message(Messenger& messenger);

#endif