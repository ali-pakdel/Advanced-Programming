#include <fstream>

#include "Logger.hpp"

using namespace std;

Logger::Logger(int _type, std::string _file_name) : Observer(_type)
{
    file_name = _file_name;
}

void Logger::update(string message)
{
    ofstream output_file;
    output_file.open(file_name, ios::app);
    output_file << message << endl;
}
