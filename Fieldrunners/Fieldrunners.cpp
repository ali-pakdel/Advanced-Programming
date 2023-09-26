#include <cstdlib>
#include <time.h>
#include <random>
#include <algorithm>

#include "Fieldrunners.hpp"
#include "TheRunner.hpp"
#include "StubbornRunner.hpp"
#include "SuperTrooper.hpp"
#include "Scrambler.hpp"
#include "Gatling.hpp"
#include "Missile.hpp"
#include "Tesla.hpp"
#include "Glue.hpp"

#define THE_RUNNER_ 0
#define STUBBORN_RUNNER_ 1
#define SUPER_TROOPER_ 2
#define SCRAMBLER_ 3
#define EMPTY 0

#define THE_RUNNER_HEALTH 250
#define THE_RUNNER_speed 2.5
#define THE_RUNNER_KILLING_REWARD 6
#define THE_RUNNER_DAMAGE 1
#define THE_RUNNER 1

#define STUBBORN_HEALTH 400
#define STUBBORN_speed 1.5
#define STUBBORN_KILLING_REWARD 10
#define STUBBORN_DAMAGE 4
#define STUBBORN 2

#define SUPER_TROOPER_HEALTH 500
#define SUPER_TROOPER_speed 1.25
#define SUPER_TROOPER_KILLING_REWARD 8
#define SUPER_TROOPER_DAMAGE 4
#define SUPER_TROOPER 3

#define SCRAMBLER_HEALTH 100
#define SCRAMBLER_speed 4.5
#define SCRAMBLER_KILLING_REWARD 4
#define SCRAMBLER_DAMAGE 2
#define SCRAMBLER 4

#define THE_ENEMY_X0 -300
#define THE_ENEMY_Y0 -300

#define REST_TIME 60
#define ZERO_NINE 0.9
#define ZERO_ONE 0.1
#define ZERO 0
#define SHOW_ENEMY_DELAY 10

#define CUBE_SIZE 60
#define ENEMY_X0_ 120
#define ENEMY_Y0_ 175
#define FIRST_CELL 0

#define GATLING_KEY 'g'
#define GATLING_COST 55
#define GATLING_DAMGAE 35
#define GATLING_UPGRADE_COST 40
#define LEVEL_ONE 1
#define GATLING_SPEED 20
#define GATLING_TYPE 1
#define MISSILE_KEY 'm'
#define MISSILE_COST 55
#define MISSILE_DAMGAE 35
#define MISSILE_UPGRADE_COST 40
#define MISSILE_SPEED 20
#define MISSILE_TYPE 2
#define MISSILE_KEY 'm'
#define MISSILE_COST 70
#define MISSILE_DAMGAE 75
#define MISSILE_UPGRADE_COST 60
#define MISSILE_SPEED 60
#define MISSILE_TYPE 2
#define TESLA_KEY 't'
#define TESLA_COST 120
#define TESLA_DAMGAE 700
#define TESLA_UPGRADE_COST 100
#define TESLA_SPEED 30
#define TESLA_TYPE 3
#define GLUE_KEY 'l'
#define GLUE_COST 60
#define GLUE_DAMGAE 0.6
#define GLUE_UPGRADE_COST 45
#define GLUE_SPEED 40
#define GLUE_TYPE 4
#define GLUE_DURATION 50
#define FIELD_WIDTH 19
#define FIELD_HEIGHT 11
#define YOU_WIN_PATH "you_win.png"
#define YOU_LOSE_PATH "you_lose.png"
#define YOU_WIN_WIDTH 1365
#define YOU_WIN_HEIGHT 1024

#define END_DELAY 2000

using namespace std;

