#include "StubbornRunner.hpp"
#include "rsdl.hpp"

#define STUBBORN_RUNNER_PATH "stubborn-runner.png"
#define STUBBORN__Y0 5
#define STUBBORN_SIZE 40

using namespace std;

void StubbornRunner::draw(Window* window)
{
	window->draw_img(STUBBORN_RUNNER_PATH, Rectangle(Point(current_xy.first, current_xy.second + STUBBORN__Y0),
				STUBBORN_SIZE, STUBBORN_SIZE));
}