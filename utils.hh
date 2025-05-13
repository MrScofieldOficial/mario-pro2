#ifndef UTILS_HH
#define UTILS_HH

#include <vector>
#include "geometry.hh"
#include "window.hh"

namespace pro2 {

/**
 * @brief Dibuixa una línia horitzontal a la finestra.
 *
 * @param window Finestra on es dibuixa la línia.
 * @param xini Coordenada x inicial.
 * @param xfin Coordenada x final.
 * @param y Coordenada y.
 * @param color Color de la línia (valor per defecte: blanc).
 */
void paint_hline(pro2::Window& window, int xini, int xfin, int y, pro2::Color color = pro2::white);

/**
 * @brief Dibuixa una línia vertical a la finestra.
 *
 * @param window Finestra on es dibuixa la línia.
 * @param x Coordenada x.
 * @param yini Coordenada y inicial.
 * @param yfin Coordenada y final.
 * @param color Color de la línia (valor per defecte: blanc).
 */
void paint_vline(pro2::Window& window, int x, int yini, int yfin, pro2::Color color = pro2::white);

/**
 * @brief Dibuixa un rectangle a la finestra.
 *
 * @param window Finestra on es dibuixa el rectangle.
 * @param rect Rectangle a pintar.
 * @param color Color del contorn (valor per defecte: negre).
 */
void paint_rect(pro2::Window& window, pro2::Rect rect, pro2::Color color = pro2::black);

/**
 * @brief Dibuixa el marge d'un rectangle
 * 
 * @param window Finestra on es dibuixa el rectangle.
 * @param rect Rectangle per pintar el marge.
 * @param color Color del contorn (valor per defecte: blanc).
 */
void paint_rect_outline(pro2::Window& window, pro2::Rect rect, pro2::Color color = pro2::white);

/**
 * @brief Dibuixa una imatge/textura a la finestra a partir d'una posició.
 *
 * @param window Finestra a la que pintar.
 * @param orig Origen (cantonada superior esquerra) del rectangle que forma el sprite.
 * @param sprite Matriu de colors que representa la imatge (sprite).
 * @param mirror Si cal pintar la textura girada horitzontalment.
 */
void paint_sprite(pro2::Window&                        window,
                  pro2::Pt                             orig,
                  const std::vector<std::vector<int>>& sprite,
                  bool                                 mirror);

/**
 * @brief Comprova si dos rectangles es solapen.
 * 
 * @param rect1 Primer rectangle. 
 * @param rect2 Segon rectangle. 
 * 
 * @returns Cert si els rectangles es solapen.
 */
bool rects_overlap(const pro2::Rect& rect1, const pro2::Rect& rect2);

}  // namespace pro2

#endif
