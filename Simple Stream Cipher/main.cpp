#include<iostream>
#include<vector>
#include<fstream>
#include<string>

#define ENCRYPT "encrypt"
#define DECRYPT "decrypt"
#define SIMPLE "simple"
#define COMPLICATED "complicated"
#define END_LINE '\0'
#define TYPE first
#define KIND second
#define MAX_RANDOM 11

using namespace std;

struct Input
{
	string input_file_path;
	string output_file_path;
	string key;
	pair<string, string> method;
};

Input get_input();

vector<int> read(Input input_infos);
vector<int> read_file_encrypt(string input_file_path);
vector<int> read_file_decrypt(string input_file_path);

vector<int> do_command(Input input_infos);

vector<int> encrypt_proccess(Input input_infos, vector<int> input_txt);
vector<int> decrypt_proccess(Input input_infos, vector<int> input_txt);

vector<int> encrypt_simple(vector<int> input_txt, string key);
vector<int> decrypt_simple(vector<int> input_txt, string key);

string create_key_for_input_size(int size, string key);

vector<int> encrypt_complicated(vector<int> input_txt, string key);
vector<int> decrypt_complicated(vector<int> input_txt, string key);
int get_random_seed(string key);
vector<int> get_random_key(int size);

void write_to_file(Input input_infos, vector<int> output_txt);
void write_to_file_encrypt(string out_file_path, vector<int> output_txt);
void write_to_file_decrypt(string out_file_path, vector<int> output_txt);

int main() {
	Input input_infos = get_input();
	vector<int> output_txt = do_command(input_infos);
	write_to_file(input_infos, output_txt);
}

Input get_input()
{
	Input input_infos;
	cin >> input_infos.method.TYPE >> input_infos.method.KIND
		>> input_infos.key >> input_infos.input_file_path
		>> input_infos.output_file_path;
	return input_infos;
}

vector<int> read(Input input_infos)
{
	if (input_infos.method.TYPE == ENCRYPT)
		return read_file_encrypt(input_infos.input_file_path);
	else if (input_infos.method.TYPE == DECRYPT)
		return read_file_decrypt(input_infos.input_file_path);
}

vector<int> read_file_encrypt(string inp_file_path)
{
	ifstream input_file(inp_file_path);

	string temp_input_txt;
	vector<int> input_txt;
	getline(input_file, temp_input_txt, END_LINE);

	for (int i = 0; i < temp_input_txt.size(); i++)
		input_txt.push_back((int)temp_input_txt[i]);
	return input_txt;
}

vector<int> read_file_decrypt(string inp_file_path)
{
	ifstream input_file(inp_file_path);

	vector<int> input_txt;
	string number;

	while (getline(input_file, number))
		input_txt.push_back(stoi(number));
	return input_txt;
}

vector<int> do_command(Input input_infos)
{
	vector<int> input_txt = read(input_infos);
	if (input_infos.method.TYPE == ENCRYPT)
		return encrypt_proccess(input_infos, input_txt);
	else if (input_infos.method.TYPE == DECRYPT)
		return decrypt_proccess(input_infos, input_txt);
}

vector<int> encrypt_proccess(Input input_infos, vector<int> input_txt)
{
	if (input_infos.method.KIND == SIMPLE)
		return encrypt_simple(input_txt, input_infos.key);
	else if (input_infos.method.KIND == COMPLICATED)
		return encrypt_complicated(input_txt, input_infos.key);
}

vector<int> decrypt_proccess(Input input_infos, vector<int> input_txt)
{
	if (input_infos.method.KIND == SIMPLE)
		return decrypt_simple(input_txt, input_infos.key);
	else if (input_infos.method.KIND == COMPLICATED)
		return decrypt_complicated(input_txt, input_infos.key);
}

vector<int> encrypt_simple(vector<int> input_txt, string key)
{
	vector<int> output_txt;
	string long_key = create_key_for_input_size(input_txt.size(), key);
	for (int i = 0; i < input_txt.size(); i++)
		output_txt.push_back(input_txt[i] + long_key[i]);
	return output_txt;
}

vector<int> decrypt_simple(vector<int> input_txt, string key)
{
	vector<int> output_txt;
	string long_key = create_key_for_input_size(input_txt.size(), key);
	for (int i = 0; i < input_txt.size(); i++)
		output_txt.push_back(input_txt[i] - long_key[i]);
	return output_txt;
}

string create_key_for_input_size(int size, string key)
{
	string long_key = key;
	for (int i = key.size(); i < size; i++)
		long_key += key[i % key.size()];
	return long_key;
}

vector<int> encrypt_complicated(vector<int> input_txt, string key)
{
	srand(get_random_seed(key));
	vector<int> random_key = get_random_key(input_txt.size());
	vector<int> output_txt;
	for (int i = 0; i < input_txt.size(); i++)
		output_txt.push_back(input_txt[i] + random_key[i]);
	return output_txt;
}

vector<int> decrypt_complicated(vector<int> input_txt, string key)
{
	srand(get_random_seed(key));
	vector<int> random_key = get_random_key(input_txt.size());
	vector<int> output_txt;
	for (int i = 0; i < input_txt.size(); i++)
		output_txt.push_back(input_txt[i] - random_key[i]);
	return output_txt;
}

int get_random_seed(string key)
{
	int seed = 0;
	for (int i = 0; i < key.size(); i++)
		seed += key[i];
	return seed;
}

vector<int> get_random_key(int size)
{
	vector<int> random_key;
	for (int i = 0; i <= size; i++)
		random_key.push_back(rand() % MAX_RANDOM);
	return random_key;
}

void write_to_file(Input input_infos, vector<int> output_txt)
{
	if (input_infos.method.TYPE == ENCRYPT)
		write_to_file_encrypt(input_infos.output_file_path, output_txt);
	else if (input_infos.method.TYPE == DECRYPT)
		write_to_file_decrypt(input_infos.output_file_path, output_txt);
}

void write_to_file_encrypt(string out_file_path, vector<int> output_txt)
{
	ofstream output_file(out_file_path);
	for (int i = 0; i < output_txt.size(); i++)
		output_file << output_txt[i] << endl;
}

void write_to_file_decrypt(string out_file_path, vector<int> output_txt)
{
	ofstream output_file(out_file_path);
	for (int i = 0; i < output_txt.size(); i++)
		output_file << (char)output_txt[i];
}