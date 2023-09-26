#include <string>
#include <vector>

#include "Book.hpp"

using namespace std;

void Book::print_book_info()
{ 
	cout << "id: " << book_ID 
		 << " Title: " << title << endl; 
}

void Book::print_book_shelf_info()
{
	cout << "id: " << book_ID
		 << endl << "Title: " << title
		 << endl << "Genre: " << genre << endl;
}

double Book::calculate_rating_avg()
{
	if (pointer_reviews_info.size() == 0)
		return 0;
	int sum_ratings = 0;
	for (int i = 0; i < pointer_reviews_info.size(); i++)
		sum_ratings += pointer_reviews_info[i]->get_review_rating();
	double avg = double(sum_ratings) / double(pointer_reviews_info.size());
	return avg;
}