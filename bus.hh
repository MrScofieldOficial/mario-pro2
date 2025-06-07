#ifndef BUS_HH
#define BUS_HH

#include "window.hh"

class Bus {
 private:
    pro2::Pt pos_;
    std::string stop_num_;  // Número de línia (0 - 9)
    std::string stop_id_;   // Id per saber si és una de dos (0 - 1)
    pro2::Rect hit_box_;
    int k_;

 public:
    /**
     * @brief Constructor de Bus amb id automàtic (0)
     * 
     * @param pos Posició de la parada
     * @param k Factor d'escalat per calcular la posició i hitbox
     */
    Bus(pro2::Pt pos, int k)
        : pos_({pos.x * k + 2, pos.y * k}),
          stop_num_("0"),
          stop_id_("0"),
          k_(k),
          hit_box_({pos_.x, pos_.y, pos_.x + 4*k, pos_.y + 2*k}) {}

    /**
     * @brief Constructor de Bus amb id específic
     * 
     * @param pos Posició de la parada
     * @param num Número de línia del bus (com a string)
     * @param id Identificador de la parada (com a string)
     * @param k Factor d'escalat per calcular la posició i hitbox
     */
    Bus(pro2::Pt pos, std::string num, std::string id, int k)
        : pos_({pos.x * k + 2, pos.y * k}),
          stop_num_(num),
          stop_id_(id),
          k_(k),
          hit_box_({pos_.x, pos_.y, pos_.x + 4*k, pos_.y + 2*k}) {}

    /**
     * @brief Pinta la parada
     * 
     * @param window Finestra on es pinta
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Actualitza l'estat del bus segons la col·lisió amb el personatge
     * 
     * @param character_hit_box Hitbox del personatge
     * @return enter les desenes del qual representen el número de parada i les unitats la id de la parada
     *         retorna 0 si el personatge no està dins d'una parada
     */
    int update(const pro2::Rect& character_hit_box);

    /**
     * @brief Retorna el rectangle de col·lisió (hitbox) de la parada de bus
     * 
     * @return pro2::Rect Hitbox del bus
     */
    pro2::Rect get_rect() const { return hit_box_; }

    /**
     * @brief Retorna la posició del bus
     * 
     * @return pro2::Pt Posició del bus
     */
    pro2::Pt get_pos() { return pos_; }

    /**
     * @brief Retorna el número de línia del bus
     * 
     * @return int Número de línia (convertit de string)
     */
    int get_num() { return stoi(stop_num_); }

    /**
     * @brief Retorna l'identificador de la parada
     * 
     * @return int Identificador (convertit de string)
     */
    int get_id() { return stoi(stop_id_); }
};

#endif
