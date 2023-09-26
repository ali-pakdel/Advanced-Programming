#include "Array.hpp"

using namespace std;

void Array::print_data(data_2D datas_info, int tab)
{
    if (key != EMPTY_KEY)
        print_name(tab);
    cout << OPEN_BRACKET;
    print_inside(datas_info, tab);
    cout << CLOSE_BRACKET;
}