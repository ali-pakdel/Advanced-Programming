#include <iostream>
#include <vector>
#include <algorithm>

#include "Author.hpp"

using namespace std;

void Author::print_author_all_infos()
{
	print_author_info();
	print_author_genres();
	print_author_books_info();
}

void Author::print_author_info()
{
	cout << "id: " << author_ID << endl
		<< "Name: " << author_name << endl
		<< "Year of Birth: " << year_of_birth << endl
		<< "Place of Birth: " << place_of_birth << endl
		<< "Member Since: " << member_since << endl;
}

void Author::print_author_genres()
{
	sort(genres.begin(), genres.end());
	cout << "Genres: ";
	if (genres.size() > 0)
	{
		cout << genres[0];
		for (int i = 1; i < genres.size(); i++)
			cout << ", " << genres[i];
	}
}

void Author::print_author_books_info()
{
	cout << endl << "Books:" << endl;
	for (int i = 0; i < pointer_books_info.size(); i++)
		pointer_books_info[i]->print_book_info();
}
