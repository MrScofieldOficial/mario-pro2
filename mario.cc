#include "mario.hh"
#include "sprites.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

void Mario::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x - 6, pos_.y - 17};
    string sprite_id; // Declara la id del sprite que es va construint depenent de les variables
    if (id_ == 0) {
        sprite_id = "mario_sprite_"; // mario_sprite_
    } else if (id_ == 1) {
        sprite_id = "luigi_sprite_"; // luigi_sprite_
    }
    if (rush_) {
        sprite_id += "blushed_";
    }
    if (jumping_) {
        sprite_id += "jump_";  // mario_sprite_jump_ o luigi_sprite_jump_
        paint_sprite(window, top_left, Sprites::character_sprites.at(sprite_id), looking_left_);
    } else if (!window.is_key_down(left_key_) && !window.is_key_down(right_key_)) {
        sprite_id += "normal_";  // mario_sprite_normal_ o luigi_sprite_normal_
        paint_sprite(window, top_left, Sprites::character_sprites.at(sprite_id), looking_left_);
    } else {
        int frame = window.frame_count();
        // Escull entre les 3 sprites de córrer respecte el frame que ens trobem
        sprite_id += "run_" + std::to_string(frame % 3);  // mario_sprite_run_{0,1,2} o luigi_sprite_run_{0,1,2}
        paint_sprite(window, top_left, Sprites::character_sprites.at(sprite_id), looking_left_);
    }
}

void Mario::paint_rush_bar(pro2::Window& window, pro2::Pt cam, int total_coffee) {
    int bar_lenght = 70;
    int right = cam.x + window.width() / 3 + 70, top = cam.y - window.height() / 2.5 + 6;
    int percent_decrease = 0;
    int percent_increase = 0;
    if (rush_) {
        percent_decrease = (rush_time_ * bar_lenght) / rush_time_max_;
    } else {
        percent_increase = bar_lenght - ((total_coffee % coffee_for_rush) * bar_lenght) / coffee_for_rush;
    }
    pro2::Rect bar = {right - bar_lenght + percent_decrease + percent_increase, top, right, top + 7};
    paint_rect(window, bar, 0x824217);
    pro2::Rect outline = {right - bar_lenght, top, right, top + 7};
    paint_rect_outline(window, outline, 0xf5e59d);
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

void Mario::jump(float mult) {
    if (grounded_) {
        speed_.y = -1;
        accel_.y = -6 * mult;
        grounded_ = false;
        accel_time_ = 2;
        jumping_ = true;
    }
}

void Mario::update(pro2::Window& window, const vector<Platform>& platforms, vector<Coffee>& cafes, int& total_coffee) {
    float run_mult = 1;
    float jump_mult = 1;
    if (rush_) {
        jump_mult = 1.3;
        run_mult = 1.5;
    }

    last_pos_ = pos_;
    if (window.is_key_down(jump_key_)) {
        jump(jump_mult);
    }

    // Velocitat horitzontal
    speed_.x = 0;
    if (window.is_key_down(left_key_)) {
        speed_.x = -4 * run_mult;
    } else if (window.is_key_down(right_key_)) {
        speed_.x = 4 * run_mult;
    }
    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }

    // Apply acceleration and speed
    apply_physics_();

    // Check position
    set_grounded(false);

    // Check Platform interactions
    for (const Platform& platform : platforms) {
        std::string id = platform.id();
        if (platform.has_crossed_floor_downwards(last_pos_, pos_)) {
            set_grounded(true);
            set_y(platform.top());
        } else if (platform.has_crossed_floor_upwards(last_pos_, pos_) && id != "cloud") {
            set_y(platform.bottom() + 16);
            speed_.y = 1;
        } else if (platform.has_crossed_right(last_pos_, pos_) && id != "cloud") {
            set_x(platform.right() + 4);
        } else if (platform.has_crossed_left(last_pos_, pos_) && id != "cloud") {
            set_x(platform.left() - 11);
        }
    }

    // Calculates all the rush logic
    if (!rush_) {
        if (total_coffee % coffee_for_rush == 0 && total_coffee != last_rush_) {
            rush_ = true;
            last_rush_ = total_coffee;
        }
    } else {
        if (rush_time_ <= rush_time_max_) {
            rush_time_++;
        }
        else {
            rush_ = false;
            rush_time_ = 0;
        }
    }
}
