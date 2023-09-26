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
#define MAX_GRADE 20
#define NORMAL 0
#define VALID 1
#define INVALID -1
#define SEVENTHEEN 17
#define TWENTY 20
#define TWENTY_FOUR 24
#define OUTPUT_FILE_PATH "semester.sched"



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
bool can_take(CourseTable course_details, GradesTable course_grades,
			int course_ID, int course_num);
bool is_passed(GradesTable course_grades, int course_ID);
int course_grade(GradesTable course_grades, int course_ID);
bool prerequisites_are_passed(CourseTable course_details,
			GradesTable course_grades, int course_num);
void generate_output(CourseTable course_details, GradesTable course_grades,
			vector<int> suggested_courses, int semester_counter);
int find_course_num_by_ID(CourseTable course_details, int course_ID);
vector<pair<float, int>> calculate_GPA(CourseTable course_details, GradesTable course_grades);
vector<pair<int, int>> create_pair_ID_units(CourseTable course_details);
vector<int> suggest_courses(CourseTable course_details, GradesTable& course_grades,
			int& passed_courses, int semester_counter, vector<pair<float, int>>& GPA_units);
vector<int> can_take_by_time(CourseTable course_details, vector<int> takable_courses);
bool time_conflict(CourseTable course_details, int first_ID, int second_ID);
vector<pair<int, int>> sort_pair_int_int_by_second_element(vector<pair<int, int>> ID_units);
vector<pair<string, int>> sort_pair_str_int_by_first_element(vector<pair<string, int>> names_units);
vector<pair<string, int>> sort_pair_str_int_by_second_element(vector<pair<string, int>> names_units);
int max_units_can_taken(CourseTable course_details, GradesTable course_grades,
			int semester_counter, vector<pair<float, int>>& GPA_units);
float calculate_future_GPA(vector<pair<float, int>>& GPA);
float repeated_or_not_grade(GradesTable course_grades, int grade_num);
void suggest_all_semesters(CourseTable course_details, GradesTable course_grades);
vector<int> sort_IDs_by_name(CourseTable course_details, vector<int> suggested_courses);
vector<pair<string, int>> create_pair_name_units(CourseTable course_details);
vector<pair<string, int>> sort_by_name_and_units(vector<pair<string, int>> names_units);
void write_to_file(vector<int> sorted_IDs, int semester_counter);

