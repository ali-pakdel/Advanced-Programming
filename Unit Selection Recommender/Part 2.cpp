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
vector<int> find_takable_courses(CourseTable course_details, GradesTable course_grades);
vector<string> create_vector_of_names(CourseTable course_details);
bool comparison(string first, string second);
vector<string> alphabatically_sort(vector<string> names);
int find_course_ID_by_name(CourseTable course_details, string name1);
bool can_take(CourseTable course_details, GradesTable course_grades, int course_ID, int course_num);
bool is_passed(CourseTable course_details, GradesTable course_grades, int course_ID);
int course_grade(GradesTable course_grades, int course_ID);
bool prerequisites_are_passed(CourseTable course_details, GradesTable course_grades,
			int course_num);
void generate_output(CourseTable course_details, GradesTable course_grades, 
			vector<int> suggested_courses);
int find_course_num_by_ID(CourseTable course_details, int course_ID);
float calculate_GPA(CourseTable course_details, GradesTable course_grades);
vector<pair<int, int>> create_pair_ID_units(CourseTable course_details, vector<int> takable_courses);
vector<int> suggest_courses(CourseTable course_details, GradesTable course_grades);
vector<int> can_take_by_time(CourseTable course_details, vector<pair<int, int>> ID_units);
bool time_conflict(CourseTable course_details, int first_ID, int second_ID);
vector<pair<int, int>> sort_pair_by_second_element(vector<pair<int, int>> ID_units);
int max_units_can_taken(CourseTable course_details, GradesTable course_grades);

int main()
{
	CourseTable course_details;
	GradesTable course_grades;

	read_files(course_details, course_grades);
	vector<int> suggested_courses = suggest_courses(course_details, course_grades);
	generate_output(course_details, course_grades, suggested_courses);
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

vector<int> find_takable_courses(CourseTable course_details, GradesTable course_grades)
{
	vector<int> takable_courses;
	vector<string> names = create_vector_of_names(course_details);
	vector<string> sorted_names = alphabatically_sort(names);
	for (int i = 0; i < sorted_names.size(); i++)
	{
		int course_ID = find_course_ID_by_name(course_details, sorted_names[i]);
		int course_num = find_course_num_by_ID(course_details, course_ID);
		if (can_take(course_details, course_grades, course_ID, course_num))
			takable_courses.push_back(course_details[course_num].ID);
	}
	return takable_courses;
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

int find_course_ID_by_name(CourseTable course_details, string name1)
{
	for (int i = 0; i < course_details.size(); i++)
	{
		if (name1 == course_details[i].name)
			return course_details[i].ID;
	}
}

bool can_take(CourseTable course_details, GradesTable course_grades, int course_ID,
			int course_num)
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

void generate_output(CourseTable course_details, GradesTable course_grades, 
			vector<int> suggested_courses)
{
	vector<int> sorted_by_name = find_takable_courses(course_details, course_grades);
	for (int i = 0; i < sorted_by_name.size(); i++)
	{
		for (int j = 0; j < suggested_courses.size(); j++)
		{
			if (sorted_by_name[i] == suggested_courses[j])
				cout << suggested_courses[j] << endl;
		}
	}
}

int find_course_num_by_ID(CourseTable course_details, int course_ID)
{
	for (int i = 0; i < course_details.size(); i++)
		if (course_details[i].ID == course_ID)
			return i;
}

float calculate_GPA(CourseTable course_details, GradesTable course_grades)
{
	float grades_sum = 0;
	int units_sum = 0;
	for (int i = 0; i < course_grades.size(); i++)
	{
		int course_num = find_course_num_by_ID(course_details, course_grades[i].ID);
		grades_sum += course_details[course_num].units*course_grades[i].grade;
		units_sum += course_details[course_num].units;
	}
	return grades_sum / units_sum;
}

vector<pair<int, int>> create_pair_ID_units(CourseTable course_details,
			vector<int> takable_courses)
{
	vector<pair<int, int>> ID_units;
	for (int i = 0; i < takable_courses.size(); i++)
	{
		int first_element = takable_courses[i];
		int course_num = find_course_num_by_ID(course_details, takable_courses[i]);
		int second_element = course_details[course_num].units;
		ID_units.push_back(make_pair(first_element, second_element));
	}
	return ID_units;
}

vector<int> suggest_courses(CourseTable course_details, GradesTable course_grades)
{
	vector<int> suggested_courses;
	vector<int> takable_courses = find_takable_courses(course_details, course_grades);
	vector<pair<int, int>> ID_units = sort_pair_by_second_element(create_pair_ID_units(course_details, takable_courses));
	vector<int> intervention_courses = can_take_by_time(course_details, ID_units);
	int units_sum = 0;
	int max_units = max_units_can_taken(course_details, course_grades);
	for (int i = 0; i < ID_units.size(); i++)
	{
		if ((intervention_courses[i] == 1) && (units_sum + ID_units[i].second <= max_units))
		{
			suggested_courses.push_back(ID_units[i].first);
			units_sum += ID_units[i].second;
		}
	}
	return suggested_courses;
}

vector<pair<int, int>> sort_pair_by_second_element(vector<pair<int, int>> ID_units)
{
	sort(ID_units.begin(), ID_units.end(), [](const pair<int, int> &left, 
				const pair<int, int> &right) {
		return left.second > right.second;
	});
	return ID_units;
}

vector<int> can_take_by_time(CourseTable course_details, vector<pair<int, int>> ID_units)
{
	vector<int>	intervention_courses(ID_units.size(), 0);
	for (int i = 0; i < ID_units.size(); i++)
	{
		if (intervention_courses[i] == 0)
		{
			for (int j = i + 1; j < ID_units.size(); j++)
			{

				intervention_courses[i] = 1;
				if (time_conflict(course_details, ID_units[i].first, ID_units[j].first))
					intervention_courses[j] = -1;
			}
		}
	}
	return intervention_courses;
}

bool time_conflict(CourseTable course_details, int first_ID, int second_ID)
{
	int course_num1 = find_course_num_by_ID(course_details, first_ID);
	int course_num2 = find_course_num_by_ID(course_details, second_ID);
	for (int i = 0; i < course_details[course_num1].schedule.days.size(); i++)
	{
		for (int j = 0; j < course_details[course_num2].schedule.days.size(); j++)
		{
			if (course_details[course_num1].schedule.days[i] == course_details[course_num2].schedule.days[j])
			{
				if (!((course_details[course_num1].schedule.times[i].first >= 
						course_details[course_num2].schedule.times[j].second) ||
					(course_details[course_num1].schedule.times[i].second <= 
						course_details[course_num2].schedule.times[j].first)))
					return true;
			}
		}
	}
	return false;
}

int max_units_can_taken(CourseTable course_details, GradesTable course_grades)
{
	if (calculate_GPA(course_details, course_grades) >= 17)
		return 24;
	else
		return 20;
}