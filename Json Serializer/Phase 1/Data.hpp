#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Defines.hpp"

class Data
{
public:
    Data(int _parentId, int _type);

    int get_type() { return type; }
    std::string get_key() { return key; }
    
    virtual void print_data(std::vector<std::vector<Data*>>  datas_info, int tab) = 0;

protected:
    void print_tab(int tab);

    int type;
    int parentId;
    std::string key = "";
};

typedef std::vector<Data*> datas;
typedef std::vector<std::vector<Data*>> data_2D;

#endif
