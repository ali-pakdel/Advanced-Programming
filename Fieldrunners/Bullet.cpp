#include "Bullet.hpp"

#define CUBE_SIZE 60
#define BULLET_X0 150
#define BULLET_Y0 205
#define GATLING 1
#define MISSILE 2
#define TESLA 3
#define GLUE 4
#define GATLING_BULLET_PATH "B1.png"
#define GATLING_BULLET_WIDTH 5
#define GATLING_BULLET_HEIGHT 5

#define MISSILE_BULLET_PATH "B2.png"
#define MISSILE_BULLET_WIDTH 20 
#define MISSILE_BULLET_HEIGHT 20 

#define TESLA_BULLET_PATH "B3.png"
#define TESLA_BULLET_WIDTH 30
#define TESLA_BULLET_HEIGHT 30

#define GLUE_BULLET_PATH "B4.png"
#define GLUE_BULLET_WIDTH 10
#define GLUE_BULLET_HEIGHT 10

#define ENEMY_CENTER 20
#define BULLET_SPEED 20

using namespace std;

Bullet::Bullet(Enemy* _enemy, int _bullet_type)
{
	enemy = _enemy;
	bullet_type = _bullet_type;
}

void Bullet::set_position(pair<float, float> _position)
{
	bullet_position.first = (_position.first * CUBE_SIZE) + BULLET_X0;
	bullet_position.second = (_position.second * CUBE_SIZE) + BULLET_Y0;
}

void Bullet::draw(Window* window)
{
	move();
	if (bullet_type == GATLING)
		window->draw_img(GATLING_BULLET_PATH, Rectangle(bullet_position.first,
					bullet_position.second, GATLING_BULLET_WIDTH, GATLING_BULLET_HEIGHT));

	if (bullet_type == MISSILE)
		window->draw_img(MISSILE_BULLET_PATH, Rectangle(bullet_position.first,
					bullet_position.second, MISSILE_BULLET_WIDTH, MISSILE_BULLET_HEIGHT));

	if (bullet_type == TESLA)
		window->draw_img(TESLA_BULLET_PATH, Rectangle(bullet_position.first,
					bullet_position.second, TESLA_BULLET_WIDTH, TESLA_BULLET_HEIGHT));

	if (bullet_type == GLUE)
		window->draw_img(GLUE_BULLET_PATH, Rectangle(bullet_position.first,
					bullet_position.second, GLUE_BULLET_WIDTH, GLUE_BULLET_HEIGHT));
}

void Bullet::move()
{
	if (bullet_position.first < enemy->get_current_xy().first + ENEMY_CENTER)
	{
		bullet_position.first += BULLET_SPEED;
		if (bullet_position.first > enemy->get_current_xy().first + ENEMY_CENTER)
			bullet_position.first = enemy->get_current_xy().first + ENEMY_CENTER;
	}
	if (bullet_position.second < enemy->get_current_xy().second + ENEMY_CENTER)
	{
		bullet_position.second += BULLET_SPEED;
		if (bullet_position.second > enemy->get_current_xy().second + ENEMY_CENTER)
			bullet_position.second = enemy->get_current_xy().second + ENEMY_CENTER;
	}
	if (bullet_position.first > enemy->get_current_xy().first + ENEMY_CENTER)
	{
		bullet_position.first -= BULLET_SPEED;
		if (bullet_position.first < enemy->get_current_xy().first + ENEMY_CENTER)
			bullet_position.first = enemy->get_current_xy().first + ENEMY_CENTER;
	}
	if (bullet_position.second > enemy->get_current_xy().second + ENEMY_CENTER)
	{
		bullet_position.second -= BULLET_SPEED;
		if (bullet_position.second < enemy->get_current_xy().second + ENEMY_CENTER)
			bullet_position.second = enemy->get_current_xy().second + ENEMY_CENTER;
	}
}