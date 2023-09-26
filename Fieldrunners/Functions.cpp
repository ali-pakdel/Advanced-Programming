#include <sstream>
#include <string>

#include "Functions.hpp"
#include "Fieldrunners.hpp"

#define UPGRADE 'u'
#define UP_PATH "path_up.png"
#define DOWN_PATH "path_down.png"
#define LEFT_PATH "path_left.png"
#define RIGHT_PATH "path_right.png"
#define BACKGROUND_IMAGE_PATH "background.png"
#define BACKGROUND_HEIGHT 1024
#define BACKGROUND_WIDTH 1365
#define ORIGIN 0
#define NO_ENEMIES 4
#define HEART_IMAGE "heart"
#define PNG ".png"
#define HEART_IMAGE_X0 1200
#define HEART_IMAGE_Y0 150
#define HEART_IMAGE_WIDTH 30
#define HEART_IMAGE_HEIGHT 30
#define MONEY_BACKGROUND "sscore.png"
#define MY_FONT "OpenSans.ttf"
#define FONT_SIZE 15
#define FONT1_X0 1180
#define FONT1_Y0 120
#define FONT2_X0 1000
#define FONT2_Y0 120
#define CUBE_SIZE 60
#define PATH_WIDTH 40
#define PATH_HEIGHT 20
#define PATH_X0 133
#define PATH_Y0 193
#define MONEY_BACKGROUND_X0 300
#define MONEY_BACKGROUND_Y0 150
#define MONEY_BACKGROUND_WIDTH 60
#define MONEY_BACKGROUND_HEIGHT 30
#define MONEY_ "Money: "



using namespace std;

WaveInfo get_input()
{
	WaveInfo wave_info;
	wave_info.movment_path = get_movment_path();
	wave_info.no_each_enemy = get_no_each_enemy();
	return wave_info;
}

vector<pair<int, int>> get_movment_path()
{
	vector<pair<int, int>> movment_path;
	int x, y;
	string line;
	getline(cin, line);
	stringstream word(line);
	for (int i = 0; word >> x; i++)
	{
		movment_path.push_back(make_pair(x, 0));
		word >> y;
		movment_path[i].second = y;
	}
	vector<pair<int, int>> new_path = make_path(movment_path);
	return new_path;
}

vector<vector<int>> get_no_each_enemy()
{
	int count;
	string line;
	vector<vector<int>> no_each_enemy;
	for (int i = 0; getline(cin, line); i++)
	{
		stringstream word1(line);
		vector<int> temp;
		while (word1 >> count)
			temp.push_back(count);
		no_each_enemy.push_back(temp);
	}
	return no_each_enemy;
}

vector<pair<int, int>> make_path(vector<pair<int, int>> path)
{
	vector<pair<int, int>> new_path;
	int count;
	new_path.push_back(path[0]);
	for (int i = 0; i < path.size(); i++)
	{
		if (new_path[new_path.size() - 1].first < path[i].first &&
			new_path[new_path.size() - 1].second == path[i].second)
		{
			count = path[i].first - new_path[new_path.size() - 1].first;
			for (int j = 0; j <count; j++)
				new_path.push_back(make_pair(new_path[new_path.size() - 1].first + 1, path[i].second));
		}

		if (new_path[new_path.size() - 1].first == path[i].first &&
			new_path[new_path.size() - 1].second < path[i].second)
		{
			count = path[i].second - new_path[new_path.size() - 1].second;
			for (int j = 0; j < count; j++)
				new_path.push_back(make_pair(path[i].first, new_path[new_path.size() - 1].second + 1));
		}

		if (new_path[new_path.size() - 1].first == path[i].first &&
			new_path[new_path.size() - 1].second > path[i].second)
		{
			count = new_path[new_path.size() - 1].second - path[i].second;
			for (int j = 0; j < count; j++)
				new_path.push_back(make_pair(path[i].first, new_path[new_path.size() - 1].second - 1));
		}

		if (new_path[new_path.size() - 1].first > path[i].first &&
			new_path[new_path.size() - 1].second == path[i].second)
		{
			count = new_path[new_path.size() - 1].first - path[i].first;
			for (int j = 0; j < count; j++)
				new_path.push_back(make_pair(new_path[new_path.size() - 1].first - 1, path[i].second));
		}
	}
	return new_path;
}

