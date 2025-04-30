#ifndef SPRITES_HH
#define SPRITES_HH
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Sprites {
 public:

     static const std::map<std::string, std::vector<std::vector<int>>> character_sprites;

    static const std::map<int, std::vector<std::vector<int>>> coffe_sprites;

    static const std::map<std::string, std::vector<std::vector<int>>> signs_sprites;

    static const std::map<char, std::vector<std::vector<int>>> diccionari;

    static const std::map<std::string, std::vector<std::vector<int>>> platform_textures;

    static const std::map<std::string, std::vector<std::vector<int>>> blocs_especials;
};
#endif