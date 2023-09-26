#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#define EOF_ '\0'
#define ENTER '\n'
#define WHITE_SPACE ' '
#define EMPTY_STRING ""

#define DOLLAR '$'
#define DOLLAR_ "$"
#define QUESTION_MARK '?'
#define EXCLAMATION_MARK '!'
#define PLUS_SIGN '+'
#define MINUS_SIGN '-'
#define MULTIPLICATION_SIGN '*'
#define DIVISION_SIGN '/'
#define EQUAL_SIGN '='
#define STACK ""

#define ADD "43"
#define SUBTRACT "45"
#define MULTIPLY "42"
#define DIVIDE "47"
#define EQUAL "61"

#define CIN "63"
#define COUT "33"

#define ZERO 0
#define ONE 1
#define TWO 2

#define FIRST 0
#define SECOND 1

#define ZERO_ '0'
#define NINE_ '9'
#define MINIMUM_STEPS "Minimum Steps: "

using namespace std;

typedef vector<vector<string>> VecString2D; 


VecString2D get_input();
VecString2D make_vector_of_string(string text);
vector<string> separate_last_line(string line);
bool is_reached_sign(char sign);

class Variable
{
public:
    Variable(string name_, int value_) { name = name_; value = value_; }

    void print() { cout << value << endl; }
    void set_value(int value_) { value = value_; }

    string get_name() { return name; }
    int get_value() { return value; }

private:
    string name;
    int value;
    vector<string> dependencies;
};
typedef vector<Variable*> VariablesVec;

class Interperter
{
public:
    Interperter(VecString2D lines_);
    void proccess_lines();  
    void find_minimum_steps();

private:
    void set_inputted_datas(vector<string> line);
    void set_variable_infos(string name, int value);

    void cin_operator(string name);
    void cout_operator(vector<string> line);
    int compute_line(vector<string> line);
    void print_output(vector<string> line);

    pair<int, int> find_values(string name1, string name2);

    int add(string variable_name1, string variable_name2);
    int subtract(string variable_name1, string variable_name2);
    int multiply(string variable_name1, string variable_name2);
    int divide(string variable_name1, string variable_name2);

    int find_value_by_name(string name);
    VecString2D find_changing_variables();
    VecString2D find_not_changing_variables();
    vector<string> get_chaning_variables_of_line(vector<string> line);
    vector<string> get_not_changing_variables_of_line(vector<string> line);

    void get_higher(int line_number);
    bool can_go_higher(int source_line, int destination_line);

    void combine_lines(int source_line, int destination_line);


    vector<int> inputted_datas;
    VecString2D lines;
    VariablesVec variables;

    VecString2D changing_variables;
    VecString2D not_changing_variables;
};

int main()
{
    VecString2D lines = get_input();

    Interperter simple_interpreter(lines);
    simple_interpreter.proccess_lines();
    simple_interpreter.find_minimum_steps();
}

vector<string> separate_last_line(string line)
{
    vector<string> separated__line;
    stringstream temp(line);
    string word;

    while (temp >> word)
        separated__line.push_back(word);

    return separated__line;
}

VecString2D make_vector_of_string(string text)
{
    VecString2D lines;
    vector<string> line;
    string word = EMPTY_STRING;
	for (int i = 0; i < text.size(); i++)
	{
        if (text[i] == DOLLAR)
        {
            string temp = EMPTY_STRING;
            temp.insert(temp.size(), text, i, text.size());
            vector<string> last_line = separate_last_line(temp);
            lines.push_back(last_line);
            break;
        }
        if (text[i] == ENTER)
        {
            line.push_back(word);
            lines.push_back(line);
            line = {};
            word = EMPTY_STRING;
            continue;
        }
        if (is_reached_sign(text[i]))
        {
	        if (word != EMPTY_STRING)
	        {
		        line.push_back(word);
		        word = EMPTY_STRING;
	        }
            line.push_back(to_string(text[i]));
            continue;
		}
        if (i + 1 == text.size())
        {
            word += text[i];
            line.push_back(word);
            lines.push_back(line);
            break;
        }
        word += text[i]; 
    }
    return lines;
}

bool is_reached_sign(char sign)
{
    if (sign == QUESTION_MARK || sign == EXCLAMATION_MARK ||
            sign == DOLLAR || sign == EQUAL_SIGN ||
			sign == PLUS_SIGN || sign == MINUS_SIGN || 
            sign == MULTIPLICATION_SIGN || sign == DIVISION_SIGN)
        return true;
    return false;
}

