#include <string>

#include "Functions.hpp"
#include "GoodReads.hpp"

#define SHOW_AUTHOR_INFO "show_author_info"
#define SHOW_SORTED_SHELF "show_sorted_shelf"
#define CREDIT "credit"
#define BEST_BOOK "best_book"
#define BEST_REVIEWER "best_reviewer"
#define RECOMMEND_FIRST_APPROACH "recommend_first_approach"
#define RECOMMEND_SECOND_APPROACH "recommend_second_approach"

using namespace std;

void read_files(GoodReads& good_reads, std::string path)
{
	good_reads.read_authors(path);
	good_reads.read_books(path);
	good_reads.read_users(path);
	good_reads.read_reviews(path);
	good_reads.read_follow_edges(path);
}

void do_command(GoodReads good_reads, std::string command)
{
	if (command == SHOW_AUTHOR_INFO)
		good_reads.show_author_info();
	if (command == SHOW_SORTED_SHELF)
		good_reads.show_sorted_shelf();
	if (command == CREDIT)
		good_reads.credit();
	if (command == BEST_BOOK)
		good_reads.best_book();
	if (command == BEST_REVIEWER)
		good_reads.best_reviewer();
	if (command == RECOMMEND_FIRST_APPROACH)
		good_reads.recommend_first_approach();
	if (command == RECOMMEND_SECOND_APPROACH)
		good_reads.recommand_second_approach();
}
