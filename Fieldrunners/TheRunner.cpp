#include "TheRunner.hpp"

#define THE_RUNNER_PATH "runner.png"
#define RUNNER_Y0 5
#define RUNNER_SIZE 40

using namespace std;


void TheRunner::draw(Window* window)
{
	window->draw_img(THE_RUNNER_PATH, Rectangle(Point(current_xy.first, current_xy.second + RUNNER_Y0), 
				RUNNER_SIZE, RUNNER_SIZE)); 
}