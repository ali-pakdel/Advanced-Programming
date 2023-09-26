#ifndef BULLET_HPP
#define BULLET_HPP

#include "Enemy.hpp"

class Bullet 
{
public:
	Bullet(Enemy* _enemy, int _bullet_type);
	void set_position(std::pair<float, float> _position);
	void draw(Window* window);
	
	std::pair<float, float> get_position() { return bullet_position; }
	Enemy* get_enemy() { return enemy; }
	int get_bullet_type() { return bullet_type; }

private:
	void move();

	std::pair<float, float> bullet_position;
	Enemy* enemy;
	int bullet_type;
};

#endif
