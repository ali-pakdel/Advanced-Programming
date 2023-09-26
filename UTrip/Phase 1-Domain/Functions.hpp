#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <sstream>

#include "UTrip.hpp"

void get_command(UTrip& trip);
void which_command(std::string line, UTrip& trip);
void do_post_commands(std::stringstream& line, UTrip& trip);
void do_get_commands(std::stringstream& line, UTrip& trip);
void do_delete_commands(std::stringstream& line, UTrip& trip);
void check_not_found(std::string command, std::vector<std::string> commands);

#endif