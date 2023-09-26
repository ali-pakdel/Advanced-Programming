#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "Container.hpp"

class Array : public Container
{
public:
    Array(int _parentId, std::string _key, int _id, int _type)
        : Container(_parentId, _key, _id, _type) {};
    
    void print_data(data_2D datas_info, int tab);
};

#endif
