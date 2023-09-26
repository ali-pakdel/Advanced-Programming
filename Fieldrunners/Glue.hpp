#ifndef GLUE_HPP
#define GLUE_HPP

#include "Tower.hpp"

class Glue : public Tower
{
public:
	Glue(float _damage, int _upgrade_cost, int _level, int _attack_speed, int _tower_type)
		: Tower(_damage, _upgrade_cost, _level, _attack_speed, _tower_type) {};
	void draw(Window* window);
	void decrease_enemy_health(enemies enemies_info, Enemy* enemy);
	void decrease_enemy_speed(enemies enemies_info, Enemy* enemy);
	void set_glue_duration(int _glue_duration) { glue_duration = _glue_duration; }
	void increase_glue_duration();
	void upgrade();
private:
	int glue_duration;
};
#endif // !GLUE_HPP
