#ifndef SPRITES_HH
#define SPRITES_HH
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Sprites {
 public:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
    static const std::vector<std::vector<int>> mario_sprite_jump_;
    static const std::map<int, std::vector<std::vector<int>>> mario_sprites_run_;
    
    static const std::vector<std::vector<int>> luigi_sprite_normal_;
    static const std::vector<std::vector<int>> luigi_sprite_jump_;
    static const std::map<int, std::vector<std::vector<int>>> luigi_sprites_run_;

    static const std::map<int, std::vector<std::vector<int>>> coffe_sprites;

    static const std::map<char, std::vector<std::vector<int>>> diccionari;

    static const std::map<std::string, std::vector<std::vector<int>>> platform_textures;
};
#endif