pair<float, float> update(Window* window, FieldRunners& game, pair<float, float> mouse_position)
{
	Point _mouse_position;
	while (window->has_pending_event())
	{
		Event event = window->poll_for_event();
		switch (event.get_type())
		{
		case Event::EventType::LCLICK:
			_mouse_position = event.get_mouse_position();
			mouse_position.first = _mouse_position.x; mouse_position.second = _mouse_position.y;
			break;
		case Event::EventType::KEY_PRESS:
			if (event.get_pressed_key() == UPGRADE)
				game.upgrade_tower(window, mouse_position);
			else
				game.set_towers(event.get_pressed_key(), mouse_position);
			break;
		case Event::EventType::QUIT:
			exit(0);
			break;
		}
	}
	return mouse_position;
}

void draw_path_guide(Window* window, WaveInfo wave_info)
{
	for (int i = 0; i < wave_info.movment_path.size() - 2; i++)
	{
		if (wave_info.movment_path[i].first == wave_info.movment_path[i + 1].first &&
			wave_info.movment_path[i].second > wave_info.movment_path[i + 1].second)
			window->draw_img(UP_PATH, Rectangle((wave_info.movment_path[i].first * CUBE_SIZE) + PATH_X0,
			(wave_info.movment_path[i].second * CUBE_SIZE) + PATH_Y0, PATH_WIDTH, PATH_HEIGHT));

		if (wave_info.movment_path[i].first == wave_info.movment_path[i + 1].first &&
			wave_info.movment_path[i].second < wave_info.movment_path[i + 1].second)
			window->draw_img(DOWN_PATH, Rectangle((wave_info.movment_path[i].first * CUBE_SIZE) + PATH_X0,
			(wave_info.movment_path[i].second * CUBE_SIZE) + PATH_Y0, PATH_WIDTH, PATH_HEIGHT));

		if (wave_info.movment_path[i].first > wave_info.movment_path[i + 1].first &&
			wave_info.movment_path[i].second == wave_info.movment_path[i + 1].second)
			window->draw_img(LEFT_PATH, Rectangle((wave_info.movment_path[i].first * CUBE_SIZE) + PATH_X0,
			(wave_info.movment_path[i].second * CUBE_SIZE) + PATH_Y0, PATH_WIDTH, PATH_HEIGHT));

		if (wave_info.movment_path[i].first < wave_info.movment_path[i + 1].first &&
			wave_info.movment_path[i].second == wave_info.movment_path[i + 1].second)
			window->draw_img(RIGHT_PATH, Rectangle((wave_info.movment_path[i].first * CUBE_SIZE) + PATH_X0,
			(wave_info.movment_path[i].second * CUBE_SIZE) + PATH_Y0, PATH_HEIGHT, PATH_HEIGHT));
	}
}

void draw_background_details(Window* window, FieldRunners game, WaveInfo wave_info)
{
	window->draw_img(BACKGROUND_IMAGE_PATH, Rectangle(ORIGIN, ORIGIN, BACKGROUND_WIDTH, BACKGROUND_HEIGHT));
	window->show_text(MONEY_ + to_string(game.get_money()), Point(FONT2_X0, FONT2_Y0), WHITE, MY_FONT, FONT_SIZE);
	draw_path_guide(window, wave_info);
	string file_name = HEART_IMAGE;
	file_name += to_string(game.get_hearts());
	file_name += PNG;
	window->draw_img(file_name, Rectangle(HEART_IMAGE_X0, HEART_IMAGE_Y0, HEART_IMAGE_WIDTH, HEART_IMAGE_HEIGHT));
	window->show_text(to_string(game.get_hearts()),Point(FONT1_X0, FONT1_Y0) ,WHITE, MY_FONT, FONT_SIZE);
}

void draw(Window* window, FieldRunners game, WaveInfo wave_info)
{
	window->clear();
	draw_background_details(window, game, wave_info);
	game.draw_towers(window);
	game.draw_enemies(window, wave_info);
	game.draw_bullets(window);
	window->update_screen();
}