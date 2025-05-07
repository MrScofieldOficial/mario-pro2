#ifndef UI_HH
#define UI_HH

#include "window.hh"

/**
 * @brief Pinta el comptador de cafès recollits a la cantonada superior dreta de la pantalla.
 * 
 * @param window Finestra on es pinta.
 * @param counter Nombre total de cafès recollits.
 * @param cam Posició central de la càmera.
 */
void paint_num_of_coffee(pro2::Window& window, int counter, pro2::Pt cam);

/**
 * @brief Pinta la pantalla de pausa amb un fons semiopac i el text "JOC PAUSAT".
 * 
 * @param window Finestra on es pinta.
 * @param cam Posició central de la càmera.
 */
void paint_pause_screen(pro2::Window& window, pro2::Pt cam);

/**
 * @brief Pinta la pantalla de victòria amb un fons negre i el missatge "HAS GUANYAT!".
 * 
 * @param window Finestra on es pinta.
 * @param cam Posició central de la càmera.
 */
void paint_win_screen(pro2::Window& window, pro2::Pt cam);

/**
 * @brief Pinta la pantalla de derrota amb un fons vermell i el missatge "HAS PERDUT".
 * 
 * @param window Finestra on es pinta.
 * @param cam Posició central de la càmera.
 */
void paint_game_over_screen(pro2::Window& window, pro2::Pt cam);

/**
 * @brief Pinta un missatge centrat a la part inferior de la pantalla, que parpelleja.
 * 
 * @param window Finestra on es pinta.
 * @param cam Posició central de la càmera.
 * @param s Missatge a mostrar (p. ex. "PITJA 'R' PER REINICIAR").
 */
void restart_info(pro2::Window& window, pro2::Pt cam, std::string s);

#endif // UI_HH
