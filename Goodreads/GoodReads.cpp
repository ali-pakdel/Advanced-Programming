#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

#include "GoodReads.hpp"

#define ASSETS_SIZE 6
#define AUTHORS_FILE_PATH "/authors.csv"
#define BOOKS_FILE_PATH "/books.csv"
#define USERS_FILE_PATH "/users.csv"
#define REVIEWS_FILE_PATH "/reviews.csv"
#define FOLLOW_EDGES "/follow_edges.csv"
#define COMMA ','
#define DOLLAR '$'
#define NO_AUTHOR_INFOS 6
#define GENRES 6
#define NO_BOOK_INFOS 3
#define NO_USER_INFOS 8
#define FAVORITE_AUTHORS 4
#define FAVORITE_GENRES 5
#define WANT_TO_READ_ 6
#define CURRENTLY_READING_ 7
#define READ_ 8
#define NO_REVIEW_INFOS 5
#define NO_FOLLOW_EDGE_INFOS 1
#define FOLLOWINGS 1
#define USER_ID_G 0
#define INITIALIZE 0
#define NO_LIKES_G 5
#define TWO 2.0
#define THREE 3
#define WANT_TO_READ "want_to_read"
#define CURRENTLY_READING "currently_reading"
#define READ "read"

using namespace std;

vector<string> GoodReads::separate_line(string line, int no_infos)
{
	vector<string> infos;
	string word;
	stringstream temp_line;
	temp_line << line;
	for (int i = 0; getline(temp_line, word, COMMA); i++)
	{
		infos.push_back(word);
		if (i == no_infos)
			break;
	}
	return infos;
}

void GoodReads::read_authors(string path)
{
	path.insert(ASSETS_SIZE, AUTHORS_FILE_PATH);
	ifstream input_file(path);

	string line;
	vector<string> infos;
	vector<string> genres;
	getline(input_file, line);
	for (int i = 0; getline(input_file, line); i++)
	{
		authors_info.push_back(Author());
		infos = separate_line(line, NO_AUTHOR_INFOS);
		genres = separate_author_genres(infos[GENRES]);
		authors_info[i].set_author_info(infos, genres);
	}
}
vector<string> GoodReads::separate_author_genres(string line)
{
	string genre;
	stringstream temp_line;
	vector<string> genres;
	temp_line << line;
	while (getline(temp_line, genre, DOLLAR))
		genres.push_back(genre);
	return genres;
}

void GoodReads::read_books(string path)
{
	path.insert(ASSETS_SIZE, BOOKS_FILE_PATH);
	ifstream input_file(path);

	string line;
	vector<string> infos;

	getline(input_file, line);
	for (int i = 0; getline(input_file, line); i++)
	{
		books_info.push_back(Book());
		infos = separate_line(line, NO_BOOK_INFOS);
		books_info[i].set_book_info(infos);
	}
}

void GoodReads::read_users(string path)
{
	path.insert(ASSETS_SIZE, USERS_FILE_PATH);
	ifstream input_file(path);

	string line;
	vector<string> infos;
	vector<int> favorite_authors;
	vector<string> favorite_genres;
	vector<int> want_to_read;
	vector<int> currently_reading;
	vector<int> read;

	getline(input_file, line);
	for (int i = 0; getline(input_file, line); i++)
	{
		users_info.push_back(User());
		infos = separate_line(line, NO_USER_INFOS);
		favorite_authors = separate_user_favorite_authors(infos[FAVORITE_AUTHORS]);
		favorite_genres = separate_user_favorite_genres(infos[FAVORITE_GENRES]);
		want_to_read = separate_user_want_to_reads(infos[WANT_TO_READ_]);
		currently_reading = separate_user_currently_readings(infos[CURRENTLY_READING_]);
		read = separate_user_reads(infos[READ_]);
		users_info[i].set_user_info(infos, favorite_authors, favorite_genres,
			want_to_read, currently_reading, read);
	}
}
vector<int> GoodReads::separate_user_favorite_authors(string line)
{
	vector<int> favorite_authors;
	string word;
	stringstream temp_line;
	temp_line << line;

	while (getline(temp_line, word, DOLLAR))
		favorite_authors.push_back(stoi(word));

	return favorite_authors;
}
vector<string> GoodReads::separate_user_favorite_genres(string line)
{
	vector<string> favorite_genres;
	string word;
	stringstream temp_line;
	temp_line << line;

	while (getline(temp_line, word, DOLLAR))
		favorite_genres.push_back(word);

	return favorite_genres;
}
vector<int> GoodReads::separate_user_want_to_reads(string line)
{
	vector<int> want_to_read;
	string word;
	stringstream temp_line;
	temp_line << line;

	while (getline(temp_line, word, DOLLAR))
		want_to_read.push_back(stoi(word));

	return want_to_read;
}
vector<int> GoodReads::separate_user_currently_readings(string line)
{
	vector<int> currently_reading;
	string word;
	stringstream temp_line;
	temp_line << line;

	while (getline(temp_line, word, DOLLAR))
		currently_reading.push_back(stoi(word));

	return currently_reading;
}
vector<int> GoodReads::separate_user_reads(string line)
{
	vector<int> read;
	string word;
	stringstream temp_line;
	temp_line << line;

	while (getline(temp_line, word, DOLLAR))
		read.push_back(stoi(word));

	return read;
}

