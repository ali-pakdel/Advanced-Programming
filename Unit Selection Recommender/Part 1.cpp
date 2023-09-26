#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>

#define COURSES_FILE_PATH "courses.csv"
#define GRADES_FILE_PATH "grades.csv"
#define DASH '-'
#define COMMA ','
#define SLASH '/'
#define COLON ':'
#define HUNDRED 100

using namespace std;

struct Schedule
{
	vector<string> days;
	vector<pair<int, int>> times;
};
typedef Schedule ScheduleTable;

struct Course
{
	int ID;
	string name;
	int units;
	ScheduleTable schedule;
	vector<int> prerequisites;
};
typedef vector<Course> CourseTable;

struct Grade
{
	int ID;
	float grade;
};
typedef vector<Grade> GradesTable;

void read_files(CourseTable& course_details, GradesTable& course_grades);
void read_course_info(CourseTable& course_details);
void read_course_grades(GradesTable& course_grades);
void find_takable_courses(CourseTable course_details, GradesTable course_grades);
vector<string> create_vector_of_names(CourseTable course_details);
bool comparison(string first, string second);
vector<string> alphabatically_sort(vector<string> names);
int find_course_ID(CourseTable course_details, string name1);
bool can_take(CourseTable course_details, GradesTable course_grades, 
			int course_ID, int course_num);
bool is_passed(CourseTable course_details, GradesTable course_grades,
			int course_ID);
int course_grade(GradesTable course_grades, int course_ID);
bool prerequisites_are_passed(CourseTable course_details, 
			GradesTable course_grades, int course_num);
void print_takable_courses(vector<int> takable_courses);
int find_course_num_by_ID(CourseTable course_details, int course_ID);

int main()
{
	CourseTable course_details;
	GradesTable course_grades;

	read_files(course_details, course_grades);
	find_takable_courses(course_details, course_grades);
}

void read_files(CourseTable& course_details, GradesTable& course_grades)
{
	read_course_info(course_details);
	read_course_grades(course_grades);
}
void read_course_info(CourseTable& course_details)
{
	string temp_ID;
	string temp_name;
	string temp_units;
	ifstream courseFile(COURSES_FILE_PATH);
	string dummy;
	string temp_prereq;
	string temp_schedule1;
	stringstream temp_schedule2;
	getline(courseFile, dummy);
	int i = 0, count_dash = 1, count_slash = 1;
	while (getline(courseFile, temp_ID, COMMA))
	{
		course_details.push_back(Course());
		course_details[i].ID = stoi(temp_ID);
		getline(courseFile, temp_name, COMMA);
		course_details[i].name = temp_name;
		getline(courseFile, temp_units, COMMA);
		course_details[i].units = stoi(temp_units);
		string temp_day = "";
		string temp_time = "";
		int first_time, last_time;
		int first_last = 1;
		int l = 0, k;
		int out_of_size = 0;
		getline(courseFile, temp_schedule1, COMMA);
		for (int j = 0; j < temp_schedule1.size(); j++)
			if (temp_schedule1[j] == SLASH)
				count_slash++;
		stringstream temp1;
		temp1 << temp_schedule1;
		for (int j = 0; j < count_slash - 1; j++)
		{
			getline(temp1, temp_day, DASH);
			course_details[i].schedule.days.push_back(temp_day);
			getline(temp1, temp_time, COLON);
			first_time = stoi(temp_time) * 100;
			getline(temp1, temp_time, DASH);
			first_time += stoi(temp_time);
			getline(temp1, temp_time, COLON);
			last_time = stoi(temp_time) * 100;
			getline(temp1, temp_time, SLASH);
			last_time += stoi(temp_time);
			course_details[i].schedule.times.push_back(make_pair(first_time, last_time));
			first_time = 0; 
			last_time = 0;
		}
		getline(temp1, temp_day, DASH);
		course_details[i].schedule.days.push_back(temp_day);
		getline(temp1, temp_time, COLON);
		first_time = stoi(temp_time) * 100;
		getline(temp1, temp_time, DASH);
		first_time += stoi(temp_time);
		getline(temp1, temp_time, COLON);
		last_time = stoi(temp_time) * 100;
		getline(temp1, temp_time, COMMA);
		last_time += stoi(temp_time);
		course_details[i].schedule.times.push_back(make_pair(first_time, last_time));
		count_slash = 1;
		getline(courseFile, temp_prereq);
		for (int j = 0; j < temp_prereq.size(); j++)
			if (temp_prereq[j] == DASH)
				count_dash++;
		stringstream temp2;
		temp1 << temp_prereq;
		for (int j = 1; j < count_dash; j++)
		{
			getline(temp1, temp_prereq, DASH);
			course_details[i].prerequisites.push_back(stoi(temp_prereq));
		}
		getline(temp1, temp_prereq, COMMA);
		course_details[i].prerequisites.push_back(stoi(temp_prereq));
		count_dash = 1;
		i++;
	}
}

