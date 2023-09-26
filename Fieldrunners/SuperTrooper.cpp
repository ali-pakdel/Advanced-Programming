#include "SuperTrooper.hpp"

#define SUPER_TROOPER_FILE "supertrooper.png"
#define SUPER__TROOPER_Y0 5
#define SUPER_TROOPER_SIZE 50

void SuperTrooper::draw(Window* window)
{
	window->draw_img(SUPER_TROOPER_FILE, Rectangle(current_xy.first, current_xy.second + SUPER__TROOPER_Y0,
				SUPER_TROOPER_SIZE, SUPER_TROOPER_SIZE));
}