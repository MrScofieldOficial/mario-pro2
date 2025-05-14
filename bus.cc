#include "bus.hh"
#include "sprites.hh"
#include "utils.hh"
#include "ui.hh"

void Bus::paint(pro2::Window& window) const {
    paint_sprite(window, pos_, Sprites::bus.at("parada"), false);
    paint_sprite(window, {pos_.x + 3*k_, pos_.y}, Sprites::bus.at("senyal"), false);
    paint_centered_text(window, {pos_.x + 3*k_ + 7, pos_.y + 3}, stop_num_);
}

int Bus::update(const pro2::Rect& mario_hit_box) {
    if (rects_overlap(mario_hit_box, hit_box_)) {
        return stoi(stop_num_ + stop_id_);
    }
    return 0;
}
