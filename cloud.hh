#ifndef CLOUD_HH
#define CLOUD_HH

#include "window.hh"

class Cloud {
 private:
    pro2::Pt pos_, original_pos_;
    int id_;

 public:
    /**
     * @brief Constructor de Cloud amb id automàtic (basat en la X per aleatorietat)
     * 
     * @param pos Posició inicial del núvol
     */
    Cloud(pro2::Pt pos) : pos_(pos), original_pos_(pos), id_(0) {}

    /**
     * @brief Constructor de Cloud amb id específic
     * 
     * @param pos Posició inicial del núvol
     * @param id Identificador del núvol
     */
    Cloud(pro2::Pt pos, int id) : pos_(pos), original_pos_(pos), id_(id) {}

    /**
     * @brief Pinta el núvol a la finestra
     * 
     * @param window Finestra on es pinta
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Actualitza la posició del núvol per aconseguir un efecte de "paralax"
     * 
     * @param window Finestra on es pinta
     * @param reference_pos Posició de referència
     */
    void update(pro2::Window& window, pro2::Pt reference_pos);

    /**
     * @brief Restaura la posició inicial
     */
    void reset_pos() { pos_ = original_pos_; }

    /**
     * @brief Retorna la posicio actual
     */
    pro2::Pt pos() const { return pos_; }
};

#endif
