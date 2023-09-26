#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "Data.hpp"

class Container : public Data
{
public:
    Container(int _parentId, std::string _key, int _id, int _type);

    virtual void print_data(data_2D datas_info, int tab) = 0;
    
protected:
    void print_name(int tab);
    void print_inside(data_2D datas_info, int tab);
    void print_other_datas(data_2D datas_info, int tab);

    int id;
};

#endif