#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Container.hpp"

class Object : public Container
{
public:
    Object(int _parentId, std::string _name, int _id, int _type) 
            : Container(_parentId, _name, _id, _type) {};

    void print_data(data_2D datas_info, int tab);
};

#endif