void GoodReads::read_reviews(string path)
{
	path.insert(ASSETS_SIZE, REVIEWS_FILE_PATH);
	ifstream input_file(path);

	string line;
	vector<string> infos;
	int no_all_review_likes = 0;
	int prevoius_likes = 0;
	getline(input_file, line);
	for (int i = 0; getline(input_file, line); i++)
	{
		reviews_info.push_back(Review());
		infos = separate_line(line, NO_REVIEW_INFOS);
		reviews_info[i].set_review_info(infos);
		no_all_review_likes += stoi(infos[NO_LIKES_G]);
	}
	set_no_all_review_likes(no_all_review_likes);
}

void GoodReads::read_follow_edges(string path)
{
	path.insert(ASSETS_SIZE, FOLLOW_EDGES);
	ifstream input_file(path);

	string line;
	vector<string> infos;
	vector<int> followings;
	getline(input_file, line);
	while (getline(input_file, line))
	{
		infos = separate_line(line, NO_FOLLOW_EDGE_INFOS);
		followings = separate_follow_edge_folloings(infos[FOLLOWINGS]);
		users_info[stoi(infos[USER_ID_G])].set_followings(followings);
	}
}
vector<int> GoodReads::separate_follow_edge_folloings(string line)
{
	vector<int> followings;
	stringstream temp_line;
	temp_line << line;
	string word;
	while (getline(temp_line, word, DOLLAR))
		followings.push_back(stoi(word));
	return followings;
}

void GoodReads::set_pointer_books_to_authors()
{
	for (int i = 0; i < books_info.size(); i++)
	{
		int author_num = books_info[i].get_author_ID();
		authors_info[author_num].set_books_info(&books_info[i]);
	}
}
void GoodReads::set_pointer_reviews_to_users()
{
	for (int i = 0; i < reviews_info.size(); i++)
	{
		int user_ID = reviews_info[i].get_user_ID();
		users_info[user_ID].set_reviews_info(&reviews_info[i]);
	}
}
void GoodReads::set_pointer_reviews_to_books()
{
	for (int i = 0; i < reviews_info.size(); i++)
	{
		int book_num = reviews_info[i].get_book_ID();
		books_info[book_num].set_reviews_info(&reviews_info[i]);
	}
}
void GoodReads::set_pointer_books_to_users()
{
	for (int i = 0; i < users_info.size(); i++)
	{
		set_pointer_want_to_read(i);
		set_pointer_currently_reading(i);
		set_pointer_read(i);
	}
}
void GoodReads::set_pointer_authors_to_users()
{
	for (int i = 0; i < users_info.size(); i++)
		for (int j = 0; j < users_info[i].get_favorite_authors_ID().size(); j++)
		{
			int author_ID = users_info[i].get_favorite_authors_ID()[j];
			users_info[i].set_pointer_favorite_authors(&authors_info[author_ID]);
		}
}

void GoodReads::set_pointer_want_to_read(int user_num)
{
	for (int i = 0; i < users_info[user_num].get_want_to_read().size(); i++)
	{
		int book_num = users_info[user_num].get_want_to_read()[i];
		users_info[user_num].set_pointer_want_to_read(&books_info[book_num]);
	}
}
void GoodReads::set_pointer_currently_reading(int user_num)
{
	for (int i = 0; i < users_info[user_num].get_currently_reading().size(); i++)
	{
		int book_num = users_info[user_num].get_currently_reading()[i];
		users_info[user_num].set_pointer_currently_reading(&books_info[book_num]);
	}
}
void GoodReads::set_pointer_read(int user_num)
{
	for (int i = 0; i < users_info[user_num].get_read().size(); i++)
	{
		int book_num = users_info[user_num].get_read()[i];
		users_info[user_num].set_pointer_read(&books_info[book_num]);
	}
}

void GoodReads::show_author_info()
{
	set_pointer_books_to_authors();
	int author_ID;
	cin >> author_ID;
	authors_info[author_ID].print_author_all_infos();
}

