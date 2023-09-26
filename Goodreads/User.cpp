#include <iostream>
#include <algorithm>

#include "User.hpp"

using namespace std;

int User::calculate_likes_sum()
{
	if (pointer_reviews_info.size() == 0)
		return -1;
	int sum_likes = 0;
	for (int i = 0; i < pointer_reviews_info.size(); i++)
		sum_likes += pointer_reviews_info[i]->get_no_likes();
	return sum_likes;
}

void User::print_best_reviewer()
{
	sort(pointer_authors_info.begin(), pointer_authors_info.end());
	sort(favorite_genres.begin(), favorite_genres.end());
	print_user_info();
	print_favorite_genres();
	print_favorite_authors();
	print_no_books_in_shelf();
	cout << "Number of Likes: " << calculate_likes_sum() << endl;
}

void User::print_user_info()
{
	cout << "id: " << user_ID << endl
		<< "Name: " << user_name << endl
		<< "Place of Birth: " << place_of_birth << endl
		<< "Member Since: " << member_since << endl;
}

void User::print_favorite_genres()
{
	cout << "Favorite Genres: ";
	if (favorite_genres.size() > 0)
	{
		cout << favorite_genres[0];
		for (int i = 1; i < favorite_genres.size(); i++)
			cout << ", " << favorite_genres[i];
	}
}

 void User::print_favorite_authors()
 {
	 cout << endl << "Favorite Authors: ";
	 if (pointer_authors_info.size() > 0)
	 {
		 cout << pointer_authors_info[0]->get_author_name();
		 for (int i = 1; i < pointer_authors_info.size(); i++)
			 cout << ", " << pointer_authors_info[i]->get_author_name();
	 }
 }

 void User::print_no_books_in_shelf()
 {
	 cout << endl << "Number of Books in Read Shelf: " << read.size()
		 << endl << "Number of Books in Want to Read Shelf: "
		 << want_to_read.size()
		 << endl << "Number of Books in Currently Reading Shelf: "
		 << currently_reading.size() << endl;
 }
