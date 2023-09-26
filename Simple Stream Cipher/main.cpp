#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

int get_input(string &inp_file_path, string &key, string &out_file_path);
vector<int> read_file_enc(string inp_file_path);
vector<int> read_file_dec(string inp_file_path);
vector<int> read(string inp_file_path, int enc_or_dec);
void simple(string inp_file_path, string key, string out_file_path, int enc_or_dec);
void complicated(string inp_file_path, string key, string out_file_path, int enc_or_dec);
void write_file_enc(string out_file_path, vector<int> vec);
void write_file_dec(string out_file_path, vector<int> vec);
void write(string out_file_path, vector<int> vec_enc_dec, int enc_or_dec);

int main() {
	string key;
	string inp_file_path;
	string out_file_path;
	int enc_or_dec;
	switch (get_input(inp_file_path, key, out_file_path))
	{
	case 1:
		enc_or_dec = 1;
		simple(inp_file_path, key, out_file_path, enc_or_dec);
		break;
	case 2:
		enc_or_dec = 1;
		complicated(inp_file_path, key, out_file_path, enc_or_dec);
		break;
	case 3:
		enc_or_dec = 2;
		simple(inp_file_path, key, out_file_path, enc_or_dec);
		break;
	case 4:
		enc_or_dec = 2;
		complicated(inp_file_path, key, out_file_path, enc_or_dec);
	}
}

int get_input(string &inp_file_path, string &key, string &out_file_path) 
{
	string enc_dec;
	string simp_comp;
	cin >> enc_dec >> simp_comp >> key >> inp_file_path >> out_file_path;
	if (enc_dec == "encrypt" && simp_comp == "simple")
		return 1;
	else if (enc_dec == "encrypt" && simp_comp == "complicated")
		return 2;
	else if (enc_dec == "decrypt" && simp_comp == "simple")
		return 3;
	else if (enc_dec == "decrypt" && simp_comp == "complicated")
		return 4;
}

vector<int> read_file_enc(string inp_file_path) 
{
	ifstream inFILE;
	string intxt;
	vector<int> vec_intxt;
	inFILE.open(inp_file_path);
	getline(inFILE, intxt, '\0');
	for (int i = 0; i < intxt.size(); i++)
	{
		vec_intxt.push_back((int)intxt[i]);
	}
	inFILE.close();
	return vec_intxt;
}

vector<int> read_file_dec(string inp_file_path)
{
	ifstream inFILE;
	vector<int> vec_intxt;
	inFILE.open(inp_file_path);
	int num, i = 0;
	while (1)
	{
		inFILE >> num;
		if (inFILE.eof())
			break;
		vec_intxt.push_back(num);
		i++;
	}
	inFILE.close();
	return vec_intxt;
}

vector<int> read(string inp_file_path, int enc_or_dec)
{
	vector<int> vec;
	if (enc_or_dec == 1)
		vec = read_file_enc(inp_file_path);
	else
		vec = read_file_dec(inp_file_path);
	return vec;
}

void simple(string inp_file_path, string key, string out_file_path, int enc_or_dec)
{	
	vector<int> vec_intxt = read(inp_file_path, enc_or_dec);
	vector<int> vec_enc_dec;
	int i = 0, out = 0, j = 0, pos_or_neg;
	if (enc_or_dec == 1)
		pos_or_neg = 1;
	else
		pos_or_neg = -1;
	while (i < vec_intxt.size())
	{
		if (j == key.size())
			j = 0;
		out = vec_intxt[i] + (pos_or_neg * key[j]);
		vec_enc_dec.push_back(out);
		i++;
		j++;
	}
	write(out_file_path, vec_enc_dec, enc_or_dec);
}

void complicated(string inp_file_path, string key, string out_file_path, int enc_or_dec)
{
	vector<int> vec_intxt = read(inp_file_path, enc_or_dec);
	int key_sum = 0, i = 0, pos_or_neg;
	if (enc_or_dec == 1)
		pos_or_neg = 1;
	else
		pos_or_neg = -1;
	vector<int> vec_enc;
	for (i = 0; i < key.size(); i++)
		key_sum += key[i];
	i = 0;
	srand(key_sum);
	for (i = 0; i < vec_intxt.size(); i++)
		vec_enc.push_back(vec_intxt[i] + (pos_or_neg * (rand() % 11)));

	write(out_file_path, vec_enc, enc_or_dec);
}

void write_file_enc(string out_file_path, vector<int> vec) 
{
	ofstream outFILE;
	outFILE.open(out_file_path);
	for (int i = 0; i < vec.size(); i++)
		outFILE << vec[i] << endl;
}

void write_file_dec(string out_file_path,vector<int> vec)
{
	ofstream outFILE;
	outFILE.open(out_file_path);
	for (int i = 0; i < vec.size(); i++)
		outFILE << (char)vec[i];
}

void write(string out_file_path, vector<int> vec_enc_dec, int enc_or_dec) 
{
	if (enc_or_dec == 1)
		write_file_enc(out_file_path, vec_enc_dec);
	else
		write_file_dec(out_file_path, vec_enc_dec);
}