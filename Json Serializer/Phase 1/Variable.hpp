#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include "Data.hpp"

class Variable : public Data
{
public:
    Variable(int _parentId, std::string _key, std::string _value, int _type) 
            : Data(_parentId, _type)
    {
        key = _key;
        value = _value;
    }

    virtual void print_data(data_2D datas_info, int tab) = 0;

protected:
    std::string value;
};

#endif