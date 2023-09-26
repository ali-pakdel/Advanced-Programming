#include "Glue.hpp"

using namespace std;

#define DEFAULT_GLUE_ "Pics/L"
#define UPGRADE_DAMAGE 0.1
#define UPGRADE_DURATION 10
#define STUBBORN__ 2
#define RANGE__ 30
void Glue::draw(Window* window)
{
	string file_name = DEFAULT_GLUE_;
	file_name += make_file_name();

	window->draw_img(file_name, Rectangle((position.first * CUBE_SIZE__) + TOWER_X0_,
		(position.second * CUBE_SIZE__) + TOWER_Y0_, CUBE_SIZE__, CUBE_SIZE__));
}
void Glue::upgrade()
{
	damage -= UPGRADE_DAMAGE;
	glue_duration += UPGRADE_DURATION;
	level++;
}
void Glue::decrease_enemy_health(enemies enemies_info, Enemy* enemy)
{
	if (enemy->get_enemy_type() != STUBBORN__)
		decrease_enemy_speed(enemies_info, enemy);
}

void Glue::decrease_enemy_speed(enemies enemies_info, Enemy* enemy)
{
	for (int i = 0; i < enemies_info.size(); i++)
		if (sqrt(pow(enemies_info[i]->get_current_xy().first - enemy->get_current_xy().first, 2) +
			pow(enemies_info[i]->get_current_xy().second - enemy->get_current_xy().second, 2)) < RANGE__)
			enemies_info[i]->start_glue_duration(damage, glue_duration);
}