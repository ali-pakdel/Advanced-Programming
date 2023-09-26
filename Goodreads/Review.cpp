#include <iostream>

#include "Review.hpp"

using namespace std;

void Review::print_review_info()
{
	cout << "id: " << review_ID << " Rating: " << review_rating
		 << " Likes: " << no_likes << " Date: " << date << endl;
}