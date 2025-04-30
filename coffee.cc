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

bool Coffee::can_collect_coin (pro2::Pt character_pos) {
    bool horizontal, vertical, inside;
    pro2::Rect character_hit_box = {character_pos.x - 3, character_pos.y - 17, character_pos.x + 11, character_pos.y + 1};
    // Calcula la condició horitzontal perquè el cafè sigui recolectat
    horizontal = (character_hit_box.top >= coffee_hit_box_.top && character_hit_box.top <= coffee_hit_box_.bottom ||
                  character_hit_box.bottom >= coffee_hit_box_.top && character_hit_box.bottom <= coffee_hit_box_.bottom);
    // Calcula la condició vertical perquè el cafè sigui recolectat
    vertical = (character_hit_box.left >= coffee_hit_box_.left && character_hit_box.left <= coffee_hit_box_.right ||
                character_hit_box.right >= coffee_hit_box_.left && character_hit_box.right <= coffee_hit_box_.right);
    // Calcula si els dos rectangles es superposen completament
    inside = (character_hit_box.left <= coffee_hit_box_.left && character_hit_box.right >=  coffee_hit_box_.right &&
              character_hit_box.top <= coffee_hit_box_.top && character_hit_box.bottom >= coffee_hit_box_.bottom);
    return (horizontal && vertical) || inside;
}