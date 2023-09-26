#ifndef USER_HPP
#define USER_HPP "USER_HPP"

#include <string>
#include <vector>

#include "Book.hpp"
#include "Review.hpp"
#include "Author.hpp"

#define USER_ID_U 0
#define USER_NAME_U 1
#define USER_BIRTH_PLACE 2
#define USER_MEMBER_SINCE 3

class User
{
public:
	void set_user_ID(int _user_ID) { user_ID = _user_ID; }
	void set_user_name(std::string _user_name) { user_name = _user_name; }
	void set_place_of_birth(std::string _place_of_birth) { place_of_birth = _place_of_birth; }
	void set_member_since(std::string _member_since) { member_since = _member_since; }
	void set_favorite_authors_ID(std::vector<int> _authors_ID) { favorite_authors = _authors_ID; }
	void set_favorite_genres(std::vector<std::string> _genres) { favorite_genres = _genres; }
	void set_want_to_read(std::vector<int> _books_ID) { want_to_read = _books_ID; }
	void set_currently_reading(std::vector<int> _books_ID) { currently_reading = _books_ID; }
	void set_read(std::vector<int> _books_ID) { read = _books_ID; }
	void set_pointer_want_to_read(Book* address) { pointer_want_to_read.push_back(address); }
	void set_pointer_currently_reading(Book* address) { pointer_currently_reading.push_back(address); }
	void set_pointer_read(Book* address) { pointer_read.push_back(address); }
	void set_pointer_favorite_authors(Author* address) { pointer_authors_info.push_back(address); }
	void set_followings(std::vector<int> _users_ID) { followings = _users_ID; }
	void set_reviews_info(Review* address) { pointer_reviews_info.push_back(address); }
	void set_user_info(std::vector<std::string> infos, std::vector<int> _favorite_authors,
		std::vector<std::string> _favorite_genres, std::vector<int> _want_to_read,
		std::vector<int> _currently_reading, std::vector<int> _read)
	{
		set_user_ID(stoi(infos[USER_ID_U])); set_user_name(infos[USER_NAME_U]);
		set_place_of_birth(infos[USER_BIRTH_PLACE]); set_member_since(infos[USER_MEMBER_SINCE]);
		set_favorite_authors_ID(_favorite_authors); set_favorite_genres(_favorite_genres);
		set_want_to_read(_want_to_read); set_currently_reading(_currently_reading); set_read(_read);
	}

	int get_user_ID() { return user_ID; }
	std::string get_user_name() { return user_name; }
	std::string get_place_of_birth() { return place_of_birth; }
	std::string get_member_since() { return member_since; }
	std::vector<int> get_favorite_authors_ID() { return favorite_authors; }
	std::vector<std::string> get_favorite_genres() { return favorite_genres; }
	std::vector<int> get_want_to_read() { return want_to_read; }
	std::vector<int> get_currently_reading() { return currently_reading; }
	std::vector<int> get_read() { return read; }
	std::vector<int> get_followings() { return followings; }
	pointerBooks get_pointer_want_to_read() { return pointer_want_to_read; }
	pointerBooks get_pointer_currently_reading() { return pointer_currently_reading; }
	pointerBooks get_pointer_read() { return pointer_read; }
	pointerReviews get_reviews_info() { return pointer_reviews_info; }

	void print_best_reviewer();
	void print_user_info();
	void print_favorite_genres();
	void print_favorite_authors();
	void print_no_books_in_shelf();
	int calculate_likes_sum();

private:
	int user_ID;
	std::string user_name;
	std::string place_of_birth;
	std::string member_since;
	std::vector<int> followings;
	std::vector<int> favorite_authors;
	std::vector<int> want_to_read;
	std::vector<int> currently_reading;
	std::vector<int> read;
	std::vector<std::string> favorite_genres;
	pointerBooks pointer_want_to_read;
	pointerBooks pointer_currently_reading;
	pointerBooks pointer_read;
	pointerReviews pointer_reviews_info;
	pointerAuthors pointer_authors_info;
};

typedef std::vector<User> users;

#endif
