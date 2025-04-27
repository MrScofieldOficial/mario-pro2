#include <cmath>
#include "coffee.hh"
#include "sprites.hh"
#include "utils.hh"

void Coffee::paint(pro2::Window& window) const {
    if (colected) {    
        return;
    }
    int frame = window.frame_count();
    int            offset = std::sin(frame* 0.1) * 2 ;
    const pro2::Pt top_left = {pos_.x + 2, pos_.y - offset};
    int sprite_id = (frame % (22 * 3)) / 3;
    paint_sprite(window, top_left, Sprites::coffe_sprites.at(sprite_id), false);
}

bool Coffee::can_collect_coin (pro2::Rect character_hit_box, pro2::Rect coffee_hit_box) {
    bool horizontal, vertical;
    horizontal = (character_hit_box.top >= coffee_hit_box.top && character_hit_box.top <= coffee_hit_box.bottom ||
                  character_hit_box.bottom >= coffee_hit_box.top && character_hit_box.bottom <= coffee_hit_box.bottom);
    vertical = (character_hit_box.left >= coffee_hit_box.left && character_hit_box.left <= coffee_hit_box.right ||
                character_hit_box.right >= coffee_hit_box.left && character_hit_box.right <= coffee_hit_box.right);
    return horizontal && vertical;
}

void Coffee::update (pro2::Window& window, const pro2::Pt& mario_pos, const pro2::Pt& luigi_pos, int& total_colected) {
    pro2::Rect mario_hit_box = {mario_pos.x - 3, mario_pos.y - 17, mario_pos.x + 11, mario_pos.y + 1};
    pro2::Rect luigi_hit_box = {luigi_pos.x - 3, luigi_pos.y - 17, luigi_pos.x + 11, luigi_pos.y + 1};
    pro2::Rect coffee_hit_box = {pos_.x + 4, pos_.y - 1, pos_.x + 13, pos_.y + 17};
    if (!colected) {
        colected = (can_collect_coin(mario_hit_box, coffee_hit_box) || can_collect_coin(luigi_hit_box, coffee_hit_box));
        if (colected)
            total_colected++;
    }
    //* Veure hit boxes
    // paint_rect(window, mario_hit_box, pro2::black);
    // paint_rect(window, luigi_hit_box, pro2::black);
    // paint_rect(window, coffee_hit_box, pro2::black);

}
