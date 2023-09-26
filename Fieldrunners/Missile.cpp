#include "Missile.hpp"
 
using namespace std;
#define DEFAULT_MISSILE_PATH "Pics/M"
#define UPGRADE_DAMGAE 75
#define RANGE_ 50

void Missile::draw(Window* window)
{
	string file_name = DEFAULT_MISSILE_PATH;
	file_name += make_file_name();

	window->draw_img(file_name, Rectangle((position.first * CUBE_SIZE__) + TOWER_X0_,
				(position.second * CUBE_SIZE__) + TOWER_Y0_, CUBE_SIZE__, CUBE_SIZE__));
}

void Missile::upgrade()
{
	damage += UPGRADE_DAMGAE;
	level++;
}

void Missile::decrease_enemy_health(enemies enemies_info, Enemy* enemy)
{
	for (int i = 0; i < enemies_info.size(); i++)
		if (sqrt(pow(enemies_info[i]->get_current_xy().first - enemy->get_current_xy().first, 2) +
			pow(enemies_info[i]->get_current_xy().second - enemy->get_current_xy().second, 2)) < RANGE_)
			enemies_info[i]->decrease_health(damage);
}