#ifndef COFFEE_HH
#define COFFEE_HH

#include "window.hh"

class Coffee {
 private:
    pro2::Pt pos_;
    pro2::Rect coffee_hit_box_ = {pos_.x + 4, pos_.y - 1, pos_.x + 13, pos_.y + 16};
    int id_;
    bool colected_;

 public:
    /**
     * @brief Constructor de Coffee amb id automàtic (basat en la X per aleatorietat)
     * 
     * @param pos Posició inicial del cafè
     */
    Coffee(pro2::Pt pos) : pos_(pos), colected_(false), id_(pos.x) {}

    /**
     * @brief Constructor de Coffee amb id específic
     * 
     * @param pos Posició inicial del cafè
     * @param id Identificador del cafè
     */
    Coffee(pro2::Pt pos, int id) : pos_(pos), colected_(false), id_(id) {}

    /**
     * @brief Pinta el cafè a la finestra
     * 
     * @param window Finestra on es pinta
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Comprova si Mario o Luigi poden recollir aquest cafè
     * 
     * @param mario_hit_box Caixa de col·lisió de Mario
     * @param luigi_hit_box Caixa de col·lisió de Luigi
     * @return Cert si algun dels dos pot recollir-lo
     */
    bool can_collect_coffee(const pro2::Rect& mario_hit_box, const pro2::Rect& luigi_hit_box);

    /**
     * @brief Marca el cafè com a recollit
     */
    void colect() { colected_ = true; }

    /**
     * @brief Indica si el cafè ha estat recollit
     * 
     * @return Cert si ha estat recollit
     */
    bool is_colected() const { return colected_; }

    /**
     * @brief Assigna si el cafè ha estat recollit
     * 
     * @param colected Estat de recollida
     */
    void set_colect(bool colected) { colected_ = colected; }

    /**
     * @brief Marca el cafè com a recollit i actualitza el comptador total
     * 
     * @param colected Estat de recollida
     * @param total_colected Referència al comptador global de cafès recollits
     */
    void set_colect(bool colected, int& total_colected) {
        colected_ = colected;
        if (colected_) {
            total_colected++;
        }
    }
};

#endif