void FieldRunners::set_enemies_info(WaveInfo wave_info)
{
	if (!(is_round_over() && rest_time == REST_TIME) && round != 0)
		return;
	set_the_runners(wave_info);
	set_stubborn_runners(wave_info);
	set_super_troopers(wave_info);
	set_scramblers(wave_info);
	randomize_enemies();
	round++;
	if (round > 0)
		increase_enemies_health();
	rest_time = ZERO;
}
void FieldRunners::set_the_runners(WaveInfo wave_info)
{
	for (int i = 0; i < wave_info.no_each_enemy[round][THE_RUNNER_]; i++)
	{
		TheRunner* the_runner = new TheRunner(THE_RUNNER_HEALTH, THE_RUNNER_speed,
			THE_RUNNER_KILLING_REWARD, THE_RUNNER_DAMAGE, THE_RUNNER);
		the_runner->set_current_xy(THE_ENEMY_X0, THE_ENEMY_Y0);
		the_runner->set_setted_or_not(0);
		enemies_info.push_back(the_runner);
	}
}
void FieldRunners::set_stubborn_runners(WaveInfo wave_info)
{
	for (int i = 0; i < wave_info.no_each_enemy[round][STUBBORN_RUNNER_]; i++)
	{
		StubbornRunner* stubborn_runner = new StubbornRunner(STUBBORN_HEALTH, STUBBORN_speed,
			STUBBORN_KILLING_REWARD, STUBBORN_DAMAGE, STUBBORN);
		stubborn_runner->set_current_xy(THE_ENEMY_X0, THE_ENEMY_Y0);
		stubborn_runner->set_setted_or_not(0);
		enemies_info.push_back(stubborn_runner);
	}
}
void FieldRunners::set_super_troopers(WaveInfo wave_info)
{
	for (int i = 0; i < wave_info.no_each_enemy[round][SUPER_TROOPER_]; i++)
	{
		SuperTrooper* super_trooper = new SuperTrooper(SUPER_TROOPER_HEALTH, SUPER_TROOPER_speed,
			SUPER_TROOPER_KILLING_REWARD, SUPER_TROOPER_DAMAGE, SUPER_TROOPER);
		super_trooper->set_current_xy(THE_ENEMY_X0, THE_ENEMY_Y0);
		super_trooper->set_setted_or_not(0);
		enemies_info.push_back(super_trooper);
	}
}
void FieldRunners::set_scramblers(WaveInfo wave_info)
{
	for (int i = 0; i < wave_info.no_each_enemy[round][SCRAMBLER_]; i++)
	{
		Scrambler* scrambler = new Scrambler(SCRAMBLER_HEALTH, SCRAMBLER_speed,
			SCRAMBLER_KILLING_REWARD, SCRAMBLER_DAMAGE, SCRAMBLER);
		scrambler->set_current_xy(THE_ENEMY_X0, THE_ENEMY_Y0);
		scrambler->set_setted_or_not(0);
		enemies_info.push_back(scrambler);
	}
}
void FieldRunners::increase_enemies_health()
{
	for (int i = 0; i < enemies_info.size(); i++)
		enemies_info[i]->increase_health((ZERO_NINE + (ZERO_ONE * round)) * enemies_info[i]->get_health());
}
void FieldRunners::randomize_enemies()
{
	auto rng = default_random_engine{};
	shuffle(begin(enemies_info), end(enemies_info), rng);
}

void FieldRunners::set_positions(WaveInfo wave_info, int delay_counter)
{
	for (int i = 0; i < enemies_info.size(); i++)
		if (enemies_info[i]->get_setted_or_not() == 0 && (delay_counter % SHOW_ENEMY_DELAY == 0))
		{
			enemies_info[i]->set_current_xy((wave_info.movment_path[FIRST_CELL].first * CUBE_SIZE) + ENEMY_X0_,
				(wave_info.movment_path[FIRST_CELL].second * CUBE_SIZE) + ENEMY_Y0_);
			enemies_info[i]->set_setted_or_not(1);
			break;
		}
}
void FieldRunners::draw_enemies(Window* window, WaveInfo wave_info)
{
	for (int i = 0; i < enemies_info.size(); i++)
		enemies_info[i]->draw(window);
	move_enemies(wave_info);
}
void FieldRunners::draw_towers(Window* window)
{
	for (int i = 0; i < towers_info.size(); i++)
		towers_info[i]->draw(window);
}
void FieldRunners::draw_bullets(Window* window)
{
	for (int i = 0; i < towers_info.size(); i++)
		for (int j = 0; j < towers_info[i]->get_bullets_info().size(); j++)
			towers_info[i]->get_bullets_info()[j]->draw(window);
}

