#include "Gatling.hpp"

using namespace std;

#define DEFAULT_GATLING_ "Pics/G"
#define UPGRADE_DAMAGE 35
#define STUBBORN_ENEMY 2

void Gatling::draw(Window* window)
{
	string file_name = DEFAULT_GATLING_;
	file_name += make_file_name();

	window->draw_img(file_name, Rectangle((position.first * CUBE_SIZE__) + TOWER_X0_,
				(position.second * CUBE_SIZE__) + TOWER_Y0_, CUBE_SIZE__, CUBE_SIZE__));
}

void Gatling::upgrade()
{
	damage += UPGRADE_DAMAGE;
	level++;
}

void Gatling::decrease_enemy_health(enemies enemies_info, Enemy* enemy)
{
	if (enemy->get_enemy_type() != STUBBORN_ENEMY)
		enemy->decrease_health(damage);
}