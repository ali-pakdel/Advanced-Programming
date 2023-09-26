#include "Functions.hpp"

int main(int argc, char* argv[])
{
    UTrip trip;
    trip.read_infos(argv[FILE_PATH], argv[2]);
    get_command(trip);
}