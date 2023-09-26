#ifndef STRING_VARIABLE_HPP
#define STRING_VARIABLE_HPP

#include "Variable.hpp"

class StringVariable : public Variable
{
public:
    StringVariable(int _parentId, std::string _key, std::string _value, int _type) 
        : Variable(_parentId, _key, _value, _type) {};

    void print_data(data_2D datas_info, int tab);
};
#endif