void GoodReads::show_sorted_shelf()
{
	set_pointer_books_to_users();
	int user_ID;
	string shelf_type, genre;
	cin >> user_ID >> shelf_type;
	getline(cin >> ws, genre);
	which_shelf(user_ID, shelf_type, genre);
}
void GoodReads::which_shelf(int user_ID, string shelf_type, string genre)
{
	if (shelf_type == WANT_TO_READ)
		print_shelf(users_info[user_ID].get_pointer_want_to_read(), genre);
	if (shelf_type == CURRENTLY_READING)
		print_shelf(users_info[user_ID].get_pointer_currently_reading(), genre);
	if (shelf_type == READ)
		print_shelf(users_info[user_ID].get_pointer_read(), genre);
}
void GoodReads::print_shelf(pointerBooks shelf_books, string genre)
{
	auto shelf = shelf_books;
	sort(shelf.begin(), shelf.end(), [](Book* a, Book* b) { return a->get_title() < b->get_title(); });

	for (int i = 0; i < shelf.size(); i++)
		for (int j = i + 1; j < shelf.size(); j++)
			if ((shelf[i]->get_title() == shelf[j]->get_title()) && (shelf[i]->get_book_ID() > shelf[j]->get_book_ID())) 
				swap(shelf[i], shelf[j]);

	for (int i = 0; i < shelf.size(); i++)
	{
		if (shelf[i]->get_genre() == genre)
		{
			shelf[i]->print_book_shelf_info();
			cout << "Author: " << authors_info[shelf[i]->
			get_author_ID()].get_author_name()
			<< endl << "***" << endl;
		}
	}
	for (int i = 0; i < shelf.size(); i++)
	{
		if (shelf[i]->get_genre() != genre)
		{
			shelf[i]->print_book_shelf_info();
			cout << "Author: " << authors_info[shelf[i]->
			get_author_ID()].get_author_name()
			<< endl << "***" << endl;
		}
	}
}

void GoodReads::credit()
{
	set_pointer_reviews_to_users();
	int user_ID;
	cin >> user_ID;
	double credit = calculate_user_credit(user_ID);
	print_user_credit(credit);
}
double GoodReads::calculate_user_credit(int user_ID)
{
	double likes_avg = 0;
	double reviews_avg = 0;

	if (no_all_review_likes != 0)
		likes_avg = (double(users_info[user_ID].calculate_likes_sum())
			/ no_all_review_likes);
	if (reviews_info.size() != 0)
		reviews_avg = double(users_info[user_ID].get_reviews_info().size()) / double(reviews_info.size());

	return (likes_avg + reviews_avg) / TWO;
}
void GoodReads::print_user_credit(double credit)
{
	cout << fixed << setprecision(6) << credit << endl;
}

void GoodReads::best_book()
{
	set_pointer_reviews_to_books();
	pair<int, double> book_ID_avg = find_max_rating_avg();
	print_best_book_info(book_ID_avg.first, book_ID_avg.second);
}
pair<int, double> GoodReads::find_max_rating_avg()
{
	pair<int, double> book_num_avg(0, 0);
	double rating;
	for (int i = 0; i < books_info.size(); i++)
	{
		rating = books_info[i].calculate_rating_avg();
		if (rating > book_num_avg.second)
		{
			book_num_avg.second = rating;
			book_num_avg.first = i;
		}
	}
	return book_num_avg;
}
void GoodReads::print_best_book_info(int book_ID, double max_avg)
{
	int author_ID = books_info[book_ID].get_author_ID();
	books_info[book_ID].print_book_shelf_info();
	cout << "Author: " << authors_info[author_ID].get_author_name()
	<< endl << "Average Rating: " << fixed << setprecision(2) << max_avg << endl;
}

void GoodReads::best_reviewer()
{
	set_pointer_reviews_to_users();
	set_pointer_authors_to_users();
	show_best_reviewer();
}
int GoodReads::find_max_reviews_sum_ID()
{
	int user_ID;
	int max_review_sum = -1;
	int review_sum = 0;
	for (int i = 0; i < users_info.size(); i++)
	{
		review_sum = users_info[i].calculate_likes_sum();
		if (review_sum != -1)
		{
			if (review_sum > max_review_sum)
			{
				max_review_sum = review_sum;
				user_ID = i;
			}
		}
	}
	return user_ID;
}
void GoodReads::show_best_reviewer()
{
	int user_ID = find_max_reviews_sum_ID();
	if ( 0 <= user_ID <= users_info.size())
		users_info[user_ID].print_best_reviewer();
}

