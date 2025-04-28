#include "mario.hh"
#include "sprites.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

void Mario::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x - 6, pos_.y - 17};
    if (id_ == 0) {
        if (jumping_) {
            paint_sprite(window, top_left, Sprites::mario_sprite_jump_, looking_left_);
        } else if (!window.is_key_down(left_key_) && !window.is_key_down(right_key_)) {
            paint_sprite(window, top_left, Sprites::mario_sprite_normal_, looking_left_);
        } else {
            int frame = window.frame_count();
            int sprite_id = (frame % 3);
            paint_sprite(window, top_left, Sprites::mario_sprites_run_.at(sprite_id), looking_left_);
        }

    } else if (id_ == 1) {
        if (jumping_) {
            paint_sprite(window, top_left, Sprites::luigi_sprite_jump_, looking_left_);
        } else if (!window.is_key_down(left_key_) && !window.is_key_down(right_key_)) {
            paint_sprite(window, top_left, Sprites::luigi_sprite_normal_, looking_left_);
        } else {
            int frame = window.frame_count();
            int sprite_id = (frame % 3);
            paint_sprite(window, top_left, Sprites::luigi_sprites_run_.at(sprite_id), looking_left_);
        }
    }
}

void Mario::apply_physics_() {
    if (grounded_) {    
        jumping_ = false;
        speed_.y = 0;
        accel_.y = 0;
    }

    // Always falling to check if we aren't grounded
    // If we are, we will return to the same spot

    const int gravity = 1;  // gravity = 1 pixel / frame_time^2
    speed_.y += gravity;

    if (accel_time_ > 0) {
        speed_.y += accel_.y;
        accel_time_--;
    }

    pos_.x += speed_.x;
    pos_.y += speed_.y;
}

void Mario::jump() {
    if (grounded_) {
        speed_.y = -1;
        accel_.y = -6;
        grounded_ = false;
        accel_time_ = 2;
        jumping_ = true;
    }
}

void Mario::set_pos(pro2::Pt new_pos) {
    pos_ = new_pos;
}

pro2::Pt Mario::get_original_pos() {
    return original_pos_;
}

void Mario::update(pro2::Window& window, const vector<Platform>& platforms) {
    last_pos_ = pos_;
    if (window.is_key_down(jump_key_)) {
        jump();
    }

    // Velocitat horitzontal
    // if (!jumping_) {
    speed_.x = 0;
    // } else {
    //     if (looking_left_) {
    //         speed_.x = -1;
    //     } else {
    //         speed_.x = 1;
    //     }
    // }
    if (window.is_key_down(left_key_)) {
        speed_.x = -4;
    } else if (window.is_key_down(right_key_)) {
        speed_.x = 4;
    }
    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }

    // Apply acceleration and speed
    apply_physics_();

    // Check position
    set_grounded(false);

    for (const Platform& platform : platforms) {
        if (platform.has_crossed_floor_upwards(last_pos_, pos_)) {
            set_y(platform.bottom() + 16);
            speed_.y = 1;
        } else if (platform.has_crossed_floor_downwards(last_pos_, pos_)) {
            set_grounded(true);
            set_y(platform.top());
        } else if (platform.has_crossed_right(last_pos_, pos_)) {
            set_x(platform.right() + 4);
        } else if (platform.has_crossed_left(last_pos_, pos_)) {
            set_x(platform.left() - 11);
        }
    }
}
