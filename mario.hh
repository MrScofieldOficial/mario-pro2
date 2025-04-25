#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"

class Mario {
 private:
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;
    int      id_;

    bool grounded_ = false;
    bool looking_left_ = false;
    bool jumping_ = false;

    char jump_key_;
    char left_key_;
    char right_key_;

    void apply_physics_();

 public:
    Mario(pro2::Pt pos, int id)
        : pos_(pos),
          last_pos_(pos),
          jump_key_(pro2::Keys::Up),
          left_key_(pro2::Keys::Left),
          right_key_(pro2::Keys::Right),
          id_(id) {}

    Mario(pro2::Pt pos, char jump_key, char left_key, char right_key, int id)
        : pos_(pos),
          last_pos_(pos),
          jump_key_(jump_key),
          left_key_(left_key),
          right_key_(right_key),
          id_(id) {}

    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }

    void set_y(int y) {
        pos_.y = y;
    }

    bool is_grounded() const {
        return grounded_;
    }

    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

    void toggle_grounded() {
        set_grounded(!grounded_);
    }

    void jump();

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
    static const std::vector<std::vector<int>> mario_sprite_jump_;
    static const std::vector<std::vector<int>> mario_sprite_run0_;
    static const std::vector<std::vector<int>> mario_sprite_run1_;
    static const std::vector<std::vector<int>> mario_sprite_run2_;

    static const std::vector<std::vector<int>> luigi_sprite_normal_;
    static const std::vector<std::vector<int>> luigi_sprite_jump_;
    static const std::vector<std::vector<int>> luigi_sprite_run0_;
    static const std::vector<std::vector<int>> luigi_sprite_run1_;
    static const std::vector<std::vector<int>> luigi_sprite_run2_;
};

#endif