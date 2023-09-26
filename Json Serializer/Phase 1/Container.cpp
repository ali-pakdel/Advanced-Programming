#include "Container.hpp"

using namespace std;

Container::Container(int _parentId, std::string _key, int _id, int _type) 
            : Data (_parentId, _type)
{ 
    key = _key; 
    id = _id; 
}

void Container::print_name(int tab)
{
    print_tab(tab);
    cout << DOUBLE_QUOTATON << key << DOUBLE_QUOTATON << COLON;
}

void Container::print_inside(data_2D datas_info, int tab)
{
    if (datas_info[id].size() <= ONE)
        return;
    cout << ENTER;
    print_other_datas(datas_info, tab);
    cout << ENTER;
    print_tab(tab);
}

void Container::print_other_datas(data_2D datas_info, int tab)
{
    datas_info[id][FIRST]->print_data(datas_info, tab + ONE);
    for (int i = SECOND; i < datas_info[id].size(); i++)
    {
        cout << COMMA << ENTER;
        datas_info[id][i]->print_data(datas_info, tab + ONE);
    }
}