#include <vector>

#include "Fieldrunners.hpp"
WaveInfo get_input();
std::vector<std::pair<int, int>> make_path(std::vector<std::pair<int, int>> path);
std::vector<std::pair<int, int>> get_movment_path();
std::vector<std::vector<int>> get_no_each_enemy();

std::pair<float, float> update(Window* window, FieldRunners& game, std::pair<float, float> mouse_position);
void draw_path_guide(Window* window, WaveInfo wave_info);
void draw_background_details(Window* window, FieldRunners game, WaveInfo wave_info);
void draw(Window* window, FieldRunners game, WaveInfo wave_info);