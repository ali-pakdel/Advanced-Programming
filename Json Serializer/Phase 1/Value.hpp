#ifndef VALUE_HPP
#define VALUE_HPP

#include <vector>
#include <string>

#include "Data.hpp"

class Value : public Data
{
public:
    Value(int _parentId, std::string _value, int _type) 
            : Data(_parentId, _type) 
    { 
        value = _value; 
    }
    
    virtual void print_data(data_2D datas_info, int tab) = 0;

protected:
    std::string value;
};

#endif