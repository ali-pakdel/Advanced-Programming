#ifndef AUTHOR_HPP 
#define AUTHOR_HPP "AUTHOR_HPP" 

#include <string>
#include <vector>

#include "Book.hpp"

#define AUTHOR_ID_A 0
#define AUTHOR_NAME_A 1
#define GENDER 2
#define AUTHOR_MEMBER_SINCE 3
#define AUTHOR_BIRTH_YEAR 4
#define AUTHOR_BIRTH_PLACE 5
#define FIRST_GENRE 7

class Author
{
public:
	void set_author_ID(int _ID) { author_ID = _ID; }
	void set_name(std::string _name) { author_name = _name; }
	void set_gender(std::string _gender) { gender = _gender; }
	void set_member_since(std::string _member_since) { member_since = _member_since; }
	void set_year_of_birth(int _year_of_birth) { year_of_birth = _year_of_birth; }
	void set_place_of_birth(std::string _place_of_birth) { place_of_birth = _place_of_birth; }
	void set_genres(std::vector<std::string> _genres) { genres = _genres; }
	void set_author_info(std::vector<std::string> infos, std::vector<std::string> _genres)
	{
		set_author_ID(std::stoi(infos[AUTHOR_ID_A]));
		set_name(infos[AUTHOR_NAME_A]);
		set_gender(infos[GENDER]);
		set_member_since(infos[AUTHOR_MEMBER_SINCE]);
		set_year_of_birth(std::stoi(infos[AUTHOR_BIRTH_YEAR]));
		set_place_of_birth(infos[AUTHOR_BIRTH_PLACE]);
		set_genres(_genres);
	}
	void set_books_info(Book* address_book) { pointer_books_info.push_back(address_book); }

	int get_author_ID() { return author_ID; }
	std::string get_author_name() { return author_name; }
	std::string get_member_since() { return member_since; }
	int get_year_of_birth() { return year_of_birth; }
	std::string get_place_of_birth() { return place_of_birth; }
	std::string get_genre_i(int i) { return genres[i]; }
	int get_size_genres() { return genres.size(); }
	pointerBooks get_books_info() { return pointer_books_info; }

	void print_author_all_infos();
	void print_author_info();
	void print_author_genres();
	void print_author_books_info();

private:
	int author_ID;
	int year_of_birth;
	std::string author_name;
	std::string gender;
	std::string member_since;
	std::string place_of_birth;
	std::vector<std::string> genres;
	pointerBooks pointer_books_info;
};

typedef std::vector<Author> authors;
typedef std::vector<Author*> pointerAuthors;

#endif