void read_course_grades(GradesTable& course_grades)
{	
	ifstream gradesFile(GRADES_FILE_PATH);
	string temp_ID, temp_grade;
	int i = 0;
	string dummy;
	getline(gradesFile, dummy);
	while (getline(gradesFile, temp_ID, COMMA))
	{
		course_grades.push_back(Grade());
		course_grades[i].ID = stoi(temp_ID);
		getline(gradesFile, temp_grade);
		course_grades[i].grade = stof(temp_grade);
		i++;
	}
}
void find_takable_courses(CourseTable course_details, GradesTable course_grades)
{
	vector<int> takable_courses;
	vector<string> names = create_vector_of_names(course_details);
	vector<string> sorted_names = alphabatically_sort(names);
	for (int i = 0; i < sorted_names.size(); i++)
	{
		int course_ID = find_course_ID(course_details, sorted_names[i]);
		int course_num = find_course_num_by_ID(course_details, course_ID);
		if (can_take(course_details, course_grades, course_ID, course_num))
			takable_courses.push_back(course_details[course_num].ID);
	}
	print_takable_courses(takable_courses);
}

vector<string> create_vector_of_names(CourseTable course_details)
{
	vector<string> names;
	for (int i = 0; i < course_details.size(); i++)
		names.push_back(course_details[i].name);
	return names;
}

vector<string> alphabatically_sort(vector<string> names)
{
	sort(names.begin(), names.end(), comparison);
	return names;
}

bool comparison(string first, string second)
{
	return first < second;
}

int find_course_ID(CourseTable course_details, string name1)
{
	for (int i = 0; i < course_details.size(); i++)
	{
		if (name1 == course_details[i].name)
			return course_details[i].ID;
	}
}

bool can_take(CourseTable course_details, GradesTable course_grades, 
			int course_ID, int course_num)
{
	if (is_passed(course_details, course_grades, course_ID))
		return false;
	if (prerequisites_are_passed(course_details, course_grades, course_num))
		return true;
	else
		return false;
}

bool is_passed(CourseTable course_deatils, GradesTable course_grades, int course_ID)
{
	if (course_grade(course_grades, course_ID) >= 10)
		return true;
	else
		return false;
}

int course_grade(GradesTable course_grades, int course_ID)
{
	for (int i = 0; i < course_grades.size(); i++)
	{
		if (course_grades[i].ID == course_ID)
			return course_grades[i].grade;
	}
	return 0;
}

bool prerequisites_are_passed(CourseTable course_details, GradesTable course_grades,
			int course_num)
{
	if (course_details[course_num].prerequisites[0] > 0)
		for (int j = 0; j < course_details[course_num].prerequisites.size(); j++)
			if (!(is_passed(course_details, course_grades, course_details[course_num].prerequisites[j])))
				return false;
	return true;
}

void print_takable_courses(vector<int> takable_courses)
{
	for (int i = 0; i < takable_courses.size(); i++)
		cout << takable_courses[i] << endl;
}

int find_course_num_by_ID(CourseTable course_details, int course_ID)
{
	for (int i = 0; i < course_details.size(); i++)
		if (course_details[i].ID == course_ID)
			return i;
}