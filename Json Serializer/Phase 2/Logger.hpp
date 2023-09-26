#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Observer.hpp"

class Logger : public Observer
{
public:
    Logger(int _type, std::string _file_name);
    void update(std::string message);

private:
    std::string file_name;
};

#endif
