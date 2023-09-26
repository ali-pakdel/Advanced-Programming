#ifndef TESLA_HPP
#define TESLA_HPP

#include "Tower.hpp"

class Tesla : public Tower
{
public:
	Tesla(float _damage, int _upgrade_cost, int _level, int _attack_speed, int _tower_type)
		: Tower(_damage, _upgrade_cost, _level, _attack_speed, _tower_type) {};
	void draw(Window* window);
	void decrease_enemy_health(enemies enemies_info, Enemy* enemy);
	void upgrade();
private:
};

#endif
