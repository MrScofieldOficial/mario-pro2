#include "utils.hh"
#include "ui.hh"
#include "sprites.hh"
#include "window.hh"

void paint_num_of_coffee (pro2::Window& window, int counter, pro2::Pt cam) {
    int x = cam.x + window.width() / 2.5, y = cam.y - window.height() / 2.5;
    for (int i = 0; i < 3; i++) {
        char sprite_id = '0' + counter % 10;
        counter /= 10;
        pro2::Pt top_left = {x - i * 10, y};
        paint_sprite(window, top_left, Sprites::diccionari.at(sprite_id), false);
    }
}

