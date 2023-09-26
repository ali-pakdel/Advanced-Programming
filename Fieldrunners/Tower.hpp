#ifndef TOWER_HPP
#define TOWER_HPP

#include <vector>

#include "Bullet.hpp"

#define RIGHT_DOWN_ 2
#define RIGHT_DOWN__ "RD"
#define RIGHT_UP_ 1
#define RIGHT_UP__ "RU"
#define LEFT_DOWN_ 4
#define LEFT_DOWN__ "LD"
#define LEFT_UP_ 3
#define LEFT_UP__ "LU"
#define LEVEL_ONE_ 1
#define LEVEL_TWO_ 2
#define ONE_ "1"
#define TWO_ "2"
#define THREE_ "3"
#define PNG_ ".png"

#define CUBE_SIZE__ 60
#define TOWER_X0_ 120
#define TOWER_Y0_ 180

class Tower
{
public:
	Tower(float _damage, int _upgrade_cost, int _level, int _attack_speed, int _tower_type);

	virtual void draw(Window* window) = 0;
	virtual void upgrade() = 0;
	virtual void decrease_enemy_health(enemies enemies_info, Enemy* enemy) = 0;

	void fire(Window* window, enemies enemies_info);
	void delete_reached_bullets(enemies enemies_info);
	void which_direction();
	void set_level(int _level) { level = _level; }
	void set_position(std::pair<float, float> _position) { position = _position; }

	int get_damage() { return damage; }
	int get_level() { return level; }
	std::pair<float, float> get_position() { return position; }
	int get_upgrade_cost() { return upgrade_cost; }
	std::vector<Bullet*> get_bullets_info() { return bullets_info; }

protected:
	void choose_nearest_enemy(enemies enemies_info);
	float calculate_distance(Enemy* enemy);
	bool is_in_range(Enemy* enemy);

	bool is_bullet_reached(Bullet* bullet);

	std::string make_file_name();

	std::vector<Bullet*> bullets_info;
	int tower_type;
	std::pair<float, float> position;
	int level;
	int upgrade_cost;
	float damage;
	int attack_speed;
	Enemy* nearest_enemy = NULL;
	int attack_time;
	int direction = 1;
};

typedef std::vector<Tower*> towers;

#endif 