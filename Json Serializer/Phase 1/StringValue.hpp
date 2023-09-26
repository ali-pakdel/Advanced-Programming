#ifndef STRING_VALUE_HPP
#define STRIGN_VALUE_HPP

#include "Value.hpp"

class StringValue : public Value
{
public:
    StringValue(int _parentId, std::string _value, int _type) 
            : Value(_parentId, _value, _type) {};
            
    void print_data(data_2D datas_info, int tab);
};

#endif