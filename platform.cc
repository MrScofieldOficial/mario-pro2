#include "platform.hh"
#include "utils.hh"
using namespace std;

using pro2::Color;

const int b = 0xc84d0b;
const int _ = 0;

// clang-format off
// const vector<vector<int>> Platform::brick_platform_texture_ = {
//  {b, b, b, b, b, b, _}, 
// 	{b, b, b, b, b, b, _}, 
// 	{b, b, b, b, b, b, _}, 
// 	{_, _, _, _, _, _, _},
//  {b, b, b, _, b, b, b}, 
// 	{b, b, b, _, b, b, b}, 
// 	{b, b, b, _, b, b, b}, 
// 	{_, _, _, _, _, _, _},
// };

const vector<vector<int>> Platform::brick_platform_texture_ = {
    {_, b, b, b, b, b, b, b, _, b, b, b, b, b, b, b},
    {_, b, b, b, b, b, b, b, _, b, b, b, b, b, b, b},
    {_, b, b, b, b, b, b, b, _, b, b, b, b, b, b, b},
    {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
    {b, b, b, b, _, b, b, b, b, b, b, b, _, b, b, b},
    {b, b, b, b, _, b, b, b, b, b, b, b, _, b, b, b},
    {b, b, b, b, _, b, b, b, b, b, b, b, _, b, b, b},
    {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
    {_, b, b, b, b, b, b, b, _, b, b, b, b, b, b, b},
    {_, b, b, b, b, b, b, b, _, b, b, b, b, b, b, b},
    {_, b, b, b, b, b, b, b, _, b, b, b, b, b, b, b},
    {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
    {b, b, b, b, _, b, b, b, b, b, b, b, _, b, b, b},
    {b, b, b, b, _, b, b, b, b, b, b, b, _, b, b, b},
    {b, b, b, b, _, b, b, b, b, b, b, b, _, b, b, b},
    {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
};
// clang-format on

void Platform::paint(pro2::Window& window) const {
    const int xsz = brick_platform_texture_.size();
    const int ysz = brick_platform_texture_[0].size();
    for (int i = top_ + 1; i <= bottom_; i++) {
        for (int j = left_; j <= right_; j++) {
            window.set_pixel({j, i},
                             brick_platform_texture_[(i - top_ - 1) % xsz][(j - left_) % ysz]);
        }
    }
    paint_hline(window, left_, right_, top_ + 1, 0xfcd8a9);
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