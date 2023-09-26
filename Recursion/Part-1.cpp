#include <iostream>
#include <vector>
#include <string>

using namespace std;

string get_input();
void reverse_string(string &inp_str, int from, int to);
string get_input();

int main() 
{
	string inp_str = get_input();
	reverse_string(inp_str, 0, inp_str.size()-1);
	cout << inp_str << endl;
}

string get_input() 
{
	string inp_string;
	cin >> inp_string;
	return inp_string;
}

void reverse_string(string &inp_str, int from, int to)
{
	char temp;
	int diff = from - to;
	if (from < to)
	{
		int j = to;
		for (int i = from; i < j; i++, j--)
		{
			temp = inp_str[i];
			inp_str[i] = inp_str[j];
			inp_str[j] = temp;
		}
	}
	else
		return;
	reverse_string(inp_str, from, (to + from) / 2);
	reverse_string(inp_str, ((to + from) / 2) + 1, to);
}