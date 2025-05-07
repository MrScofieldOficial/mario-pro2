#include <cmath>
#include "coffee.hh"
#include "sprites.hh"
#include "utils.hh"


void Coffee::paint(pro2::Window& window) const {
    if (colected_) return;
    
    const int num_sprites = Sprites::coffe_sprites.size();
    int frame = window.frame_count();
    const int slowdown_factor = 3;

    int adjusted_frame = frame + num_sprites * id_;
    int sprite_id = (adjusted_frame % (num_sprites * slowdown_factor)) / slowdown_factor;
    
    int offset = std::sin(frame * 0.1 - id_ * 2) * 3.5;
    const pro2::Pt top_left = {pos_.x + 2, pos_.y - offset - 3};
    paint_sprite(window, top_left, Sprites::coffe_sprites.at(sprite_id), false);
}

bool Coffee::can_collect_coffee(const pro2::Rect& mario_hit_box, const pro2::Rect& luigi_hit_box) {
    return rects_overlap(mario_hit_box, coffee_hit_box_) || rects_overlap(luigi_hit_box, coffee_hit_box_);
}
