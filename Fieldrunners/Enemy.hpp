#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>

#include "rsdl.hpp"

struct WaveInfo
{
	std::vector<std::pair<int, int>> movment_path;
	std::vector<std::vector<int>> no_each_enemy;
};

class Enemy 
{
public:
	Enemy(int _health, float _movment_speed, int _killing_reward, int _damage, int _enemy_type);
	virtual void draw(Window* window) = 0;

	void start_glue_duration(float _glue_damage, int glue_duration);

	void move(WaveInfo wave_info);
	void decrease_health(float damage_taken) { health -= damage_taken; }
	void increase_health(float _increased_health) { health = _increased_health; }

	void set_current_xy(float _x, float _y) { current_xy.first = _x;	current_xy.second = _y; }
	void set_setted_or_not(int _i) { setted_or_not = _i; }

	std::pair<float, float> get_current_xy() { return current_xy; }
	int get_killing_reward() { return killing_reward; }
	int get_damage() { return damage; }
	int get_enemy_type() { return enemy_type; }
	int get_setted_or_not() { return setted_or_not; }
	float get_health() { return health; }

protected:
	float calculate_movment_speed(float _movment_speed);

	std::pair<float, float> current_xy;
	int setted_or_not;
	float health;
	float movment_speed;
	int killing_reward;
	int damage;	
	int cell_of_movment_path = 0;
	int enemy_type;
	int on_glue_time = 0;
	int glue_time = 0;
	float glue_damage;
};

typedef std::vector<Enemy*> enemies;

#endif
