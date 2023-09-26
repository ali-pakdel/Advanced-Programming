#include "Enemy.hpp"

#define START 1
#define STOP 0
#define CUBE_SIZE 60
#define ENEMY_X0 120
#define ENEMY_Y0 175

using namespace std;

Enemy::Enemy(int _health, float _movment_speed, int _killing_reward, int _damage, int _enemy_type)
{
	health = _health;
	movment_speed = _movment_speed;
	killing_reward = _killing_reward;
	damage = _damage;
	enemy_type = _enemy_type;
}
void Enemy::start_glue_duration(float _glue_damage, int glue_duration)
{
	on_glue_time = START;
	glue_time = glue_duration;
	glue_damage = _glue_damage;
}
float Enemy::calculate_movment_speed(float _movment_speed)
{
	if (on_glue_time > STOP && on_glue_time < glue_time)
	{
		_movment_speed *= glue_damage;
		on_glue_time++;
	}
	if (glue_time + START == on_glue_time)
		on_glue_time = STOP;
	return _movment_speed;
}
void Enemy::move(WaveInfo wave_info)
{
	float _movment_speed = movment_speed;
	_movment_speed = calculate_movment_speed(_movment_speed);

	if (abs(current_xy.first - ((wave_info.movment_path[cell_of_movment_path].first * CUBE_SIZE) + ENEMY_X0)) == CUBE_SIZE  ||
		abs(current_xy.second - ((wave_info.movment_path[cell_of_movment_path].second * CUBE_SIZE) + ENEMY_Y0)) == CUBE_SIZE )
		cell_of_movment_path++;

	if (current_xy.second < ((wave_info.movment_path[cell_of_movment_path + 1].second * CUBE_SIZE) + ENEMY_Y0))
	{
		current_xy.second += _movment_speed;
		if (current_xy.second > ((wave_info.movment_path[cell_of_movment_path + 1].second * CUBE_SIZE) + ENEMY_Y0))
			current_xy.second = (wave_info.movment_path[cell_of_movment_path + 1].second * CUBE_SIZE) + ENEMY_Y0;
	}
	if (current_xy.first < ((wave_info.movment_path[cell_of_movment_path + 1].first * CUBE_SIZE) + ENEMY_X0))
	{
		current_xy.first += _movment_speed;
		if (current_xy.first > ((wave_info.movment_path[cell_of_movment_path + 1].first * CUBE_SIZE) + ENEMY_X0))
			current_xy.first = (wave_info.movment_path[cell_of_movment_path + 1].first * CUBE_SIZE) + ENEMY_X0;
	}
	if (current_xy.second > ((wave_info.movment_path[cell_of_movment_path + 1].second * CUBE_SIZE) + ENEMY_Y0))
	{
		current_xy.second -= _movment_speed;
		if (current_xy.second <= ((wave_info.movment_path[cell_of_movment_path + 1].second * CUBE_SIZE) + ENEMY_Y0))
			current_xy.second = (wave_info.movment_path[cell_of_movment_path + 1].second * CUBE_SIZE) + ENEMY_Y0;
	}
	if (current_xy.first > ((wave_info.movment_path[cell_of_movment_path + 1].first * CUBE_SIZE) + ENEMY_X0))
	{
		current_xy.first -= _movment_speed;
		if (current_xy.first <= ((wave_info.movment_path[cell_of_movment_path + 1].first * CUBE_SIZE) + ENEMY_X0))
			current_xy.first = (wave_info.movment_path[cell_of_movment_path + 1].first * CUBE_SIZE) + ENEMY_X0;
	}
}