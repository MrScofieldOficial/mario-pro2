#ifndef SPRITES_HH
#define SPRITES_HH
#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef vector<vector<int>> sprite;


class Sprites {
 public:
    static const map<string, sprite> character_sprites;

    static const map<int, sprite> coffe_sprites;

    static const map<string, sprite> signs_sprites;

    static const map<char, sprite> diccionari;

    static const map<string, sprite> platform_textures;

    static const map<string, sprite> blocs_especials;
};
#endif