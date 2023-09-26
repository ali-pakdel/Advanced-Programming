#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int multiply(vector<int> vec, int i);
void sortNums(vector<int> &vec, int i);
void print(vector<int> vec);

int main()
{
	int inp_num;
	vector<int> vec_inp;
	while (cin >> inp_num)
		vec_inp.push_back(inp_num);	
	sortNums(vec_inp, 0);
	print(vec_inp);
}
void sortNums(vector<int> &vec, int i)
{
	int temp;
	int result;
	temp = vec[i];
	vec.erase(vec.begin() + i);
	result = multiply(vec, 0);
	vec.insert(vec.begin() + i, temp);
	if (i + 1 < vec.size())
		sortNums(vec,  i + 1);
	vec[i] = result;

}
int multiply(vector<int> vec, int i)
{
	if (i + 1 <= vec.size())
		return vec[i] * multiply(vec, i + 1);
	return 1;
}
void print(vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << ' ';
}