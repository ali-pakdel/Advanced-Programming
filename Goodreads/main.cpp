#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

#include "GoodReads.hpp"
#include "Functions.hpp"

#define FILE_NAME 1

using namespace std;

int main(int argc, char* argv[])
{
	GoodReads good_reads;
	read_files(good_reads,  argv[FILE_NAME]);
	string command;
	while (cin >> command)
		do_command(good_reads, command);
}
