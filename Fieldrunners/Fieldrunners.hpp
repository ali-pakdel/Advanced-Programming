#ifndef FIELDRUNNERS_HPP
#define FIELDRUNNERS_HPP

#include "Tower.hpp"
#include "Enemy.hpp"

using namespace std;


class FieldRunners
{
public:
	FieldRunners(int _money, int _hearts) { money = _money; hearts = _hearts;}
	void play(Window* window, WaveInfo wave_info, int delay_counter);

	void set_towers(char pressed_key, std::pair<float, float> position);
	void upgrade_tower(Window* window, std::pair<float, float> pixel_position);

	void draw_enemies(Window* window, WaveInfo wave_info);
	void draw_towers(Window* window);
	void draw_bullets(Window* window);

	void check_end_of_round(WaveInfo wave_info, Window* window);

	void set_money(int _money) { money = _money; }
	void set_hearts(int _hearts) { hearts = _hearts; }

	int get_money() { return money; }
	int get_hearts() { return hearts; }
	enemies get_enemies_info() { return enemies_info; }
	towers get_towers_info() { return towers_info; }


private:
	void set_enemies_info(WaveInfo wave_info);
	void set_the_runners(WaveInfo wave_info);
	void set_stubborn_runners(WaveInfo wave_info);
	void set_super_troopers(WaveInfo wave_info);
	void set_scramblers(WaveInfo wave_info);

	void set_gatling(std::pair<float, float> pixel_position);
	void set_missile(std::pair<float, float> pixel_position);
	void set_tesla(std::pair<float, float> pixel_position);
	void set_glue(std::pair<float, float> pixel_position);

	void randomize_enemies();
	void increase_enemies_health();
	void set_positions(WaveInfo wave_info, int _delay);

	void move_enemies(WaveInfo wave_info);
	void attack_enemies(Window* window);
	void find_reached_bullets();
	void delete_enemies();

	std::pair<float, float> calculate_pos(std::pair<float, float> pixel_position);
	bool is_round_over();
	void end_game(Window* window);

	int hearts;
	int money;
	int round = 0;
	int rest_time = 60;
	enemies enemies_info;
	towers towers_info;
	
};

#endif
