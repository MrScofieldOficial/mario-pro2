#ifndef BUS_HH
#define BUS_HH

#include "window.hh"

class Bus {
 private:
    pro2::Pt pos_;
    std::string stop_num_;  // Número de línia (0 - 9)
    std::string stop_id_;  // Id per saber si es una de dos (0 - 1)
    pro2::Rect hit_box_;
    int k_;

 public:
    /**
     * @brief Constructor de Bus amb id automàtic (basat en la X per aleatorietat)
     * 
     * @param pos Posició de la parada
     */
    Bus(pro2::Pt pos, int k) : pos_(pos * k), stop_num_("0"), stop_id_("0"), k_(k), hit_box_ ({pos_.x, pos_.y, pos_.x + 4*k, pos_.y + 2*k}) {}

    /**
     * @brief Constructor de Bus amb id específic
     * 
     * @param pos Posició de la parada
     * @param id Identificador del núvol
     */
    Bus(pro2::Pt pos, std::string num, std::string id, int k) : pos_(pos * k), stop_num_(num), stop_id_(id), k_(k), hit_box_ ({pos_.x, pos_.y, pos_.x + 4*k, pos_.y + 2*k}) {}

    /**
     * @brief Pinta la parada
     * 
     * @param window Finestra on es pinta
     */
    void paint(pro2::Window& window) const;

    int update(const pro2::Rect& character_hit_box);

    pro2::Rect get_rect() const { return hit_box_; }
    
    pro2::Pt get_pos() { return pos_; }

    int get_num() { return stoi(stop_num_); }

    int get_id() { return stoi(stop_id_); }
    
};

#endif
