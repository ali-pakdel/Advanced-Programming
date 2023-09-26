#ifndef THE_RUNNER_HPP
#define THE_RUNNER_HPP

#include "Enemy.hpp"

class TheRunner : public Enemy
{
public:
	TheRunner(int _health, float _movment_speed, int _killing_reward, int _damage, int _enemy_type)
			: Enemy(_health, _movment_speed, _killing_reward, _damage, _enemy_type) {};
	void draw(Window* window);

};

#endif 
