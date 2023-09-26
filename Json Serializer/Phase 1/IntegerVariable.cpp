#include "IntegerVariable.hpp"

using namespace std;

void IntegerVariable::print_data(data_2D datas_info, int tab) 
{
    print_tab(tab);
    cout << DOUBLE_QUOTATON << key << DOUBLE_QUOTATON << COLON << value;
}
