#include <cmath>
#include "coffee.hh"
#include "sprites.hh"
#include "utils.hh"

void Coffee::paint(pro2::Window& window) const {
    // Si està recolectat no el pintem
    if (colected_) {    
        return;
    }
    int frame = window.frame_count();
    // Calcula el offset vertical seguint un moviment sinusoidal (la id canvia el desfasament inicial)
    int            offset = std::sin(frame* 0.1 - id_ * 2) * 3.5;
    // Escull entre les 22 sprites de gir respecte el frame que ens trobem i enlenteix el movient 3 cops
    int sprite_id = ((frame + 22 * id_) % (22 * 3)) / 3;
    const pro2::Pt top_left = {pos_.x + 2, pos_.y - offset - 3};
    paint_sprite(window, top_left, Sprites::coffe_sprites.at(sprite_id), false);
}

bool Coffee::can_collect_coin (const pro2::Rect& mario_hit_box, const pro2::Rect& luigi_hit_box) {
    return rects_overlap (mario_hit_box, coffee_hit_box_) || rects_overlap (luigi_hit_box, coffee_hit_box_);
}