int main()
{
	CourseTable course_details;
	GradesTable course_grades;

	read_files(course_details, course_grades);
	suggest_all_semesters(course_details, course_grades);
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
		string temp_prereq = "";
		getline(courseFile, temp_prereq);
		for (int j = 0; j < temp_prereq.size(); j++)
			if (temp_prereq[j] == DASH)
				count_dash++;
		stringstream temp2;
		temp2 << temp_prereq;
		for (int j = 1; j < count_dash; j++)
		{
			getline(temp2, temp_prereq, DASH);
			course_details[i].prerequisites.push_back(stoi(temp_prereq));
		}
		getline(temp2, temp_prereq, COMMA);
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

vector<pair<string, int>> create_pair_name_units(CourseTable course_details)
{
	vector<pair<string, int>> names_units;
	for (int i = 0; i < course_details.size(); i++)
		names_units.push_back(make_pair(course_details[i].name, course_details[i].units));
	return names_units;
}

vector<pair<string, int>> sort_by_name_and_units(vector<pair<string, int>> names_units)
{
	vector<pair<string, int>> sorted = sort_pair_str_int_by_first_element(names_units);
	return sort_pair_str_int_by_second_element(names_units);
}

vector<int> find_takable_courses(CourseTable course_details, GradesTable course_grades)
{
	vector<int> takable_courses;
	vector<pair<string, int>> names_units = sort_by_name_and_units(create_pair_name_units(course_details));
	int units_sum = 0;
	for (int i = 0; i < names_units.size(); i++)
	{
		int ID = find_course_ID_by_name(course_details, names_units[i].first);
		int course_num = find_course_num_by_ID(course_details, ID);
		if (can_take(course_details, course_grades, ID, course_num)) {
			takable_courses.push_back(ID);
			units_sum += names_units[i].second;
		}
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

bool can_take(CourseTable course_details, GradesTable course_grades, int course_ID, int course_num)
{
	if (is_passed(course_grades, course_ID))
		return false;
	if (prerequisites_are_passed(course_details, course_grades, course_num))
		return true;
	else
		return false;
}

bool is_passed(GradesTable course_grades, int course_ID)
{
	if (course_grade(course_grades, course_ID) >= 10)
		return true;
	else
		return false;
}

int course_grade(GradesTable course_grades, int course_ID)
{
	for (int i = course_grades.size() - 1; i >= 0; i--)
	{
		if (course_grades[i].ID == course_ID)
			return course_grades[i].grade;
	}
	return 0;
}

bool prerequisites_are_passed(CourseTable course_details, GradesTable course_grades, int course_num)
{
	if (course_details[course_num].prerequisites[0] > 0)
		for (int j = 0; j < course_details[course_num].prerequisites.size(); j++)
			if (!(is_passed(course_grades, course_details[course_num].prerequisites[j])))
				return false;
	return true;
}

void generate_output(CourseTable course_details, GradesTable course_grades,
			vector<int> suggested_courses, int semester_counter)
{	
	vector<int> sorted_IDs = sort_IDs_by_name(course_details, suggested_courses);
	write_to_file(sorted_IDs, semester_counter);
}

vector<int> sort_IDs_by_name(CourseTable course_details, vector<int> suggested_courses)
{
	vector<int> sorted_IDs;
	vector<string> names = create_vector_of_names(course_details);
	vector<string> sorted_names = alphabatically_sort(names);
	for (int i = 0; i < sorted_names.size(); i++)
		for (int j = 0; j < course_details.size(); j++)
			if (sorted_names[i] == course_details[j].name)
				for (int k = 0; k < suggested_courses.size(); k++)
					if (suggested_courses[k] == course_details[j].ID)
						sorted_IDs.push_back(suggested_courses[k]);
	return sorted_IDs;
}

int find_course_num_by_ID(CourseTable course_details, int course_ID)
{
	for (int i = 0; i < course_details.size(); i++)
		if (course_details[i].ID == course_ID)
			return i;
}

vector<pair<float, int>> calculate_GPA(CourseTable course_details, GradesTable course_grades)
{
	float grades_sum = 0;
	int units_sum = 0;
	int repeated_flag = 0;
	vector<pair<float, int>> GPA_units;
	for (int i = 0; i < course_grades.size(); i++)
	{
		int course_num = find_course_num_by_ID(course_details, course_grades[i].ID);
		grades_sum += (repeated_or_not_grade(course_grades, i))*course_details[course_num].units;
		units_sum += course_details[course_num].units;
	}
	GPA_units.push_back(make_pair(grades_sum / units_sum, units_sum));
	return GPA_units;
}

float repeated_or_not_grade(GradesTable course_grades, int grade_num)
{
	if (course_grades[grade_num].grade < 10)
		for (int i = grade_num + 1; i < course_grades.size(); i++)
			if (course_grades[grade_num].ID == course_grades[i].ID)
				return course_grades[i].grade;
	return course_grades[grade_num].grade;
}

vector<pair<int, int>> create_pair_ID_units(CourseTable course_details)
{
	vector<pair<int, int>> ID_units;
	for (int i = 0; i < course_details.size(); i++)
		ID_units.push_back(make_pair(course_details[i].ID, course_details[i].units));
	return ID_units;
}

vector<int> suggest_courses(CourseTable course_details, GradesTable& course_grades, int& passed_courses,
			int semester_counter, vector<pair<float, int>>& GPA_units)
{
	vector<int> suggested_courses;
	vector<int> takable_courses = find_takable_courses(course_details, course_grades);
	vector<int> intervention_courses = can_take_by_time(course_details, takable_courses);
	int units_sum = 0;
	int max_units = max_units_can_taken(course_details, course_grades, semester_counter, GPA_units);
	for (int i = 0; i < takable_courses.size(); i++)
	{
		int course_num = find_course_num_by_ID(course_details, takable_courses[i]);
		if ((intervention_courses[i] == VALID) && (units_sum + course_details[course_num].units <= max_units))
		{
			suggested_courses.push_back(takable_courses[i]);
			passed_courses++;
			units_sum += course_details[course_num].units;
			course_grades.push_back(Grade());
			course_grades[course_grades.size() - 1].grade = 10;
			course_grades[course_grades.size() - 1].ID = takable_courses[i];
		}
	}
	float next_term_GPA = calculate_future_GPA(GPA_units);
	GPA_units.push_back(make_pair(next_term_GPA, units_sum));
	return suggested_courses;
}

vector<pair<int, int>> sort_pair_int_int_by_second_element(vector<pair<int, int>> ID_units)
{
	sort(ID_units.begin(), ID_units.end(), [](const pair<int, int> &left, const pair<int, int> &right) {
		return left.second > right.second;
	});
	return ID_units;
}

vector<pair<string, int>> sort_pair_str_int_by_second_element(vector<pair<string, int>> names_units)
{
	sort(names_units.begin(), names_units.end(), [](const pair<string, int> &left,
				const pair<string, int> &right) {
		if (left.second == right.second)
			return left.first < right.first;
		return left.second > right.second;
	});
	return names_units;
}

vector<pair<string, int>> sort_pair_str_int_by_first_element(vector<pair<string, int>> names_units)
{
	sort(names_units.begin(), names_units.end(), [](const pair<string, int> &left,
				const pair<string, int> &right) {
		return left.first > right.first;
	});
	return names_units;
}

vector<int> can_take_by_time(CourseTable course_details, vector<int> takable_courses)
{
	vector<int>	intervention_courses(takable_courses.size(), NORMAL);
	if (takable_courses.size() == 1)
		intervention_courses[0] = VALID;
	for (int i = 0; i < takable_courses.size(); i++)
	{
		if (i == takable_courses.size() - 1 && intervention_courses[i] == NORMAL)
			intervention_courses[i] = VALID;
		if (intervention_courses[i] == NORMAL)
		{
			for (int j = i + 1; j < takable_courses.size(); j++)
			{
				intervention_courses[i] = VALID;
				if (time_conflict(course_details, takable_courses[i], takable_courses[j]))
					intervention_courses[j] = INVALID;
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

int max_units_can_taken(CourseTable course_details, GradesTable course_grades,
			int semester_counter,vector<pair<float, int>>& GPA_units)
{
	vector<pair<float, int>> total_GPA_units;
	if (semester_counter == 1) {
		total_GPA_units = calculate_GPA(course_details, course_grades);
		GPA_units.push_back(make_pair(total_GPA_units[0].first, total_GPA_units[0].second));
		if (total_GPA_units[0].first >= SEVENTHEEN)
			return TWENTY_FOUR;
		else
			return TWENTY;
	}
	if (calculate_future_GPA(GPA_units) >= SEVENTHEEN)
		return TWENTY_FOUR;
	else
		return TWENTY;
}

void suggest_all_semesters(CourseTable course_details, GradesTable course_grades)
{
	int semester_counter = 1;
	int passed_courses = 0;
	vector<pair<float, int>> GPA_units; 
	GPA_units.push_back(make_pair(0, 0));
	for (int i = 0; i < course_grades.size(); i++)
		if (course_grades[i].grade >= 10)
			passed_courses++;
	while (passed_courses < course_details.size())
	{
		vector<int> suggested_courses = suggest_courses(course_details, course_grades,
					passed_courses, semester_counter, GPA_units);
		semester_counter++;
		generate_output(course_details, course_grades, suggested_courses, semester_counter);
	}
}

float calculate_future_GPA(vector<pair<float, int>>& GPA_units)
{
	float GPAs_sum = 0;
	int units_sum = 0;
	for (int i = 1; i < GPA_units.size(); i++)
	{
		GPAs_sum += (GPA_units[i].first * GPA_units[i].second);
		units_sum += GPA_units[i].second;
	}
	if ((GPAs_sum / units_sum) + (5 * (GPAs_sum / units_sum) / 100) >= MAX_GRADE)
		GPA_units[0].first = MAX_GRADE;
	else
		GPA_units[0].first = (GPAs_sum / units_sum) + (5 * (GPAs_sum / units_sum) / 100);
	return GPA_units[0].first;
}


void write_to_file(vector<int> sorted_IDs, int semester_counter)
{
	string defualt_path = OUTPUT_FILE_PATH;
	defualt_path.insert(8, to_string(semester_counter - 1));
	stringstream temp;
	ofstream output_file(defualt_path);
	for (int i = 0; i < sorted_IDs.size(); i++)
		output_file << sorted_IDs[i] << endl;
}