#include "platform.hh"
#include "utils.hh"
#include "sprites.hh"

void Platform::paint(pro2::Window& window) const {
    const int xsz = Sprites::platform_textures.at(id_).size();
    const int ysz = Sprites::platform_textures.at(id_)[0].size();

    for (int i = top_ + 1; i <= bottom_; i++) {
        for (int j = left_; j <= right_; j++) {
            window.set_pixel({j, i}, Sprites::platform_textures.at(id_)[(i - top_ - 1) % xsz][(j - left_) % ysz]);
        }
    }

    if (id_ == "brick") {
        // Dibuixa una línia superior especial per a plataformes de tipus brick
        paint_hline(window, left_, right_, top_ + 1, 0xfcd8a9);
    }
}

// Detecta si el personatge ha travessat el terra cap avall
bool Platform::has_crossed_floor_downwards(pro2::Pt plast, pro2::Pt pcurr) const {
    return (left_ <= plast.x && plast.x <= right_) &&
           (left_ <= pcurr.x && pcurr.x <= right_) &&
           (plast.y <= top_ && pcurr.y >= top_);
}

// Detecta si ha travessat el terra des de sota cap amunt
bool Platform::has_crossed_floor_upwards(pro2::Pt plast, pro2::Pt pcurr) const {
    pcurr.y -= 16; // Ajusta per l'alçada del personatge (per detectar contacte inferior)
    return (left_ <= plast.x && plast.x <= right_) &&
           (left_ <= pcurr.x && pcurr.x <= right_) &&
           (plast.y >= bottom_ && pcurr.y <= bottom_);
}

// Detecta si ha xocat amb la paret dreta de la plataforma
bool Platform::has_crossed_right(pro2::Pt plast, pro2::Pt pcurr) const {
    pcurr.x -= 4; // Ajusta per l'amplada del personatge a l'esquerra
    return left_ <= pcurr.x && pcurr.x <= right_ &&
           top_ <= pcurr.y && pcurr.y <= bottom_ &&
           plast.x > right_;
}

// Detecta si ha xocat amb la paret esquerra de la plataforma
bool Platform::has_crossed_left(pro2::Pt plast, pro2::Pt pcurr) const {
    pcurr.x += 11; // Ajusta per l'amplada del personatge a la dreta
    return left_ <= pcurr.x && pcurr.x <= right_ &&
           top_ <= pcurr.y && pcurr.y <= bottom_ &&
           plast.x < left_;
}

// Comprova si un punt està dins de la plataforma
bool Platform::is_pt_inside(pro2::Pt pt) const {
    return left_ <= pt.x && pt.x <= right_ &&
           top_ <= pt.y && pt.y <= bottom_;
}
