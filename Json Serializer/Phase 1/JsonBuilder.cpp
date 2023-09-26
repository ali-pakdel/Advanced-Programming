#include "JsonBuilder.hpp"
#include "Array.hpp"
#include "Object.hpp"
#include "IntegerVariable.hpp"
#include "StringVariable.hpp"
#include "IntegerValue.hpp"
#include "StringValue.hpp"
#include "Invalid.hpp"
#include "Duplicate.hpp"
#include "Undefined.hpp"

using namespace std;

void JsonBuilder::addStringToObject(int parentId, 
        string key, string value)
{
    check_parentId_object(parentId);
    check_key(parentId, key);
    StringVariable* string_variable = new StringVariable(parentId,
             key, value, STRING_VARIABLE);
    datas_info[parentId].push_back(string_variable);
}

void JsonBuilder::addIntegerToObject(int parentId,
         string key, int value)
{
    check_parentId_object(parentId);
    check_key(parentId, key);
    IntegerVariable* integer_variable = new IntegerVariable(parentId, key,
    to_string(value), INTEGER_VARIABLE);
    datas_info[parentId].push_back(integer_variable);
}

int JsonBuilder::addContainerToObject(int parentId,
         string key, string type)
{
    check_parentId_object(parentId);
    check_key(parentId, key);
    check_type(type);
    vector<Data*> temp;
    if (type == ARRAY)
        temp.push_back(addArrayToObject(parentId, key));

    else if (type == OBJECT)
        temp.push_back(addObjectToObject(parentId, key));

    datas_info.push_back(temp);
    return datas_info.size() - 1;
}

Data* JsonBuilder::addObjectToObject(int parentId,
         string key)
{
    Object* object = new Object(parentId, key,
             datas_info.size(), OBJECT_);
    datas_info[parentId].push_back(object);
    return object;
}

Data* JsonBuilder::addArrayToObject(int parentId,
         string key)
{
    Array* array = new Array(parentId, key,
             datas_info.size(), ARRAY_);
    datas_info[parentId].push_back(array);
    return array;
}

void JsonBuilder::addStringToArray(int parentId,
         string value)
{
    check_parentId_array(parentId);
    StringValue* string_value = new StringValue(parentId,
             value, STRING_VALUE);
    datas_info[parentId].push_back(string_value);
}

void JsonBuilder::addIntegerToArray(int parentId,
         int value)
{
    check_parentId_array(parentId);
    IntegerValue* integer_value = new IntegerValue(parentId,
             to_string(value), INTEGER_VALUE);
    datas_info[parentId].push_back(integer_value);
}

int JsonBuilder::addContainerToArray(int parentId,
         string type)
{
    check_parentId_array(parentId);
    check_type(type);
    vector<Data*> temp;
    if (type == ARRAY)
        temp.push_back(addArrayToArray(parentId));

    if (type == OBJECT)
        temp.push_back(addObjectToArray(parentId));

    datas_info.push_back(temp);
    return datas_info.size() - 1;
}

Data* JsonBuilder::addObjectToArray(int parentId)
{
    Object* object = new Object(parentId, EMPTY_KEY,
             datas_info.size(), OBJECT_);
    datas_info[parentId].push_back(object);
    return object;
}

Data* JsonBuilder::addArrayToArray(int parentId)
{
    Array* array = new Array(parentId, EMPTY_KEY,
             datas_info.size(), ARRAY_);
    datas_info[parentId].push_back(array);
    return array;
}

void JsonBuilder::print(int id)
{
    check_parentId_object(id);
    if (check_if_empty(id))
        return;
    print_inside(id);
    cout << ENTER;
    cout << CLOSE_ACCOLADE << ENTER;
}

bool JsonBuilder::check_if_empty(int id)
{
    if (datas_info[id].size() <= ONE)
    {
        cout << OPEN_ACCOLADE << CLOSE_ACCOLADE << ENTER;
        return true;
    }
    cout << OPEN_ACCOLADE << ENTER;
    return false;
}

void JsonBuilder::print_inside(int id)
{
    datas_info[id][FIRST]->print_data(datas_info, ONE);
    for (int i = SECOND; i < datas_info[id].size(); i++)
    {
        cout << COMMA << ENTER;
        datas_info[id][i]->print_data(datas_info, ONE);
    }
}

void JsonBuilder::check_parentId_object(int parentId)
{
    if ((parentId == MOTHER) || 
            (parentId < datas_info.size() && 
                    datas_info[parentId][DEFAULT]->get_type() == OBJECT_) )
        return;
    throw(Invalid());
}

void JsonBuilder::check_parentId_array(int parentId)
{
    if ((parentId == MOTHER) || 
            (parentId < datas_info.size() && 
                    datas_info[parentId][DEFAULT]->get_type() == ARRAY_))
        return;
    throw(Invalid());
}

void JsonBuilder::check_key(int parentId, string key)
{
    for (int i = 1; i < datas_info[parentId].size(); i++)
        if (datas_info[parentId][i]->get_key() == key && 
                key != EMPTY_KEY)
                throw(Duplicate());

}

void JsonBuilder::check_type(string type)
{
    if (type != OBJECT && type != ARRAY)
        throw(Undefined());
}
