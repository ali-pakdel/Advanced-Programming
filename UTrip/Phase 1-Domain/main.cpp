#include "Functions.hpp"

int main(int argc, char* argv[])
{
    UTrip trip;
    trip.read_hotels_info(argv[FILE_PATH]);
    get_command(trip);
}