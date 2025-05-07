#include "platform.hh"
#include "utils.hh"
#include "sprites.hh"
using namespace std;

void Platform::paint(pro2::Window& window) const {
    const int xsz = Sprites::platform_textures.at(id_).size();
    const int ysz = Sprites::platform_textures.at(id_)[0].size();
    for (int i = top_ + 1; i <= bottom_; i++) {
        for (int j = left_; j <= right_; j++) {
            window.set_pixel({j, i}, Sprites::platform_textures.at(id_)[(i - top_ - 1) % xsz][(j - left_) % ysz]);
        }
    }
    if (id_ == "brick") {
        paint_hline(window, left_, right_, top_ + 1, 0xfcd8a9);
    }
}

bool Platform::has_crossed_floor_downwards(pro2::Pt plast, pro2::Pt pcurr) const {
    return (left_ <= plast.x && plast.x <= right_) && (left_ <= pcurr.x && pcurr.x <= right_) &&
           (plast.y <= top_ && pcurr.y >= top_);
}       

bool Platform::has_crossed_floor_upwards(pro2::Pt plast, pro2::Pt pcurr) const {
    pcurr.y -= 16;
    return (left_ <= plast.x && plast.x <= right_) && (left_ <= pcurr.x && pcurr.x <= right_) &&
           (plast.y >= bottom_ && pcurr.y <= bottom_);
}

bool Platform::has_crossed_right(pro2::Pt plast, pro2::Pt pcurr) const {
    pcurr.x -= 4;
    return left_ <= pcurr.x && pcurr.x <= right_ && top_ <= pcurr.y && pcurr.y <= bottom_ &&
           plast.x > right_;
}

bool Platform::has_crossed_left(pro2::Pt plast, pro2::Pt pcurr) const {
    pcurr.x += 11;
    return left_ <= pcurr.x && pcurr.x <= right_ && top_ <= pcurr.y && pcurr.y <= bottom_ &&
           plast.x < left_;
}

bool Platform::is_pt_inside(pro2::Pt pt) const {
    return left_ <= pt.x && pt.x <= right_ && top_ <= pt.y && pt.y <= bottom_;
}