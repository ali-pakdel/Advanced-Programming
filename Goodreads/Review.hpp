#ifndef REVIEW_HPP
#define REVIEW_HPP "REVIEW_HPP"

#include <string>
#include <vector>

#define REVIEW_ID 0
#define BOOK_ID_R 1
#define USER_ID_R 2
#define REVIEW_RATING 3
#define DATE 4
#define NO_LIKES 5

class Review
{
public:
	void set_no_likes(int _no_likes) { no_likes = _no_likes; }
	void set_book_ID(int _book_ID) { book_ID = _book_ID; }
	void set_review_rating(int _review_rating) { review_rating = _review_rating; }
	void set_user_ID(int _user_ID) { user_ID = _user_ID; }
	void set_review_ID(int _review_ID) { review_ID = _review_ID; }
	void set_date(std::string _date) { date = _date; }
	void set_review_info(std::vector<std::string> infos)
	{
		set_review_ID(stoi(infos[REVIEW_ID])); set_book_ID(stoi(infos[BOOK_ID_R]));
		set_user_ID(stoi(infos[USER_ID_R])); set_review_rating(stoi(infos[REVIEW_RATING]));
		set_date(infos[DATE]); set_no_likes(stoi(infos[NO_LIKES]));
	}

	int get_book_ID() { return book_ID; }
	int get_review_rating() { return review_rating; }
	int get_user_ID() { return user_ID; }
	int get_review_ID() { return review_ID; }
	int get_no_likes() { return no_likes; }
	std::string get_date() { return date; }

	void print_review_info();

private:
	int review_ID;
	int no_likes;
	int book_ID;
	int user_ID;
	int review_rating;
	std::string date;
};

typedef std::vector<Review*> pointerReviews;
typedef std::vector<Review> reviews;

#endif
