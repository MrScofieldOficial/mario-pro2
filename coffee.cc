#include "coffee.hh"
#include <cmath>
#include "sprites.hh"
#include "utils.hh"

void Coffee::paint(pro2::Window& window) const {
    int frame = window.frame_count();
    int            offset = std::sin(frame* 0.1) * 2 ;
    const pro2::Pt top_left = {pos_.x + 2, pos_.y - offset};
    int sprite_id = (frame % (22 * 3)) / 3;
    paint_sprite(window, top_left, Sprites::coffe_sprites.at(sprite_id), false);
}

void Coffee::is_in(pro2::Rect mario_hit_box, pro2::Rect coffee_hit_box) {

}
