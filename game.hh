#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "coffee.hh"
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "ui.hh"

class Game {
    Mario                 mario_;
    Mario                 luigi_;
    std::vector<Coffee>   cafes_;
    std::vector<Platform> platforms_;

    bool finished_;
    bool paused_;
    bool following_;
    int  cooldown_keys_;
    int total_coffees_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);
    void pause(pro2::Window& window);
    void reiniciar(pro2::Window& window);

    bool is_paused() const {
        return paused_;
    }

    bool is_finished() const {
        return finished_;
    }

    void add_coffees(std::vector<Coffee>& cafes_, int center_x, int center_y, int width, int height, int num = 5);

    private:
    // canviar el color de la funcio :paint_hline_top_platforms (a utils) si canvio el color del cel;
    static constexpr int sky_blue = 0x9389fa;
};

#endif