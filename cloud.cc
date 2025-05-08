#include "cloud.hh"
#include "sprites.hh"
#include "utils.hh"

void Cloud::paint(pro2::Window& window) const {
    std::string sprite_id = (id_ == 1? "nuvol_gran": "nuvol_petit");
    paint_sprite(window, pos_, Sprites::altres.at(sprite_id), false);
}

void Cloud::update(pro2::Window& window, pro2::Pt reference_pos) {
    if (reference_pos.y + window.height() / 2 > 360 || reference_pos.x - window.width() / 2 < 0) {
        return;
    }
    // Parallax factor: quant més petit, més lent es mou el núvol (efecte llunyà)
    const float parallax_factor = 0.2;

    // Calcular la distància horitzontal entre la càmera i la posició original del núvol
    int dx = original_pos_.x - reference_pos.x;
    int dy = original_pos_.y - reference_pos.y;

    // Aplicar el factor per desplaçar el núvol a una nova posició en funció de la càmera
    pos_.x = original_pos_.x + dx * parallax_factor;
    pos_.y = original_pos_.y + dy * parallax_factor;
}