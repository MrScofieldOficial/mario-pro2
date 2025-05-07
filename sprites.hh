#ifndef SPRITES_HH
#define SPRITES_HH

#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef vector<vector<int>> sprite;

class Sprites {
 public:
    /**
     * @brief Map que conté els sprites dels personatges (Mario i Luigi) en tots els seus estats
     */
    static const map<string, sprite> character_sprites;

    /**
     * @brief Map amb els 22 sprites del cafè per fer l'animació de gir
     */
    static const map<int, sprite> coffe_sprites;

    /**
     * @brief Map amb els sprites dels cartells
     */
    static const map<string, sprite> signs_sprites;

    /**
     * @brief Diccionari de caràcters (lletres, números, símbols) com a sprites
     */
    static const map<char, sprite> diccionari;

    /**
     * @brief Map amb textures de les plataformes
     */
    static const map<string, sprite> platform_textures;

    /**
     * @brief Map amb altres sprites (com blocs especials, decoracions, etc.)
     */
    static const map<string, sprite> blocs_especials;
};

#endif
