#include "Rating.hpp"

using namespace std;

Rating::Rating(vector<string> ratings)
{
    username = ratings[0];
    location = stod(ratings[2]);
    cleanliness = stod(ratings[3]);
    staff = stod(ratings[4]);
    facilities = stod(ratings[5]);
    value_for_money = stod(ratings[6]);
    overall = stod(ratings[7]);
}

void Rating::replace_ratings(vector<string> ratings)
{
    location = stod(ratings[1]);
    cleanliness = stod(ratings[2]);
    staff = stod(ratings[3]);
    facilities = stod(ratings[4]);
    value_for_money = stod(ratings[5]);
    overall = stod(ratings[6]);
}