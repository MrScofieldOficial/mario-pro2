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
    bool win_condition_;
    bool game_over_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);
    void reiniciar(pro2::Window& window); 

    /**
     * @brief Afageix diversos cafes de manera senzilla
     * 
     * @param cafes_ Vector de Cafes
     * @param center Centre de la paràbola / recta
     * @param width Amplada (en blocs) de la paràbola / recta
     * @param height Alçada (en blocs) de la paràbola / recta
     * @param mun Nombre de cafes, per defecte 5
     */
    void add_coffees(std::vector<Coffee>& cafes_, pro2::Pt center, int width, int height, int num = 5);

    bool is_paused() const {
        return paused_;
    }
    
    bool is_finished() const {
        return finished_;
    }

    private:
    // canviar el color de les funcind: paint_hline_top_platforms (a utils) i el de pause_screen  si canvio el color del cel
    static constexpr int sky_blue = 0x9389fa;
};

#endif