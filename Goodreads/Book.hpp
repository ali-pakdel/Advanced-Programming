#ifndef BOOK_HPP
#define BOOK_HPP "BOOK_HPP"

#include <string>
#include <vector>
#include <iostream>
#include "Review.hpp"

#define BOOK_ID_B 0
#define TITLE 1
#define AUTHOR_ID_B 2
#define GENRE 3

class Book
{
public:
	void set_book_ID(int _book_ID) { book_ID = _book_ID; }
	void set_title(std::string _title) { title = _title; }
	void set_author_ID(int _author_ID) { author_ID = _author_ID; }
	void set_genre(std::string _genre) { genre = _genre; }
	void set_book_info(std::vector<std::string> infos)
	{
		set_book_ID(stoi(infos[BOOK_ID_B])); set_title(infos[TITLE]);
		set_author_ID(stoi(infos[AUTHOR_ID_B])); set_genre(infos[GENRE]);
	}
	void set_reviews_info(Review* review_address) { pointer_reviews_info.push_back(review_address); }

	int get_author_ID() { return author_ID; }
	std::string get_title() { return title; }
	std::string get_genre() { return genre; }
	int get_book_ID() { return book_ID; }
	pointerReviews get_reviews_info() { return pointer_reviews_info; }

	void print_book_info();
	void print_book_shelf_info();
	double calculate_rating_avg();

private:
	int book_ID;
	int author_ID;
	std::string title;
	std::string genre;
	pointerReviews pointer_reviews_info;
};

typedef std::vector<Book*> pointerBooks;
typedef std::vector<Book> books;

#endif
