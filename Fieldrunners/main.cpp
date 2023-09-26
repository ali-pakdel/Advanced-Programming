#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <random>

#include "rsdl.hpp"
#include "Fieldrunners.hpp"
#include "Functions.hpp"

#define FIELD_RUNNERS "Field Runners"
#define BACKGROUND_HEIGHT 1024
#define BACKGROUND_WIDTH 1365
#define ORIGIN 0

#define PLAYER_MONEY 200
#define HEATRS 20
#define ZERO_ 0
#define DELAY_TIME 50

using namespace std;

int main(int argc, char* argv[])
{
	FieldRunners game(PLAYER_MONEY, HEATRS);
	WaveInfo wave_info = get_input();
	Window *window = new Window(BACKGROUND_WIDTH, BACKGROUND_HEIGHT, FIELD_RUNNERS);
	pair<float, float> mouse_position(ZERO_, ZERO_);
	for (int delay_counter = 0; ; delay_counter++)
	{ 
		mouse_position = update(window, game, mouse_position);
		draw(window, game, wave_info);
		game.play(window, wave_info, delay_counter);
		game.check_end_of_round(wave_info, window);
		delay(DELAY_TIME);
	}
}

