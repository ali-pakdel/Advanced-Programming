#ifndef SUPER_TROOPER_HPP
#define SUPER_TROOPER_HPP

#include "Enemy.hpp"

class SuperTrooper : public Enemy
{
public:
	SuperTrooper(int _health, float _movment_speed, int _killing_reward, int _damage, int _enemy_type)
		: Enemy(_health, _movment_speed, _killing_reward, _damage, _enemy_type) {};
	void draw(Window* window);

};

#endif 