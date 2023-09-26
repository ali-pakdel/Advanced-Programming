#include "StringVariable.hpp"

using namespace std;

void StringVariable::print_data(data_2D datas_info, int tab) 
{
    print_tab(tab);
    cout << DOUBLE_QUOTATON << key << DOUBLE_QUOTATON 
    << COLON << DOUBLE_QUOTATON << value << DOUBLE_QUOTATON;  
}
