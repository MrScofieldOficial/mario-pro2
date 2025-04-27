#ifndef COFFEE_HH
#define COFFEE_HH
#include "window.hh"

class Coffee {
 private:
    pro2::Pt pos_;

    
    public:
    bool colected;
    
    Coffee(pro2::Pt pos) : pos_(pos), colected(false) {}

    void paint(pro2::Window& window) const;
    bool can_collect_coin (pro2::Rect character_hit_box, pro2::Rect coffee_hit_box);
    void update (pro2::Window& window, const pro2::Pt& mario_pos, const pro2::Pt& luigi_pos, int& total_colected);
};
#endif