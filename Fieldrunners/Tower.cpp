#include <vector>
#include <cmath>

#include "rsdl.hpp"
#include "Tower.hpp"
#include "Enemy.hpp"

using namespace std;

#define TOWER_CENTER_ 20
#define BULLET_POSITION -1000
#define CUBE_SIZE 60
#define ENEMY_X0 120
#define ENEMY_Y0 175

#define RIGHT_DOWN 2
#define RIGHT_UP 1
#define LEFT_DOWN 4
#define LEFT_UP 3
#define RANGE 150

#define POWER 2

Tower::Tower(float _damage, int _upgrade_cost, int _level, int _attack_speed, int _tower_type)
{
	damage = _damage;
	upgrade_cost = _upgrade_cost;
	attack_speed = _attack_speed;
	level = _level;
	attack_time = _attack_speed;
	tower_type = _tower_type;
}
void Tower::choose_nearest_enemy(enemies enemies_info)
{
	pair<float, Enemy*> enemy_distance(150, NULL);
	for (int i = 0; i < enemies_info.size(); i++)
		if (enemy_distance.first >= calculate_distance(enemies_info[i]))
		{
			enemy_distance.first = calculate_distance(enemies_info[i]);
			enemy_distance.second = enemies_info[i];
		}
	nearest_enemy = enemy_distance.second;
	if (enemy_distance.first > RANGE)
		nearest_enemy == NULL;
}
float Tower::calculate_distance(Enemy* enemy)
{
	int x = (position.first * CUBE_SIZE) + ENEMY_X0;
	int y = (position.second * CUBE_SIZE) + ENEMY_Y0;
	return sqrt(pow(enemy->get_current_xy().first - x, POWER) + pow(enemy->get_current_xy().second - y, POWER));
}
bool Tower::is_in_range(Enemy* enemy)
{
	if (calculate_distance(enemy) < RANGE)
		return true;
	else
		return false;
}
void Tower::fire(Window* window, enemies enemies_info)
{
	if (nearest_enemy == NULL)
	{
		choose_nearest_enemy(enemies_info);
		return;
	}
	if (is_in_range(nearest_enemy) && (attack_time == attack_speed))
	{
		Bullet* bullet = new Bullet(nearest_enemy, tower_type);
		bullet->set_position(position);
		attack_time = 1;
		which_direction();
		bullets_info.push_back(bullet);
	}
	if (!(is_in_range(nearest_enemy)))
		nearest_enemy = NULL;
	attack_time++;
}

bool Tower::is_bullet_reached(Bullet* bullet)
{
	if ((bullet->get_position().first == bullet->get_enemy()->get_current_xy().first + TOWER_CENTER_)
		&& (bullet->get_position().second == bullet->get_enemy()->get_current_xy().second + TOWER_CENTER_))
		return true;
	else
		return false;
}
void Tower::delete_reached_bullets(enemies enemies_info)
{
	for (int i = 0; i < bullets_info.size(); i++)
		if (is_bullet_reached(bullets_info[i]))	
		{
			decrease_enemy_health(enemies_info, bullets_info[i]->get_enemy());
			pair<float, float> pos(BULLET_POSITION, BULLET_POSITION);
			bullets_info[i]->set_position(pos);
		}
}

void Tower::which_direction()
{
	if (nearest_enemy == NULL)
		return;
	if (nearest_enemy->get_current_xy().first > (position.first * CUBE_SIZE) + ENEMY_X0 &&
				nearest_enemy->get_current_xy().second > (position.second * CUBE_SIZE) + ENEMY_Y0)
		direction = RIGHT_DOWN;

	if (nearest_enemy->get_current_xy().first > (position.first * CUBE_SIZE) + ENEMY_X0 &&
				nearest_enemy->get_current_xy().second < (position.second * CUBE_SIZE) + ENEMY_Y0)
		direction = RIGHT_UP;

	if (nearest_enemy->get_current_xy().first < (position.first * CUBE_SIZE) + ENEMY_X0 &&
				nearest_enemy->get_current_xy().second > position.second)
		direction = LEFT_DOWN;
	if (nearest_enemy->get_current_xy().first < (position.first * CUBE_SIZE) + ENEMY_X0 &&
				nearest_enemy->get_current_xy().second < (position.second * CUBE_SIZE) + ENEMY_Y0)
		direction = LEFT_UP;
}

string Tower::make_file_name()
{
	string file_name = "";
	if (level == LEVEL_ONE_)
		file_name += ONE_;
	else if (level == LEVEL_TWO_)
		file_name += TWO_;
	else
		file_name += THREE_;

	if (direction == RIGHT_UP_)
		file_name += RIGHT_UP__;
	if (direction == RIGHT_DOWN_)
		file_name += RIGHT_DOWN__;
	if (direction == LEFT_UP_)
		file_name += LEFT_UP__;
	if (direction == LEFT_DOWN_)
		file_name += LEFT_DOWN__;

	file_name += PNG_;
	return file_name;
}