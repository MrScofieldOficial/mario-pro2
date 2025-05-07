#ifndef COFFEE_HH
#define COFFEE_HH
#include "window.hh"

class Coffee {
 private:
    pro2::Pt pos_;
    pro2::Rect coffee_hit_box_ = {pos_.x + 4, pos_.y - 1, pos_.x + 13, pos_.y + 16};

    int id_;
    bool colected_;
    
    public:
    
    Coffee(pro2::Pt pos) : pos_(pos), colected_(false), id_(pos.x) {}
    Coffee(pro2::Pt pos, int id) : pos_(pos), colected_(false), id_(id) {}
    
    void paint(pro2::Window& window) const;
    bool can_collect_coin (const pro2::Rect& mario_hit_box, const pro2::Rect& luigi_hit_box); // Comprova si es pot recolectar el cafe
    
    void colect () {
        colected_ = true;   
    }

    bool is_colected() const {
        return colected_;
    }

    void set_colect(bool colected) {
        colected_ = colected;
    }

    void set_colect(bool colected, int& total_colected) {
        colected_ = colected;
        if (colected_) {
            total_colected++;
        }
    }
};
#endif