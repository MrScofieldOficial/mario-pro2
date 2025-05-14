#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>

#include "coffee.hh"
#include "platform.hh"
#include "utils.hh"
#include "window.hh"

class Mario {
 private:
    pro2::Pt pos_, last_pos_, original_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int accel_time_ = 0;
    int id_;  // 0 = mario, 1 = luigi

    bool grounded_ = false;
    bool looking_left_ = false;
    bool jumping_ = false;

    bool rush_ = false;
    int rush_time_ = 0;
    int rush_time_max_ = 130;
    int last_rush_ = 0;
    int coffee_for_rush = 14;

    char jump_key_;
    char left_key_;
    char right_key_;

    void apply_physics_();

 public:
    /**
     * @brief Constructor per defecte de Mario
     * 
     * @param pos Posició inicial
     * @param id Identificador del personatge (0 = Mario, 1 = Luigi)
     */
    Mario(pro2::Pt pos, int id)
        : pos_(pos),
          last_pos_(pos),
          original_pos_(pos),
          jump_key_(pro2::Keys::Up),
          left_key_(pro2::Keys::Left),
          right_key_(pro2::Keys::Right),
          id_(id) {}

    /**
     * @brief Constructor amb tecles personalitzades
     * 
     * @param pos Posició inicial
     * @param jump_key Tecla de salt
     * @param left_key Tecla esquerra
     * @param right_key Tecla dreta
     * @param id Identificador del personatge
     */
    Mario(pro2::Pt pos, char jump_key, char left_key, char right_key, int id)
        : pos_(pos),
          last_pos_(pos),
          original_pos_(pos),
          jump_key_(jump_key),
          left_key_(left_key),
          right_key_(right_key),
          id_(id) {}

    /**
     * @brief Dibuixa la sprite de Mario segons el seu estat actual
     * 
     * @param window Finestra a la que pintar.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Dibuixa una barra per indicar quan resta del rush
     * 
     * @param window Finestra a la que pintar
     * @param cam Posició de la càmera
     */
    void paint_rush_bar(pro2::Window& window, pro2::Pt cam, int total_coffee);


    /**
     * @brief Actualitza l’estat de Mario al següent fotograma
     * 
     * @param window Finestra a la que pintar.
     * @param platforms Llista de plataformes
     * @param cafes Llista de cafès
     * @param total_coffee Comte de cafès recollits
     */
    void update(pro2::Window& window, const std::vector<Platform>& platforms, std::vector<Coffee>& cafes, int& total_coffee);

    /**
     * @brief Fa que Mario salti
     * 
     * @param mult Factor multiplicador del salt
     */
    void jump(float mult);

    /**
     * @brief Reinicia l’estat de rush
     */
    void reset_rush() {
        last_rush_ = 0;
        rush_ = false;
        rush_time_ = 0;
    }

    /**
     * @brief Retorna la posició actual
     * 
     * @return Punt amb la posició
     */
    pro2::Pt pos() const { return pos_; }

    /**
     * @brief Assigna una nova posició
     * 
     * @param new_pos Nova posició
     */
    void set_pos(pro2::Pt new_pos) { pos_ = new_pos; }

    /**
     * @brief Assigna la coordenada X
     * 
     * @param x Nova X
     */
    void set_x(int x) { pos_.x = x; }

    /**
     * @brief Assigna la coordenada Y
     * 
     * @param y Nova Y
     */
    void set_y(int y) { pos_.y = y; }

    /**
     * @brief Retorna si Mario està a terra
     * 
     * @return Cert si està a terra
     */
    bool is_grounded() const { return grounded_; }

    /**
     * @brief Assigna l’estat de contacte amb terra
     * 
     * @param grounded Nou estat
     */
    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) speed_.y = 0;
    }

    /**
     * @brief Alterna l’estat de grounded
     */
    void toggle_grounded() { set_grounded(!grounded_); }

    /**
     * @brief Retorna la posició original
     * 
     * @return Punt de posició inicial
     *
     * @note Aquesta funció també posa looking_left_ a false.
     */
    pro2::Pt get_original_pos() {
        looking_left_ = false;
        return original_pos_;
    }

    /**
     * @brief Retorna el rectangle de col·lisió de Mario
     * 
     * @return Rectangle de col·lisió
     */
    pro2::Rect get_hit_box() {
        return {pos_.x - 3, pos_.y - 17, pos_.x + 11, pos_.y + 1};
    }
};

#endif
