#include <iostream>
#include <sstream>
#include <string>

#include "Functions.hpp"
#include "BadRequest.hpp"
#include "NotFound.hpp"
#include "PermissionDenied.hpp"

using namespace std;

const vector<string> post_commands{SIGNUP, LOGIN, LOGOUT, 
        WALLET, RESERVES, COMMENTS, RATINGS, FILTERS, DEFAULT_PRICE_FILTER, SORT, MANUAL_WEIGHTS};
const vector<string> get_commands{WALLET, HOTELS, COMMENTS,
        RATINGS, RESERVES, MANUAL_WEIGHTS, ESTIMATED_WEIGHTS};
const vector<string> delete_commands{RESERVES, FILTERS};

void get_command(UTrip& trip)
{
    string line;
    while (getline(cin, line))
    {
        try
        {
            which_command(line, trip);
        } catch (exception& error)
        {
            cout << error.what();
        }
        
    }
}

void which_command(string line, UTrip& trip)
{
    string command;
    stringstream line_(line);
    line_ >> command;

    if (command == POST_)
        do_post_commands(line_, trip);
    else if (command == GET_)
        do_get_commands(line_, trip);
    else if (command == DELETE)
        do_delete_commands(line_, trip);
    else
        throw(BadRequest());
        
}

void do_post_commands(stringstream& line, UTrip& trip)
{
    string command, question_mark;
    line >> command >> question_mark;

    check_not_found(command,post_commands);
    trip.check_permission(command);

    if (command == WALLET && question_mark == QUESTION_MARK)
        trip.increase_wallet(line);
    else if (command == RESERVES && question_mark == QUESTION_MARK)
        trip.get_reserve_infos(line);
    else if (command == COMMENTS && question_mark == QUESTION_MARK)
        trip.add_comment(line);
    else if (command == RATINGS && question_mark == QUESTION_MARK)
        trip.add_rating(line);
    else if (command == FILTERS && question_mark == QUESTION_MARK)
        trip.add_filter(line);
    else if (command == DEFAULT_PRICE_FILTER && question_mark == QUESTION_MARK)
        trip.reset_default_price_filter(line);
    else if (command == SORT && question_mark == QUESTION_MARK)
        trip.sort_hotels(line);
    else if (command == MANUAL_WEIGHTS && question_mark == QUESTION_MARK)
        trip.reset_rating_weights(line);
    else 
        throw(BadRequest());
}

void do_get_commands(stringstream& line, UTrip& trip)
{
    string command, question_mark;
    line >> command >> question_mark;

    check_not_found(command, get_commands);
    trip.check_permission(command);

    if (command == WALLET)
        trip.get_wallet_transactions(line);
    else if (command == HOTELS && question_mark.size() == ZERO)
        trip.show_hotels_info();
    else if (command == HOTELS && question_mark == QUESTION_MARK)
        trip.show_hotel_info(line);
    else if (command == COMMENTS && question_mark == QUESTION_MARK)
        trip.show_hotel_comments(line);
    else if (command == RATINGS && question_mark == QUESTION_MARK)
        trip.show_hotel_ratings(line);
    else if (command == RESERVES && question_mark.size() == ZERO)
        trip.show_user_reserves();
    else if (command == MANUAL_WEIGHTS && question_mark.size() == ZERO)
        trip.show_manual_weights();
    else if (command == ESTIMATED_WEIGHTS && question_mark.size() == ZERO)
        trip.show_estimated_weights();
    else
        throw(BadRequest());
}

void do_delete_commands(stringstream& line, UTrip& trip)
{
    string command, question_mark;
    line >> command >> question_mark;
    
    check_not_found(command, delete_commands);
    trip.check_permission(command);

    if (command == RESERVES && question_mark == QUESTION_MARK)
        trip.delete_reserves(line);
    else if (command == FILTERS && question_mark.size() == ZERO)
        trip.delete_filters();
}

void check_not_found(string command, vector<string> commands)
{
    for (int i = 0; i < commands.size(); i++)
    {
        if (command.size() == ZERO)
            throw(BadRequest());
        if (commands[i] == command)
            return;
    }
    throw(NotFound());
}

