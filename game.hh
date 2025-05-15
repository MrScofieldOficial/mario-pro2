#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "coffee.hh"
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "ui.hh"
#include "cloud.hh"
#include "finder.hh"
#include "bus.hh"

/**
 * @brief Classe principal del joc.
 *
 * Gestiona els personatges, els objectes col·leccionables, plataformes,
 * càmera, estat del joc i lògica principal.
 */
class Game {
    Mario                 mario_;
    Mario                 luigi_;
    std::vector<Platform> platforms_;   // Vector de plataformes del món
    std::vector<Coffee>   cafes_;       // Vector de cafès col·leccionables
    std::vector<Cloud>    clouds_;   // Vector de núvols
    std::vector<Bus>      busos_;   // Vector de parades de bus

    bool finished_;
    bool paused_;
    bool following_;      // Indica si la càmera segueix el mario (true) o al luigi (false)
    int  cooldown_keys_;  // Cooldown per evitar múltiples deteccions de teclat
    int  total_coffees_;  // Comptador de cafès col·leccionats
    bool win_condition_;  // Indica si s’ha guanyat
    bool game_over_;      // Indica si s’ha perdut

    bool in_stop_;        // Indica si està a una parada
    int stop_id_;         // Guarda la id de la parada
    bool mario_in_stop_;  // Si el mario esta un una parada de bus
    bool luigi_in_stop_;  // Si el luigi esta un una parada de bus
    pro2::Pt bus_pos_;    // Posició del sprite del bus
    bool teleport;        // Si he canviat de parada
    pro2::Pt stop_pos_;   // La posicio de la seguent parada
    bool bus_moving_;     // Si el bus s'està movent

    Finder<Platform> platform_finder_;
    Finder<Coffee> coffee_finder_;
    std::set<Platform*> visible_platforms_;
    std::set<Coffee*> visible_coffee_;  

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

    /**
     * @brief Inicialitza els núvols.
     */
    void init_clouds();

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


    void centrar_camera (pro2::Pt character_pos, pro2::Window& window);

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
     * @brief Comprova si un punt està prou lluny dels núvols existents.
     *
     * @param p Punt candidat a afegir.
     * @param min_dist Distància mínima requerida respecte tots els altres núvols.
     * 
     * @return Cert si el punt està a una distància igual o superior de tots els núvols, fals altrament.
     */
    bool is_far_enough(const pro2::Pt& p, int min_dist);

    /**
     * @brief Afegeix núvols aleatoris dins d’un rectangle, separats entre ells.
     *
     * @param left Coordenada x mínima del rectangle.
     * @param top Coordenada y mínima del rectangle.
     * @param right Coordenada x màxima del rectangle.
     * @param bottom Coordenada y màxima del rectangle.
     * @param num_clouds Nombre de núvols que es volen afegir.
     * @param min_dist Distància mínima entre qualsevol parella de núvols.
     */
    void add_clouds(int left, int top, int right, int bottom, int num_clouds, int min_dist);

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
    // canviar el color de les funcind: paint_hline_top_platforms (a utils), el de pause_screen i el del sprite del bus si canvio el color del cel
    static constexpr int sky_blue = 0x9389fa;
};

#endif