VecString2D get_input()
{
	string temp_text;
	string text = EMPTY_STRING;
	getline(cin, temp_text, EOF_);
	for (int i = 0; i < temp_text.size(); i++)
    {
        if (temp_text[i] == DOLLAR)
        {
            text.insert(text.size(), temp_text,i,temp_text.size());
            break;
        }
		if (temp_text[i] != WHITE_SPACE )
			text += temp_text[i];
    }
    return make_vector_of_string(text);
}

Interperter::Interperter(VecString2D lines_) 
{ 
    lines = lines_; 
    set_inputted_datas(lines[lines.size() - 1]);
}

void Interperter::proccess_lines()
{

    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i][FIRST] == DOLLAR_)
            break;

        else if (lines[i][FIRST] == CIN)
            cin_operator(lines[i][SECOND]);
        else if (lines[i][FIRST] == COUT)
            cout_operator(lines[i]);
        else
        {
            int result = compute_line(lines[i]);  
            set_variable_infos(lines[i][FIRST], result);  
        }   
    }
}  


void Interperter::cin_operator(string name)
{
    set_variable_infos(name, inputted_datas[FIRST]);
    inputted_datas.erase(inputted_datas.begin());
}

void Interperter::cout_operator(vector<string> line)
{
    if (line.size() > TWO)
    {
        line.erase(line.begin());
        cout << compute_line(line) << endl;
    }
    else
        print_output(line);    
}

void Interperter::set_inputted_datas(vector<string> line)
{
    if (line[0] != DOLLAR_)
        return;
    for (int i = 1; i < line.size(); i++)
        inputted_datas.push_back(stoi(line[i]));
}

void Interperter::set_variable_infos(string name, int value)
{
    for (int i = 0; i < variables.size(); i++)
        if (variables[i]->get_name() == name)
        {
            variables[i]->set_value(value);
            return;
        }
    Variable* variable = new Variable(name, value);
    variables.push_back(variable);
}

void Interperter::print_output(vector<string> line)
{
    if (ZERO_ <= line[SECOND][FIRST] && line[SECOND][FIRST] <= NINE_)
    {
        cout << stoi(line[1]) << endl;
        return;
    }

    for (int i = 0; i < variables.size(); i++)
        if (variables[i]->get_name() == line[1])
        {
            variables[i]->print();
            return;
        } 
    cout << ZERO << endl; 
}

int Interperter::compute_line(vector<string> line)
{
    if (line.size() == 3 && line[SECOND] == EQUAL)
    {
        cout << line[2] << endl;
        set_variable_infos(line[FIRST], find_value_by_name(line[TWO]));
        return find_value_by_name(line[TWO]);
    }
    reverse(line.begin(), line.end());
    int result = 0;
    string first_variable = line[0];
    for (int i = 0; i < line.size() - 2; i += 2)
    {
        if (line[i + 1] == ADD)
            result = add(first_variable, line[i + 2]);
        else if (line[i + 1] == SUBTRACT)
            result = subtract(first_variable, line[i + 2]);
        else if (line[i + 1] == MULTIPLY)
            result = multiply(first_variable, line[i + 2]);
        else if (line[i + 1] == DIVIDE)
            result = divide(first_variable, line[i + 2]);
        set_variable_infos(STACK, result);
        first_variable = STACK;        
    }
    return result;
}

int Interperter::find_value_by_name(string name)
{
    if (ZERO_ <= name[FIRST] && name[FIRST] <= NINE_)
        return stoi(name);

    for (int i = 0; i < variables.size(); i++)
        if (variables[i]->get_name() == name)
            return variables[i]->get_value();
}

int Interperter::add(string variable_name1, string variable_name2)
{
    pair<int ,int> values = find_values(variable_name1, variable_name2);
    return values.first + values.second;
}

int Interperter::subtract(string variable_name1, string variable_name2)
{
    pair<int ,int> values = find_values(variable_name1, variable_name2);
    return values.second - values.first;
}

int Interperter::multiply(string variable_name1, string variable_name2)
{
    pair<int ,int> values = find_values(variable_name1, variable_name2);
    return values.first * values.second;
}

