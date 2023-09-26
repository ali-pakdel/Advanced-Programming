#ifndef GOOD_READS
#define GOOD_READS "GOOD_READS_HPP"

#include <string>
#include <vector>

#include "Author.hpp"
#include "Book.hpp"
#include "User.hpp"
#include "Review.hpp"

class GoodReads
{
public:
	std::vector<std::string> separate_line(std::string line, int NO);

	void read_authors(std::string path);
	std::vector<std::string> separate_author_genres(std::string line);

	void read_books(std::string path);

	void read_users(std::string path);
	std::vector<int> separate_user_favorite_authors(std::string line);
	std::vector<std::string> separate_user_favorite_genres(std::string line);
	std::vector<int> separate_user_want_to_reads(std::string line);
	std::vector<int> separate_user_currently_readings(std::string line);
	std::vector<int> separate_user_reads(std::string line);

	void read_reviews(std::string path);

	void read_follow_edges(std::string path);
	std::vector<int> separate_follow_edge_folloings(std::string line);

	void set_pointer_reviews_to_users();
	void set_pointer_reviews_to_books();
	void set_pointer_books_to_authors();
	void set_pointer_books_to_users();
	void set_pointer_authors_to_users();
	void set_pointer_want_to_read(int user_num);
	void set_pointer_currently_reading(int user_num);
	void set_pointer_read(int user_num);

	void set_no_all_review_likes(int no_all_review_likes_) { no_all_review_likes = no_all_review_likes_; }

	void show_author_info();

	void show_sorted_shelf();
	void which_shelf(int user_ID, std::string shelf_type, std::string genre);
	void print_shelf(pointerBooks shelf_books, std::string genre);

	void credit();
	double calculate_user_credit(int user_ID);
	void print_user_credit(double credit);

	void best_book();
	std::pair<int, double> find_max_rating_avg();
	void print_best_book_info(int book_ID, double max_avg);

	void best_reviewer();
	int find_max_reviews_sum_ID();
	void show_best_reviewer();

	void recommend_first_approach();
	int find_book_by_max_score(int user_ID);
	double calculate_score_by_credit(int book_ID);
	bool is_common_genre(int user_ID, int book_ID);

	void recommand_second_approach();
	void find_all_users(std::vector<int>& following_series_users, int i);
	bool is_repeated(int user_ID_, std::vector<int> users_ID);
	std::vector<int> recommend_all_books(std::vector<int> followings_series);
	int find_most_repeated_book(std::vector<int> all_recommended_books);

	void print_approach(int book_ID);

private:
	int no_all_review_likes;
	authors authors_info;
	books books_info;
	users users_info;
	reviews reviews_info;
};

#endif