void FieldRunners::set_gatling(pair<float, float> _position)
{
	money -= GATLING_COST;
	Gatling* gatling = new Gatling(GATLING_DAMGAE, GATLING_UPGRADE_COST,
		LEVEL_ONE, GATLING_SPEED, GATLING_TYPE);
	gatling->set_position(_position);
	towers_info.push_back(gatling);
}
void FieldRunners::set_missile(pair<float, float> _position)
{
	money -= MISSILE_COST;
	Missile* missile = new Missile(MISSILE_DAMGAE, MISSILE_UPGRADE_COST,
		LEVEL_ONE, MISSILE_SPEED, MISSILE_TYPE);
	missile->set_position(_position);
	towers_info.push_back(missile);
}
void FieldRunners::set_tesla(pair<float, float> _position)
{
	money -= TESLA_COST;
	Tesla* tesla = new Tesla(TESLA_DAMGAE, TESLA_UPGRADE_COST,
		LEVEL_ONE, TESLA_SPEED, TESLA_TYPE);
	tesla->set_position(_position);
	towers_info.push_back(tesla);
}
void FieldRunners::set_glue(pair<float, float> _position)
{
	money -= GLUE_COST;
	Glue* glue = new Glue(GLUE_DAMGAE, GLUE_UPGRADE_COST,
		LEVEL_ONE, GLUE_SPEED, GLUE_TYPE);
	glue->set_position(_position);
	glue->set_glue_duration(GLUE_DURATION);
	towers_info.push_back(glue);
}
void FieldRunners::set_towers(char pressed_key, pair<float, float> pixel_position)
{
	pair<float, float> _position = calculate_pos(pixel_position);
	if (pressed_key == GATLING_KEY && money >= GATLING_COST)
		set_gatling(_position);
	if (pressed_key == MISSILE_KEY && money >= MISSILE_COST)
		set_missile(_position);
	if (pressed_key == TESLA_KEY && money >= TESLA_COST)
		set_tesla(_position);
	if (pressed_key == GLUE_KEY && money >= GLUE_COST)
		set_glue(_position);
}
void FieldRunners::upgrade_tower(Window* window, pair<float, float> pixel_position)
{
	pair<float, float> _position = calculate_pos(pixel_position);
	for (int i = 0; i < towers_info.size(); i++)
		if (towers_info[i]->get_position().first == _position.first &&
			towers_info[i]->get_position().second == _position.second)

			if (money >= towers_info[i]->get_upgrade_cost())
				towers_info[i]->upgrade();
}

void FieldRunners::play(Window* window, WaveInfo wave_info, int delay_counter)
{
	set_enemies_info(wave_info);
	set_positions(wave_info, delay_counter);
	find_reached_bullets();
	attack_enemies(window);
	delete_enemies();


}

void FieldRunners::move_enemies(WaveInfo wave_info)
{
	for (int i = 0; i < enemies_info.size(); i++)
		enemies_info[i]->move(wave_info);

}
void FieldRunners::attack_enemies(Window* window)
{
	for (int i = 0; i < towers_info.size(); i++)
		towers_info[i]->fire(window, enemies_info);
}
void FieldRunners::find_reached_bullets()
{
	for (int i = 0; i < towers_info.size(); i++)
		towers_info[i]->delete_reached_bullets(enemies_info);
}
void FieldRunners::delete_enemies()
{
	for (int i = 0; i < enemies_info.size(); i++)
	{
		if (enemies_info[i]->get_health() <= 0)
		{
			money += enemies_info[i]->get_killing_reward();
			delete enemies_info[i];
			enemies_info.erase(enemies_info.begin() + i);
		}
		else if (enemies_info[i]->get_current_xy().first == (FIELD_WIDTH * CUBE_SIZE) + ENEMY_X0_)
		{
			hearts -= enemies_info[i]->get_damage();
			delete enemies_info[i];
			enemies_info.erase(enemies_info.begin() + i);
		}
	}
}

bool FieldRunners::is_round_over()
{
	if (enemies_info.size() == EMPTY)
		return true;
	else 
		return false;
}
pair<float, float> FieldRunners::calculate_pos(pair<float, float> pixel_position)
{
	pair<float, float> _pos;
	for (int i = 0; i < FIELD_WIDTH; i++)
		for (int j = 0; j < FIELD_HEIGHT; j++)
			if ((pixel_position.first < (((i + 1) * CUBE_SIZE) + ENEMY_X0_)) && 
						(pixel_position.first >= ((i * CUBE_SIZE) + ENEMY_X0_))
				&& (pixel_position.second < (((j + 1) * CUBE_SIZE) + ENEMY_Y0_)) &&
						(pixel_position.second >= (j * CUBE_SIZE) + ENEMY_Y0_))
			{
				_pos.first = i;
				_pos.second = j;
				return _pos;
			}
}
void FieldRunners::check_end_of_round(WaveInfo wave_info, Window* window)
{
	if (is_round_over())
	{
		if (round + 1 > wave_info.no_each_enemy.size())
			end_game(window);
		else
			rest_time++;
	}

}
void FieldRunners::end_game(Window* window)
{
	if (hearts <= ZERO)
		window->draw_img(YOU_LOSE_PATH, Rectangle(ZERO, ZERO, YOU_WIN_WIDTH, YOU_WIN_HEIGHT));
	else
		window->draw_img(YOU_WIN_PATH, Rectangle(ZERO, ZERO, YOU_WIN_WIDTH, YOU_WIN_HEIGHT));
	window->update_screen();
	delay(END_DELAY);
	exit(0);
}

