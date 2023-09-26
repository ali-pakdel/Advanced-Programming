#include "StringValue.hpp"

using namespace std;

void StringValue::print_data(data_2D datas_info, int tab)
{
    print_tab(tab);
    cout << DOUBLE_QUOTATON << value << DOUBLE_QUOTATON;     
}