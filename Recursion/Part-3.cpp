#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>

#define POSSIBALE_MOVES 4

using namespace std;

vector<vector<int> > get_board(vector<vector<int> > &board, int row_count, int col_count);
vector<vector<int> > already_gone(vector<vector<int> > &board, int row_count, int col_count);
int find_all_ways(vector<vector<int> > &board, int current_row, int current_col, int row_count, int col_count, vector<int> &sums, vector<vector<int> > &helper_board);
void solve(vector<vector<int> >&board, int row_count, int col_count, vector<vector<int> > &helper_board);
int calculate_sum(vector<vector<int> > board, int i, int j, int row_count, int col_count, vector<vector<int> > helper_board);
void print_max_gold(vector<int> sums);
void restart_helper(vector<vector<int> > board, int row_count, int col_count, vector<vector<int> > &helper_board);

int main() 
{
	int row_count, col_count;
	cin >> row_count >> col_count;
	vector<vector<int> > board;
	vector<vector<int> > helper_board = get_board(board, row_count, col_count);
	solve(board, row_count, col_count, helper_board);
}

vector<vector<int> > get_board(vector<vector<int> > &board, int row_count, int col_count)
{
	int num;
	for (int i = 0; i < row_count; i++)
	{
		vector<int> temp;
		for (int j = 0; j < col_count; j++)
		{
			cin >> num;
			temp.push_back(num);
		}
		board.push_back(temp);
	}
	return already_gone(board, row_count, col_count);
}

vector<vector<int> > already_gone(vector<vector<int> > &board, int row_count, int col_count)
{
	vector<vector<int> > helper_board;
	for (int i = 0; i < row_count; i++)
	{
		vector<int> temp;
		for (int j = 0; j < col_count; j++)
		{
			temp.push_back(1);
			if (board[i][j] == 0)
				temp[j] = 0;
		}
		helper_board.push_back(temp);
	}
	return helper_board;
}

int find_all_ways(vector<vector<int> > &board, int current_row, int current_col, int row_count, int col_count, vector<int> &sums, vector<vector<int> > &helper_board)
{
	int row_delta[] = { 0,-1,0,1 };
	int col_delta[] = { -1,0,1,0 };
	for (int move = 0; move < POSSIBALE_MOVES; move++)
	{
		int new_row = current_row + row_delta[move];
		int new_col = current_col + col_delta[move];
		if (new_row < 0 || new_row >= row_count || new_col < 0 || new_col >= col_count)
			continue;
		if (helper_board[new_row][new_col] == 0)
			continue;
		helper_board[new_row][new_col] = 0;
		if (find_all_ways(board, new_row, new_col, row_count, col_count, sums, helper_board))
			return true;
		helper_board[new_row][new_col] = 1;
	}
	int sum = calculate_sum(board, 0, 0, row_count, col_count, helper_board);
	sums.push_back(sum);
	return false;
}

void solve(vector<vector<int> >&board, int row_count, int col_count, vector<vector<int> > &helper_board)
{
	vector<int> sums;
	for (int i = 0; i < row_count; i++) 
	{
		for (int j = 0; j < col_count; j++)
		{
			if (helper_board[i][j] == 0)
				continue;
			helper_board[i][j] = 0;
			find_all_ways(board, i, j, row_count, col_count, sums, helper_board);
			restart_helper(board, row_count, col_count, helper_board);
		}
	}
	print_max_gold(sums);
}

int calculate_sum(vector<vector<int> > board, int i, int j, int row_count, int col_count, vector<vector<int> > helper_board)
{
	int sum = 0;
	for (int i = 0; i < row_count; i++)
	{
		for (int j = 0; j < col_count; j++)
		{
			if (helper_board[i][j] == 0)
				sum += board[i][j];
		}
	}
	return sum;
}

void print_max_gold(vector<int> sums)
{
	sort(sums.begin(), sums.end());
	cout << sums[sums.size() - 1] << endl;
}

void restart_helper(vector<vector<int> > board, int row_count, int col_count, vector<vector<int> > &helper_board)
{
	for (int i = 0; i < row_count; i++)
	{
		for (int j = 0; j < col_count; j++)
		{
			helper_board[i][j] = 1;
			if (board[i][j] == 0)
				helper_board[i][j] = 0;
		}
	}
}