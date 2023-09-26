#include "Scrambler.hpp"

#define SCRAMBLER_FILE "scrambler.png"
#define SCRAMBLER__Y0 5
#define SCRAMBLER_SIZE 50

void Scrambler::draw(Window* window)
{
	window->draw_img(SCRAMBLER_FILE, Rectangle(current_xy.first, current_xy.second + SCRAMBLER__Y0,
				SCRAMBLER_SIZE, SCRAMBLER_SIZE));
}