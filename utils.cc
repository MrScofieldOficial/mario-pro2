#include "utils.hh"

namespace pro2 {

// Dibuixa una línia horitzontal
void paint_hline(pro2::Window& window, int xini, int xfin, int y, Color color) {
    for (int x = xini; x <= xfin; ++x) {
        window.set_pixel({x, y}, color);
    }
}

// Dibuixa una línia vertical
void paint_vline(pro2::Window& window, int x, int yini, int yfin, Color color) {
    for (int y = yini; y <= yfin; ++y) {
        window.set_pixel({x, y}, color);
    }
}

// Pinta un rectangle ple amb el color especificat
void paint_rect(pro2::Window& window, pro2::Rect rect, Color color) {
    for (int y = rect.top; y < rect.bottom; ++y) {
        for (int x = rect.left; x < rect.right; ++x) {
            window.set_pixel({x, y}, color);
        }
    }
}

// Pinta el contorn d’un rectangle
void paint_rect_outline(pro2::Window& window, pro2::Rect rect, Color color) {
    paint_hline(window, rect.left, rect.right, rect.top, color);
    paint_hline(window, rect.left, rect.right, rect.bottom, color);
    paint_vline(window, rect.left, rect.top, rect.bottom, color);
    paint_vline(window, rect.right, rect.top, rect.bottom, color);
}

// Dibuixa un sprite 
void paint_sprite(pro2::Window& window, pro2::Pt orig, const std::vector<std::vector<int>>& sprite, bool mirror) {
    for (int i = 0; i < sprite.size(); ++i) {
        const auto& line = sprite[i];
        for (int j = 0; j < line.size(); ++j) {
            int _j = mirror ? line.size() - j - 1 : j;
            if (line[_j] >= 0) {
                window.set_pixel({orig.x + j, orig.y + i}, line[_j]);
            }
        }
    }
}

// Comprova si dos rectangles es sobreposen
bool rects_overlap(const pro2::Rect& rect1, const pro2::Rect& rect2) {
    return !(rect1.right < rect2.left ||
             rect1.left > rect2.right ||
             rect1.top > rect2.bottom ||
             rect1.bottom < rect2.top);
}

} // namespace pro2
