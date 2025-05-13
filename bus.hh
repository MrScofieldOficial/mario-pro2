#ifndef BUS_HH
#define BUS_HH

#include "window.hh"

class Bus {
 private:
    pro2::Pt pos1_, pos2_;
    int id_;  // Número de línia (0 - 9)

 public:
    /**
     * @brief Constructor de Bus amb id automàtic (basat en la X per aleatorietat)
     * 
     * @param pos1 Posició de la pimera parada
     * @param pos1 Posició de la segona parada
     */
    Bus(pro2::Pt pos1, pro2::Pt pos2) : pos1_(pos1), pos2_(pos2), id_(0) {}

    /**
     * @brief Constructor de Bus amb id específic
     * 
     * @param pos1 Posició de la pimera parada
     * @param pos1 Posició de la segona parada
     * @param id Identificador del núvol
     */
    Bus(pro2::Pt pos1, pro2::Pt pos2, int id) : pos1_(pos1), pos2_(pos2), id_(id) {}

    /**
     * @brief Pinta les parades a la finestra
     * 
     * @param window Finestra on es pinta
     */
    void paint(pro2::Window& window) const;
};

#endif
