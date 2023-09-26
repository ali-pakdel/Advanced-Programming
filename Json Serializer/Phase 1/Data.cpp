#include "Data.hpp"

using namespace std;

Data::Data(int _parentId, int _type) 
{ 
    parentId = _parentId;
    type = _type; 
}

void Data::print_tab(int tab)
{
    for (int i = 0; i < tab; i++)
        cout << TAB;
}