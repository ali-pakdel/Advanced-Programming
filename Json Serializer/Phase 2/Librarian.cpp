#include "Librarian.hpp"
#include "Channel.hpp"

using namespace std;

Librarian::Librarian(int _type, channels _source_channels) : Observer(_type) 
{
    source_channels = _source_channels;
}
void Librarian::update(std::string message)
{
    notification++;
    if (notification >= FIVE)
    {
        notification -= FIVE;
        source_channels[0]->tell_new_message(QUIET);
    }
}