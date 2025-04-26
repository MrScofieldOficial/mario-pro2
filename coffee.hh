#ifndef COFFEE_HH
#define COFFEE_HH
#include "window.hh"

class Coffee {
 private:
    pro2::Pt pos_;

    int colected_;

 public:
    Coffee(pro2::Pt pos) : pos_(pos) {}

    void paint(pro2::Window& window) const;
    void is_in (pro2::Rect mario_hit_box, pro2::Rect coffee_hit_box);
};
#endif