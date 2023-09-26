#include "Tesla.hpp"

using namespace std;

#define DEFAULT_TESLA_ "Pics/T"
#define UPGRADE_DAMAGE 1000

#define ONE__ 1
#define TWO__ 2

void Tesla::draw(Window* window)
{
	string file_name = DEFAULT_TESLA_;
	if (level == ONE__)
		file_name += ONE_;
	else if (level == TWO__)
		file_name += TWO_;
	else 
		file_name += THREE_;
	file_name += PNG_;

	window->draw_img(file_name, Rectangle((position.first * CUBE_SIZE__) + TOWER_X0_,
		(position.second * CUBE_SIZE__) + TOWER_Y0_, CUBE_SIZE__, CUBE_SIZE__)); 
}

void Tesla::upgrade()
{
	damage += UPGRADE_DAMAGE;
	level++;
}

void Tesla::decrease_enemy_health(enemies enemies_info, Enemy* enemy)
{
		enemy->decrease_health(damage);
}