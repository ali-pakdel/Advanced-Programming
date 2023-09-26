#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

unsigned long int generatePasswordHash(string password);
string get_alphabet_hash(unsigned long int &hash, int passSize);
bool combination_of_letters(string alphabet, int passSize, int i, int current_size, vector<int> check, unsigned long int hash, int &found);
bool permute(string in, string out, unsigned long int hash, int &found);
string create_new_alphabet(string alphabet, int passSize);
void solve(string alphabet, int passSize, vector<int> check, unsigned long int hash, int &found);

int main()
{
	int found = 0;
	vector<int> check;
	int passSize;
	unsigned long int hash;
	cin >> passSize;
	string alphabet = get_alphabet_hash(hash, passSize);
	for (int i = 0; i < alphabet.size(); i++) {
		check.push_back(0);
	}
	solve(alphabet, passSize, check, hash, found);
}

unsigned long int generatePasswordHash(string password)
{
	return hash<string>() (password);
}

string get_alphabet_hash(unsigned long  int &hash, int passSize)
{
	string alphabet;
	cin >> alphabet;
	cin >> hash;
	return create_new_alphabet(alphabet, passSize);
}

bool combination_of_letters(string alphabet, int passSize, int i, int current_size, vector<int> check, unsigned long int hash, int &found)
{
	string word = "";
	if (current_size > passSize)
		return false;
	else if (current_size == passSize) {
		for (int i = 0; i < check.size(); i++) {
			if (check[i] == 1) {
				word += alphabet[i];
			}
		}
		if (permute(word, "", hash, found))
			return true;
		return false;
	}
	if (i == check.size()) {
		return false;
	}
	check[i] = 1;
	if (combination_of_letters(alphabet, passSize, i + 1, current_size + 1, check, hash, found))
		return true;
	check[i] = 0;
	combination_of_letters(alphabet, passSize, i + 1, current_size, check, hash, found);
	if (found == 0)
		return false;
	return true;
}

bool permute(string str, string out, unsigned long int hash, int &found)
{
	unsigned long int guessed_hash;
	if (str.size() == 0)
	{
		guessed_hash = generatePasswordHash(out);
		if (guessed_hash == hash)
		{
			cout << out << endl;
			found = 1;
			return true;
		}
		return false;
	}
	for (int i = 0; i < str.size(); i++)
	{
		if (permute(str.substr(1), out + str[0], hash, found))
			break;
		rotate(str.begin(), str.begin() + 1, str.end());
	}
	if (found == 1)
		return true;
	return false;
}

string create_new_alphabet(string alphabet, int passSize)
{
	string new_alphabet = alphabet;
	for (int i = 0; i < alphabet.size(); i++)
	{
		for (int j = 1; j < passSize; j++)
			new_alphabet += alphabet[i];
	}
	return new_alphabet;
}
void solve(string alphabet, int passSize, vector<int> check, unsigned long int hash, int &found)
{
	string new_alphabet = create_new_alphabet(alphabet, passSize);
	combination_of_letters(new_alphabet, passSize, 0, 0, check, hash, found);
	if (found == 0)
		cout << "NOT_FOUND";
}