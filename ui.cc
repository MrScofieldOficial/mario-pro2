#include "utils.hh"
#include "ui.hh"
#include "sprites.hh"
#include "window.hh"

const int digit_width = 8;
const int char_width = 8;
const int sprite_height_offset = -3;
const int coffee_icon_offset = 5;
const int blink_frame_period = 50;
const int blink_on_time = 20;
const pro2::Color sky_color = 0x9389fa;
const pro2::Color game_over_color = 0x8f2131;
const pro2::Color pause_color = sky_color - 0x202020;

void paint_centered_text(pro2::Window& window, pro2::Pt center, const std::string& text, int y_offset = 0) {
    int x_offset = (text.size() * char_width) / 2;
    for (int i = 0; i < text.size(); ++i) {
        paint_sprite(window, {center.x - x_offset + i * digit_width, center.y + y_offset}, Sprites::diccionari.at(text[i]), false);
    }
}

void paint_num_of_coffee(pro2::Window& window, int counter, pro2::Pt cam) {
    int x = cam.x + window.width() / 2.5 + 20;
    int y = cam.y - window.height() / 2.5 - 10;

    for (int i = 0; i < 3; ++i) {
        char sprite_id = '0' + counter % 10;
        counter /= 10;
        pro2::Pt top_left = {x - i * 10, y};
        paint_sprite(window, top_left, Sprites::diccionari.at(sprite_id), false);
    }

    paint_sprite(window, {x - 40, y - coffee_icon_offset}, Sprites::coffe_sprites.at(0), false);
}

void paint_pause_screen(pro2::Window& window, pro2::Pt cam) {
    int width = window.width() / 2;
    int height = window.height() / 2;
    pro2::Rect rect = {cam.x - width, cam.y - height, cam.x + width, cam.y + height};
    paint_rect(window, rect, pause_color);
    paint_centered_text(window, cam, "JOC PAUSAT", sprite_height_offset);
    restart_info(window, cam, "PITJA 'P' PER REPRENDRE EL JOC");
}

void paint_win_screen(pro2::Window& window, pro2::Pt cam) {
    int width = window.width() / 2;
    int height = window.height() / 2;
    pro2::Rect rect = {cam.x - width, cam.y - height, cam.x + width, cam.y + height};
    paint_rect(window, rect, 0);
    paint_centered_text(window, cam, "HAS GUANYAT!", sprite_height_offset);
}

void paint_game_over_screen(pro2::Window& window, pro2::Pt cam) {
    int width = window.width() / 2;
    int height = window.height() / 2;
    pro2::Rect rect = {cam.x - width, cam.y - height, cam.x + width, cam.y + height};
    paint_rect(window, rect, game_over_color);
    paint_centered_text(window, cam, "HAS PERDUT", sprite_height_offset);
    restart_info(window, cam, "PITJA 'R' PER REINICIAR");
}

void restart_info(pro2::Window& window, pro2::Pt cam, std::string s) {
    int frame = window.frame_count();
    if (frame % blink_frame_period > blink_on_time) {
        int x_offset = (s.size() * char_width) / 2;
        bool open_single_quote = true;
        for (int i = 0; i < s.size(); ++i) {
            bool mirror = false;
            if (s[i] == '\'') {
                mirror = open_single_quote;
                open_single_quote = !open_single_quote;
            }
            paint_sprite(window, {cam.x - x_offset + i * digit_width, cam.y + window.height() / 3 + 25},
                         Sprites::diccionari.at(s[i]), mirror);
        }
    }
}
