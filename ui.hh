#ifndef UI_HH
#define UI_HH

#include "window.hh"

// class HUD {

// public: 
// };
void paint_num_of_coffee (pro2::Window& window, int counter, pro2::Pt cam);

void paint_pause_screen (pro2::Window& window, pro2::Pt cam);

void paint_win_screen (pro2::Window& window, pro2::Pt cam);

void paint_game_over_screen (pro2::Window& window, pro2::Pt cam);

void restart_info(pro2::Window& window, pro2::Pt cam, std::string s);

#endif