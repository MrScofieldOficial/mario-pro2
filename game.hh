#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "coffee.hh"
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "ui.hh"

/**
 * @brief Classe principal del joc.
 *
 * Gestiona els personatges, els objectes col·leccionables, plataformes,
 * càmera, estat del joc i lògica principal.
 */
class Game {
    Mario                 mario_;
    Mario                 luigi_;
    std::vector<Coffee>   cafes_;       // Vector de cafès col·leccionables
    std::vector<Platform> platforms_;   // Vector de plataformes del món

    bool finished_;
    bool paused_;
    bool following_;      // Indica si la càmera segueix el mario (true) o al luigi (false)
    int  cooldown_keys_;  // Cooldown per evitar múltiples deteccions de teclat
    int  total_coffees_;  // Comptador de cafès col·leccionats
    bool win_condition_;  // Indica si s’ha guanyat
    bool game_over_;      // Indica si s’ha perdut

    /**
     * @brief Processa l’entrada del teclat.
     */
    void process_keys(pro2::Window& window);

    /**
     * @brief Actualitza l’estat dels objectes del joc.
     */
    void update_objects(pro2::Window& window);

    /**
     * @brief Actualitza la posició de la càmera.
     */
    void update_camera(pro2::Window& window);

    /**
     * @brief Inicialitza les plataformes del joc.
     */
    void init_platforms();

    /**
     * @brief Inicialitza els cafès del joc.
     */
    void init_coffees();

 public:
    /**
     * @brief Constructor del joc.
     *
     * @param width Amplada de la finestra.
     * @param height Alçada de la finestra.
     */
    Game(int width, int height);

    /**
     * @brief Actualitza el joc (entrada, física, càmera, etc.).
     */
    void update(pro2::Window& window);

    /**
     * @brief Dibuixa tot el contingut del joc.
     */
    void paint(pro2::Window& window);

    /**
     * @brief Reinicia el joc deixant-lo com al començament.
     */
    void reiniciar(pro2::Window& window); 

    /**
     * @brief Afegeix diversos cafès de forma senzilla.
     *
     * @param cafes_ Vector de cafès on s’afegiran.
     * @param center Centre de la paràbola o línia.
     * @param width Amplada (en blocs) de la paràbola / línia.
     * @param height Alçada (en blocs) de la paràbola / línia.
     * @param num Nombre de cafès a afegir (per defecte 5).
     */
    void add_coffees(std::vector<Coffee>& cafes_, pro2::Pt center, int width, int height, int num = 5);

    /**
     * @brief Consulta si el joc està pausat.
     */
    bool is_paused() const {
        return paused_;
    }

    /**
     * @brief Consulta si el joc ha finalitzat.
     */
    bool is_finished() const {
        return finished_;
    }

 private:
    // canviar el color de les funcind: paint_hline_top_platforms (a utils) i el de pause_screen  si canvio el color del cel
    static constexpr int sky_blue = 0x9389fa;
};

#endif
