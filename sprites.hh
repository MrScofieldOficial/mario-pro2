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
    static const std::vector<std::vector<int>> mario_sprite_run0_;
    static const std::vector<std::vector<int>> mario_sprite_run1_;
    static const std::vector<std::vector<int>> mario_sprite_run2_;

    static const std::vector<std::vector<int>> luigi_sprite_normal_;
    static const std::vector<std::vector<int>> luigi_sprite_jump_;
    static const std::vector<std::vector<int>> luigi_sprite_run0_;
    static const std::vector<std::vector<int>> luigi_sprite_run1_;
    static const std::vector<std::vector<int>> luigi_sprite_run2_;

    static const std::map<char, std::vector<std::vector<int>>> diccionari;
};
#endif