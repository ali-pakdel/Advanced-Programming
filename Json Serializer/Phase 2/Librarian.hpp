#ifndef LIBRARIAN_HPP
#define LIBRAIRAN_HPP

#include "Observer.hpp"

class Librarian : public Observer
{
public:
    Librarian(int _type, std::vector<Channel*> _source_channels);

    void update(std::string message);
private:
    int notification = 0;
};

#endif
