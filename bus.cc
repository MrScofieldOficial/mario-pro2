#include "bus.hh"
#include "sprites.hh"
#include "utils.hh"

void Bus::paint(pro2::Window& window) const {
    paint_sprite(window, pos1_, Sprites::bus.at("parada"), false);
    paint_sprite(window, pos2_, Sprites::bus.at("parada"), false);
}
