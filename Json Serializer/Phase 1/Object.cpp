#include "Object.hpp"

using namespace std;

void Object::print_data(data_2D datas_info, int tab) 
{ 
    if (key != "")  
        print_name(tab);
    cout << OPEN_ACCOLADE;
    print_inside(datas_info, tab);
    cout << CLOSE_ACCOLADE;
}