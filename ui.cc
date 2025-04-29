#include "utils.hh"
#include "ui.hh"
#include "sprites.hh"
#include "window.hh"

void paint_num_of_coffee (pro2::Window& window, int counter, pro2::Pt cam) {
    int x = cam.x + window.width() / 2.5 + 20, y = cam.y - window.height() / 2.5 - 10;
    for (int i = 0; i < 3; i++) {
        char sprite_id = '0' + counter % 10;
        counter /= 10;
        pro2::Pt top_left = {x - i * 10, y};
        paint_sprite(window, top_left, Sprites::diccionari.at(sprite_id), false);
    }
    paint_sprite(window, {x - 40, y - 5}, Sprites::coffe_sprites.at(0), false);
}

void paint_pause_screen (pro2::Window& window, pro2::Pt cam) {
    int x = cam.x, y = cam.y;
    int width = window.width() / 2, height = window.height() / 2;
    pro2::Rect rect = {x - width, y - height, x + width, y + height};
    paint_rect(window, rect, 0x9389fa - 0x202020);
    std::string s = "JOC PAUSAT";
    int x_offset = (s.size() * 7) / 2;
    for (int i = 0; i < s.size(); i++)
    {
        paint_sprite(window, {(x - x_offset) + i * 8, y - 3}, Sprites::diccionari.at(s[i]), false);       
    }
    restart_info(window, cam, "PITJA 'P' PER REPRENDRE EL JOC");
}

void paint_win_screen (pro2::Window& window, pro2::Pt cam) {
    int x = cam.x, y = cam.y;
    int width = window.width() / 2, height = window.height() / 2;
    pro2::Rect rect = {x - width, y - height, x + width, y + height};
    paint_rect(window, rect, 0);
    std::string s = "HAS GUANYAT!";
    int x_offset = (s.size() * 7) / 2;
    for (int i = 0; i < s.size(); i++)
    {
        paint_sprite(window, {(x - x_offset) + i * 8, y - 3}, Sprites::diccionari.at(s[i]), false);       
    }
}

void paint_game_over_screen (pro2::Window& window, pro2::Pt cam) {
    int x = cam.x, y = cam.y;
    int width = window.width() / 2, height = window.height() / 2;
    pro2::Rect rect = {x - width, y - height, x + width, y + height};
    paint_rect(window, rect, 0x8f2131);
    std::string s = "HAS PERDUT";
    int x_offset = (s.size() * 7) / 2;
    for (int i = 0; i < s.size(); i++)
    {
        paint_sprite(window, {(x - x_offset) + i * 8, y - 3}, Sprites::diccionari.at(s[i]), false);       
    }    
    restart_info(window, cam, "PITJA 'R' PER REINICIAR");
}

void restart_info (pro2::Window& window, pro2::Pt cam, std::string s) {
    int x = cam.x, y = cam.y;
    int frame = window.frame_count();
    if (frame % 40 > 15){
        int x_offset = (s.size() * 7) / 2;
        bool open_single_quote = true;
        for (int i = 0; i < s.size(); i++) {
            bool mirror = false;
            if (s[i] == 39) {
                mirror = open_single_quote;
            } 
            paint_sprite(window, {(x - x_offset) + i * 8, y + window.height() / 3 + 25}, Sprites::diccionari.at(s[i]), mirror);       
            if (s[i] == 39) {
                open_single_quote = !open_single_quote;
            }
        }
    }
}
