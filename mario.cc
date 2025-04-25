#include "mario.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int f = pro2::black;
const int g = pro2::green;
const int h = 0x964807;

// clang-format off
const vector<vector<int>> Mario::mario_sprite_normal_ = {
    {_, _, _, r, r, r, r, r, _, _, _, _},
    {_, _, r, r, r, r, r, r, r, r, r, _},
    {_, _, h, h, h, s, s, f, s, _, _, _},
    {_, h, s, h, s, s, s, f, s, s, s, _},
    {_, h, s, h, h, s, s, s, f, s, s, s},
    {_, h, h, s, s, s, s, f, f, f, f, _},
    {_, _, _, s, s, s, s, s, s, s, _, _},
    {_, _, r, r, b, r, r, r, _, _, _, _},
    {_, r, r, r, b, r, r, b, r, r, r, _},
    {r, r, r, r, b, b, b, b, r, r, r, r},
    {s, s, r, b, y, b, b, y, b, r, s, s},
    {s, s, s, b, b, b, b, b, b, s, s, s},
    {s, s, b, b, b, b, b, b, b, b, s, s},
    {_, _, b, b, b, _, _, b, b, b, _, _},
    {_, h, h, h, _, _, _, _, h, h, h, _},
    {h, h, h, h, _, _, _, _, h, h, h, h},
};

const vector<vector<int>> Mario::luigi_sprite_normal_ = {
    {_, _, _, g, g, g, g, g, _, _, _, _},
    {_, _, g, g, g, g, g, g, g, g, g, _},
    {_, _, h, h, h, s, s, f, s, _, _, _},
    {_, h, s, h, s, s, s, f, s, s, s, _},
    {_, h, s, h, h, s, s, s, f, s, s, s},
    {_, h, h, s, s, s, s, f, f, f, f, _},
    {_, _, _, s, s, s, s, s, s, s, _, _},
    {_, _, g, g, b, g, g, g, _, _, _, _},
    {_, g, g, g, b, g, g, b, g, g, g, _},
    {g, g, g, g, b, b, b, b, g, g, g, g},
    {s, s, g, b, y, b, b, y, b, g, s, s},
    {s, s, s, b, b, b, b, b, b, s, s, s},
    {s, s, b, b, b, b, b, b, b, b, s, s},
    {_, _, b, b, b, _, _, b, b, b, _, _},
    {_, h, h, h, _, _, _, _, h, h, h, _},
    {h, h, h, h, _, _, _, _, h, h, h, h},
};

// clang-format on

void Mario::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x - 6, pos_.y - 15};
    if (id_ == 0) {
        paint_sprite(window, top_left, mario_sprite_normal_, looking_left_);
    } else if (id_ == 1) {
        paint_sprite(window, top_left, luigi_sprite_normal_, looking_left_);
    }
}

void Mario::apply_physics_() {
    if (grounded_) {
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
        accel_.y = -6;
        grounded_ = false;
        accel_time_ = 2;
    }
}

void Mario::update(pro2::Window& window, const vector<Platform>& platforms) {
    last_pos_ = pos_;
    if (window.is_key_down(jump_key_)) {
        jump();
    }

    // Velocitat horitzontal
    speed_.x = 0;
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
        if (platform.has_crossed_floor_downwards(last_pos_, pos_)) {
            set_grounded(true);
            set_y(platform.top());
        }
    }
}
