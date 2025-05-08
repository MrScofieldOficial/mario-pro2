#ifndef PLATFORM_HH
#define PLATFORM_HH

#include <vector>
#include "window.hh"

class Platform {
 private:
    int left_;
    int right_;
    int top_;
    int bottom_;
    std::string id_;

 public:
    /**
     * @brief Constructor per defecte (plataforma tipus "brick").
     */
    Platform() : left_(0), right_(0), top_(0), bottom_(0), id_("brick") {}

    /**
     * @brief Constructor de còpia.
     *
     * @param other Plataforma a copiar.
     */
    Platform(const Platform& other)
        : left_(other.left_), right_(other.right_), top_(other.top_), bottom_(other.bottom_), id_(other.id_) {}

    /**
     * @brief Constructor amb valors personalitzats.
     *
     * @param left Coordenada esquerra (en unitats abans d'escalar).
     * @param right Coordenada dreta (en unitats abans d'escalar).
     * @param top Coordenada superior (en unitats abans d'escalar).
     * @param bottom Coordenada inferior (en unitats abans d'escalar).
     * @param id Identificador del tipus de plataforma (textura).
     * @param k Factor d’escala (habitualment la mida d’un tile).
     */
    Platform(int left, int right, int top, int bottom, std::string id, int k)
        : left_(left * k), right_(right * k - 1), top_(top * k), bottom_(bottom * k), id_(id) {}

    /**
     * @brief Constructor amb valors personalitzats a partir d'un punt.
     *
     * @param left Coordenada esquerra (en unitats abans d'escalar).
     * @param top Coordenada superior (en unitats abans d'escalar).
     * @param id Identificador del tipus de plataforma (textura).
     * @param k Factor d’escala (habitualment la mida d’un tile).
     */
    Platform(int left, int top, std::string id, int k)
        : left_(left * k), right_((left + 1) * k - 1), top_(top * k), bottom_((top + 1) * k), id_(id) {}

    /**
     * @brief Dibuixa la plataforma sencera.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Comprova si s’ha travessat la plataforma cap avall.
     */
    bool has_crossed_floor_downwards(pro2::Pt plast, pro2::Pt pcurr) const;

    /**
     * @brief Comprova si s’ha travessat la plataforma cap amunt.
     */
    bool has_crossed_floor_upwards(pro2::Pt plast, pro2::Pt pcurr) const;

    /**
     * @brief Comprova si s’ha travessat la paret dreta de la plataforma.
     */
    bool has_crossed_right(pro2::Pt plast, pro2::Pt pcurr) const;

    /**
     * @brief Comprova si s’ha travessat la paret esquerra de la plataforma.
     */
    bool has_crossed_left(pro2::Pt plast, pro2::Pt pcurr) const;

    /**
     * @brief Comprova si un punt es troba dins la plataforma.
     */
    bool is_pt_inside(pro2::Pt pt) const;

    /**
     * @brief Retorna la coordenada superior de la plataforma.
     */
    int top() const { return top_; }

    /**
     * @brief Retorna la coordenada inferior de la plataforma.
     */
    int bottom() const { return bottom_; }

    /**
     * @brief Retorna la coordenada dreta de la plataforma.
     */
    int right() const { return right_; }

    /**
     * @brief Retorna la coordenada esquerra de la plataforma.
     */
    int left() const { return left_; }

    /**
     * @brief Retorna id de la plataforma.
     */
    std::string id() const { return id_; }

    /**
     * @brief Retorna el rectangle que representa la plataforma.
     */
    pro2::Rect get_rect() const {
        return {left_, top_, right_, bottom_};
    }
};

#endif