int Interperter::divide(string variable_name1, string variable_name2)
{
    pair<int ,int> values = find_values(variable_name1, variable_name2);
    return values.second / values.first;
}

pair<int, int> Interperter::find_values(string name1, string name2)
{
    pair<int, int> values(ZERO,ZERO);

    for (int i = 0; i < variables.size(); i++)
    {
        if (variables[i]->get_name() == name1)
            values.first = variables[i]->get_value();

        if (variables[i]->get_name() == name2)
            values.second = variables[i]->get_value();
    }

    if (ZERO_ <= name1[FIRST] && name1[FIRST] <= NINE_)
        values.first = stoi(name1);

    if (ZERO_ <= name2[FIRST] && name2[FIRST] <= NINE_)
        values.second = stoi(name2);
    return values;
}

void Interperter::find_minimum_steps()
{
    changing_variables = find_changing_variables();
    not_changing_variables = find_not_changing_variables();
    for (int i = 1; i < lines.size() - 1; i++)
        get_higher(i);

    int minimum_steps = changing_variables.size() - 1;
    if (minimum_steps < not_changing_variables.size() - 1)
        minimum_steps = not_changing_variables.size() - 1;
    cout << MINIMUM_STEPS << minimum_steps << endl;
}

void Interperter::get_higher(int line_number)
{
    for (int i = line_number - 1; i >= 0; i--)
    {
        if (can_go_higher(line_number, i))
            continue;
        else
        {
            combine_lines(line_number, i + 1);
            break;
        }
    }   
}

void Interperter::combine_lines(int source_line, int destination_line)
{
    if (source_line == destination_line)
        return;
    for (int i = 0; i < changing_variables[source_line].size(); i++)
        changing_variables[destination_line].push_back(changing_variables[source_line][i]);
    for (int i = 0; i < not_changing_variables[source_line].size(); i++)
        not_changing_variables[destination_line].push_back(not_changing_variables[source_line][i]);

    changing_variables.erase(changing_variables.begin() + source_line);
    not_changing_variables.erase(not_changing_variables.begin() + source_line);
}

bool Interperter::can_go_higher(int source_line, int destination_line)
{
    if (lines[source_line][FIRST] == CIN && lines[destination_line][FIRST] == CIN)
        return false;
    for (int i = 0; i < changing_variables[destination_line].size(); i++)
    {
        for (int j = 0; j < changing_variables[source_line].size(); j++)
            if (changing_variables[source_line][j] == changing_variables[destination_line][i])
                return false;

        for (int j = 0; j < not_changing_variables[source_line].size(); j++)
            if (not_changing_variables[source_line][j] == changing_variables[destination_line][i])
                return false;
    }
    for (int i = 0; i < not_changing_variables[destination_line].size(); i++)
        for (int j = 0; j < changing_variables[source_line].size(); j++)
            if (changing_variables[source_line][j] == not_changing_variables[destination_line][i])
                return false;
    return true;
}

VecString2D Interperter::find_changing_variables()
{
    VecString2D changing_variables;
    for (int i = 0; i < lines.size(); i++)
        changing_variables.push_back(get_chaning_variables_of_line(lines[i]));
    return changing_variables;
}

VecString2D Interperter::find_not_changing_variables()
{
    VecString2D not_changing_variables;
    for (int i = 0; i < lines.size(); i++)
        not_changing_variables.push_back(get_not_changing_variables_of_line(lines[i]));
    return not_changing_variables;    
}

vector<string> Interperter::get_chaning_variables_of_line(vector<string> line)
{
    vector<string> changing;
    if (line[FIRST] == CIN)
        changing.push_back(line[SECOND]);
    if (line[FIRST] != CIN && line[FIRST] != COUT && line[FIRST] != DOLLAR_)
        changing.push_back(line[FIRST]);

    return changing;
}

vector<string> Interperter::get_not_changing_variables_of_line(vector<string> line)
{
    vector<string> not_changings;
    for (int i = 1; i < line.size(); i++)
    {
        if (line[i - 1] == CIN || line[i - 1] == DOLLAR_)
            break;
        if (line[i] != MULTIPLY && line[i] != ADD && line[i] != SUBTRACT && line[i] != DIVIDE && 
                line[i] != EQUAL && !(ZERO_ <= line[i][FIRST] && line[i][FIRST] <= NINE_))
            not_changings.push_back(line[i]);
    }

    return not_changings;
}