void GoodReads::recommend_first_approach()
{
	set_pointer_reviews_to_books();
	set_pointer_reviews_to_users();
	int user_ID;
	cin >> user_ID;
	int book_ID = find_book_by_max_score(user_ID);
	print_approach(book_ID);
}
int GoodReads::find_book_by_max_score(int user_ID)
{
	double rating = 0;
	double max_rating = 0;
	int max_book_ID;
	for (int book_ID = 0; book_ID < books_info.size(); book_ID++)
	{
		rating = calculate_score_by_credit(book_ID);
		if (is_common_genre(user_ID, book_ID))
			rating += 5;
		if (rating > max_rating)
		{
			max_rating = rating;
			max_book_ID = book_ID;
		}
	}
	return max_book_ID;
}
double GoodReads::calculate_score_by_credit(int book_ID)
{
	if (books_info[book_ID].get_reviews_info().size() == 0)
		return 0;
	double sum_rating_x_credit = 0;
	double rating = 0;
	double credit = 0;

	for (int i = 0; i < books_info[book_ID].get_reviews_info().size(); i++)
	{
		rating = double(books_info[book_ID].get_reviews_info()[i]->
			get_review_rating());
		credit = double(calculate_user_credit(books_info[book_ID].
			get_reviews_info()[i]->get_user_ID()));
		sum_rating_x_credit += (rating * credit);
	}
	return sum_rating_x_credit / books_info[book_ID].get_reviews_info().size();
}
bool GoodReads::is_common_genre(int user_ID, int book_ID)
{
	for (int i = 0; i < users_info[user_ID].get_favorite_genres().size(); i++)
		if (users_info[user_ID].get_favorite_genres()[i] ==
			books_info[book_ID].get_genre())
			return true;
	return false;
}

void GoodReads::recommand_second_approach()
{
	set_pointer_reviews_to_users();
	set_pointer_reviews_to_books();
	int user_ID;
	cin >> user_ID;
	vector<int> all_following_series;
	find_all_users(all_following_series, user_ID);
	vector<int> all_recommended_books = recommend_all_books(all_following_series);
	sort(all_recommended_books.begin(), all_recommended_books.end());
	int book_ID = find_most_repeated_book(all_recommended_books);
	print_approach(book_ID);
}
void GoodReads::find_all_users(vector<int>& follownig_series_users, int user_ID)
{
	if (!(is_repeated(user_ID, follownig_series_users)))
	{
		follownig_series_users.push_back(user_ID);

		for (int i = 0; i < users_info[user_ID].get_followings().size(); i++)
			find_all_users(follownig_series_users, users_info[user_ID].
				get_followings()[i]);
	}
}
bool GoodReads::is_repeated(int user_ID_, vector<int> following_series)
{
	for (int i = 0; i < following_series.size(); i++)
		if (following_series[i] == user_ID_)
			return true;
	return false;
}
vector<int> GoodReads::recommend_all_books(vector<int> followings_series)
{
	vector<int> recommended_books;
	for (int i = 1; i < followings_series.size(); i++)
	{
		vector<pair<double, int>> scores_book_ID;
		for (int j = 0; j < users_info[followings_series[i]].get_read().size(); j++)
			scores_book_ID.push_back(make_pair
			(calculate_score_by_credit(users_info[followings_series[i]].get_read()[j]),
				users_info[followings_series[i]].get_read()[j]));
		sort(scores_book_ID.begin(), scores_book_ID.end(), [](const pair<double, int>& left, const pair<double, int>& right) {
			if (left.first == right.first)
				return left.second < right.second;
			return left.first > right.first; });

		for (int j = 0; j < THREE; j++)
			recommended_books.push_back(scores_book_ID[j].second);
	}
	return recommended_books;
}
int GoodReads::find_most_repeated_book(vector<int> all_recommended_books)
{
	int book_ID, max_counter = 0;
	for (int i = 0; i < all_recommended_books.size(); i++)
	{
		int counter = 1;
		for (int j = i; all_recommended_books[i] == all_recommended_books[j]; j++)
		{
			counter++;
			if (j + 1 == all_recommended_books.size())
				break;
		}
		if (counter > max_counter)
		{
			max_counter = counter;
			book_ID = all_recommended_books[i];
		}
	}
	return book_ID;
}
void GoodReads::print_approach(int book_ID)
{
	books_info[book_ID].print_book_shelf_info();
	cout << "Author: " << authors_info[books_info[book_ID].
			get_author_ID()].get_author_name() << endl 
			<< "Reviews:" << endl;
	for (int i = 0; i < books_info[book_ID].get_reviews_info().size(); i++)
		books_info[book_ID].get_reviews_info()[i]->print_review_info();
}

