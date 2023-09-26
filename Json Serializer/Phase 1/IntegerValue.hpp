#ifndef INTEGER_VALUE_HPP
#define INTEGER_VALUE_HPP

#include "Value.hpp"

class IntegerValue : public Value
{
public:
    IntegerValue(int _parentId, std::string _value, int _type) 
            : Value(_parentId, _value, _type) {};
            
    void print_data(data_2D datas_info, int tab);
};

#endif