#include "sprites.hh"
#include <iostream>
#include <vector>
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x3b5998;
const int y = pro2::yellow;
const int f = pro2::black;
const int g = pro2::green;
const int h = 0x964807;
const int w = 1;

//* MARIO
const vector<vector<int>> Sprites::mario_sprite_normal_ = {
    {_, _, _, _, _, _, _, r, r, r, r, r, _, _, _, _, _},
    {_, _, _, _, _, _, r, r, r, r, r, r, r, r, r, _, _},
    {_, _, _, _, _, _, h, h, h, s, s, f, s, _, _, _, _},
    {_, _, _, _, _, h, s, h, s, s, s, f, s, s, s, _, _},
    {_, _, _, _, _, h, s, h, h, s, s, s, f, s, s, s, _},
    {_, _, _, _, _, h, h, s, s, s, s, f, f, f, f, _, _},
    {_, _, _, _, _, _, _, s, s, s, s, s, s, s, _, _, _},
    {_, _, _, _, _, _, r, r, b, r, r, r, _, _, _, _, _},
    {_, _, _, _, _, r, r, r, b, r, r, b, r, r, r, _, _},
    {_, _, _, _, r, r, r, r, b, b, b, b, r, r, r, r, _},
    {_, _, _, _, s, s, r, b, y, b, b, y, b, r, s, s, _},
    {_, _, _, _, s, s, s, b, b, b, b, b, b, s, s, s, _},
    {_, _, _, _, s, s, b, b, b, b, b, b, b, b, s, s, _},
    {_, _, _, _, _, _, b, b, b, _, _, b, b, b, _, _, _},
    {_, _, _, _, _, h, h, h, _, _, _, _, h, h, h, _, _},
    {_, _, _, _, h, h, h, h, _, _, _, _, h, h, h, h, _},
};

const vector<vector<int>> Sprites::mario_sprite_jump_ = {
    {_, _, _, _, _, _, _, _, _, _, _, _, _, s, s, s, _},
    {_, _, _, _, _, _, r, r, r, r, r, _, _, s, s, s, _},
    {_, _, _, _, _, r, r, r, r, r, r, r, r, r, s, s, _},
    {_, _, _, _, _, h, h, h, s, s, f, s, _, r, r, r, _},
    {_, _, _, _, h, s, h, s, s, s, f, s, s, s, r, r, _},
    {_, _, _, _, h, s, h, h, s, s, s, f, s, s, s, r, _},
    {_, _, _, _, h, h, s, s, s, s, f, f, f, f, r, _, _},
    {_, _, _, _, _, _, s, s, s, s, s, s, s, r, r, _, _},
    {_, _, r, r, r, r, r, b, r, r, r, b, r, r, _, _, _},
    {_, r, r, r, r, r, r, r, b, r, r, r, b, _, _, _, _},
    {s, s, r, r, _, r, r, r, b, b, b, b, y, b, _, _, h},
    {s, s, s, _, _, b, r, b, b, b, b, b, b, b, b, h, h},
    {_, s, _, h, _, b, b, b, b, y, b, b, b, b, b, h, h},
    {_, _, h, h, h, b, b, b, b, b, b, b, b, b, b, h, _},
    {_, h, h, h, b, b, b, b, b, b, b, b, b, _, _, _, _},
    {_, h, _, _, b, b, b, b, _, _, _, _, _, _, _, _, _},

};

const vector<vector<int>> Sprites::mario_sprite_run0_ = {
    {_, _, _, _, _, _, r, r, r, r, r, _, _, _, _, _, _},
    {_, _, _, _, _, r, r, r, r, r, r, r, r, r, _, _, _},
    {_, _, _, _, _, h, h, h, s, s, f, s, _, _, _, _, _},
    {_, _, _, _, h, s, h, s, s, s, f, s, s, s, _, _, _},
    {_, _, _, _, h, s, h, h, s, s, s, f, s, s, s, _, _},
    {_, _, _, _, h, h, s, s, s, s, f, f, f, f, _, _, _},
    {_, _, _, _, _, _, s, s, s, s, s, s, s, _, _, _, _},
    {_, _, _, r, r, r, r, b, r, r, r, b, _, _, _, _, _},
    {_, s, s, r, r, r, r, b, b, r, r, r, b, r, s, s, s},
    {_, s, s, s, _, r, r, b, b, b, b, b, b, r, r, s, s},
    {_, s, s, _, _, b, b, b, y, b, b, b, y, _, _, h, _},
    {_, _, _, _, b, b, b, b, b, b, b, b, b, b, h, h, _},
    {_, _, _, b, b, b, b, b, b, b, b, b, b, b, h, h, _},
    {_, _, h, h, b, b, b, _, _, _, b, b, b, b, h, h, _},
    {_, _, h, h, h, _, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, h, h, h, _, _, _, _, _, _, _, _, _, _, _},
};

const vector<vector<int>> Sprites::mario_sprite_run1_ = {
    {_, _, _, _, _, _, r, r, r, r, r, _, _, _, _, _, _},
    {_, _, _, _, _, r, r, r, r, r, r, r, r, r, _, _, _},
    {_, _, _, _, _, h, h, h, s, s, f, s, _, _, _, _, _},
    {_, _, _, _, h, s, h, s, s, s, f, s, s, s, _, _, _},
    {_, _, _, _, h, s, h, h, s, s, s, f, s, s, s, _, _},
    {_, _, _, _, h, h, s, s, s, s, f, f, f, f, _, _, _},
    {_, _, _, _, _, _, s, s, s, s, s, s, s, _, _, _, _},
    {_, _, _, _, _, _, _, r, r, b, b, r, _, _, _, _, _},
    {_, _, _, _, _, _, r, r, r, r, b, r, s, s, _, _, _},
    {_, _, _, _, s, s, r, r, r, r, r, r, s, s, s, _, _},
    {_, _, _, s, s, s, b, r, r, r, r, r, s, s, _, _, _},
    {_, _, _, _, h, h, b, b, b, b, b, b, b, _, _, _, _},
    {_, _, _, _, h, b, b, b, b, b, b, b, b, _, _, _, _},
    {_, _, _, h, h, b, b, _, _, b, b, b, _, _, _, _, _},
    {_, _, _, h, _, _, _, _, h, h, h, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, h, h, h, _, _, _, _, _},
};

const vector<vector<int>> Sprites::mario_sprite_run2_ = {
    {_, _, _, _, _, _, r, r, r, r, r, _, _, _, _, _, _},
    {_, _, _, _, _, r, r, r, r, r, r, r, r, r, _, _, _},
    {_, _, _, _, _, h, h, h, s, s, f, s, _, _, _, _, _},
    {_, _, _, _, h, s, h, s, s, s, f, s, s, s, _, _, _},
    {_, _, _, _, h, s, h, h, s, s, s, f, s, s, s, _, _},
    {_, _, _, _, h, h, s, s, s, s, f, f, f, f, _, _, _},
    {_, _, _, _, _, _, s, s, s, s, s, s, s, _, _, _, _},
    {_, _, _, _, _, r, r, r, b, r, r, _, _, _, _, _, _},
    {_, _, _, _, r, r, r, r, b, b, r, r, _, _, _, _, _},
    {_, _, _, _, r, r, r, b, b, y, b, b, _, _, _, _, _},
    {_, _, _, _, r, r, r, r, b, b, b, b, _, _, _, _, _},
    {_, _, _, _, b, r, r, s, s, b, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, r, s, s, b, b, _, _, _, _, _, _},
    {_, _, _, _, _, _, b, b, b, h, h, h, _, _, _, _, _},
    {_, _, _, _, _, _, h, h, h, h, _, _, _, _, _, _, _},
};

//* LUIGI
const vector<vector<int>> Sprites::luigi_sprite_normal_ = {
    {_, _, _, _, _, _, g, g, g, g, g, _, _, _, _, _, _},
    {_, _, _, _, _, g, g, g, g, g, g, g, g, g, _, _, _},
    {_, _, _, _, _, h, h, h, s, s, f, s, _, _, _, _, _},
    {_, _, _, _, h, s, h, s, s, s, f, s, s, s, _, _, _},
    {_, _, _, _, h, s, h, h, s, s, s, f, s, s, s, _, _},
    {_, _, _, _, h, h, s, s, s, s, f, f, f, f, _, _, _},
    {_, _, _, _, _, _, s, s, s, s, s, s, s, _, _, _, _},
    {_, _, _, _, _, g, g, b, g, g, g, _, _, _, _, _, _},
    {_, _, _, _, g, g, g, b, g, g, b, g, g, g, _, _, _},
    {_, _, _, g, g, g, g, b, b, b, b, g, g, g, g, _, _},
    {_, _, _, s, s, g, b, y, b, b, y, b, g, s, s, _, _},
    {_, _, _, s, s, s, b, b, b, b, b, b, s, s, s, _, _},
    {_, _, _, s, s, b, b, b, b, b, b, b, b, s, s, _, _},
    {_, _, _, _, _, b, b, b, _, _, b, b, b, _, _, _, _},
    {_, _, _, _, h, h, h, _, _, _, _, h, h, h, _, _, _},
    {_, _, _, h, h, h, h, _, _, _, _, h, h, h, h, _, _},
};

const vector<vector<int>> Sprites::luigi_sprite_jump_ = {
    {_, _, _, _, _, _, _, _, _, _, _, _, _, s, s, s, _},
    {_, _, _, _, _, _, g, g, g, g, g, _, _, s, s, s, _},
    {_, _, _, _, _, g, g, g, g, g, g, g, g, g, s, s, _},
    {_, _, _, _, _, h, h, h, s, s, f, s, _, g, g, g, _},
    {_, _, _, _, h, s, h, s, s, s, f, s, s, s, g, g, _},
    {_, _, _, _, h, s, h, h, s, s, s, f, s, s, s, g, _},
    {_, _, _, _, h, h, s, s, s, s, f, f, f, f, g, _, _},
    {_, _, _, _, _, _, s, s, s, s, s, s, s, g, g, _, _},
    {_, _, g, g, g, g, g, b, g, g, g, b, g, g, _, _, _},
    {_, g, g, g, g, g, g, g, b, g, g, g, b, _, _, _, _},
    {s, s, g, g, _, g, g, g, b, b, b, b, y, b, _, _, h},
    {s, s, s, _, _, b, g, b, b, b, b, b, b, b, b, h, h},
    {_, s, _, h, _, b, b, b, b, y, b, b, b, b, b, h, h},
    {_, _, h, h, h, b, b, b, b, b, b, b, b, b, b, h, _},
    {_, h, h, h, b, b, b, b, b, b, b, b, b, _, _, _, _},
    {_, h, _, _, b, b, b, b, _, _, _, _, _, _, _, _, _},
};

const vector<vector<int>> Sprites::luigi_sprite_run0_ = {
    {_, _, _, _, _, _, g, g, g, g, g, _, _, _, _, _, _},
    {_, _, _, _, _, g, g, g, g, g, g, g, g, g, _, _, _},
    {_, _, _, _, _, h, h, h, s, s, f, s, _, _, _, _, _},
    {_, _, _, _, h, s, h, s, s, s, f, s, s, s, _, _, _},
    {_, _, _, _, h, s, h, h, s, s, s, f, s, s, s, _, _},
    {_, _, _, _, h, h, s, s, s, s, f, f, f, f, _, _, _},
    {_, _, _, _, _, _, s, s, s, s, s, s, s, _, _, _, _},
    {_, _, _, g, g, g, g, b, g, g, g, b, _, _, _, _, _},
    {_, s, s, g, g, g, g, b, b, g, g, g, b, g, s, s, s},
    {_, s, s, s, _, g, g, b, b, b, b, b, b, g, g, s, s},
    {_, s, s, _, _, b, b, b, y, b, b, b, y, _, _, h, _},
    {_, _, _, _, b, b, b, b, b, b, b, b, b, b, h, h, _},
    {_, _, _, b, b, b, b, b, b, b, b, b, b, b, h, h, _},
    {_, _, h, h, b, b, b, _, _, _, b, b, b, b, h, h, _},
    {_, _, h, h, h, _, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, h, h, h, _, _, _, _, _, _, _, _, _, _, _},
};

const vector<vector<int>> Sprites::luigi_sprite_run1_ = {
    {_, _, _, _, _, _, g, g, g, g, g, _, _, _, _, _, _},
    {_, _, _, _, _, g, g, g, g, g, g, g, g, g, _, _, _},
    {_, _, _, _, _, h, h, h, s, s, f, s, _, _, _, _, _},
    {_, _, _, _, h, s, h, s, s, s, f, s, s, s, _, _, _},
    {_, _, _, _, h, s, h, h, s, s, s, f, s, s, s, _, _},
    {_, _, _, _, h, h, s, s, s, s, f, f, f, f, _, _, _},
    {_, _, _, _, _, _, s, s, s, s, s, s, s, _, _, _, _},
    {_, _, _, _, _, _, _, g, g, b, b, g, _, _, _, _, _},
    {_, _, _, _, _, _, g, g, g, g, b, g, s, s, _, _, _},
    {_, _, _, _, s, s, g, g, g, g, g, g, s, s, s, _, _},
    {_, _, _, s, s, s, b, g, g, g, g, g, s, s, _, _, _},
    {_, _, _, _, h, h, b, b, b, b, b, b, b, _, _, _, _},
    {_, _, _, _, h, b, b, b, b, b, b, b, b, _, _, _, _},
    {_, _, _, h, h, b, b, _, _, b, b, b, _, _, _, _, _},
    {_, _, _, h, _, _, _, _, h, h, h, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, h, h, h, _, _, _, _, _},
};

const vector<vector<int>> Sprites::luigi_sprite_run2_ = {
    {_, _, _, _, _, _, g, g, g, g, g, _, _, _, _, _, _},
    {_, _, _, _, _, g, g, g, g, g, g, g, g, g, _, _, _},
    {_, _, _, _, _, h, h, h, s, s, f, s, _, _, _, _, _},
    {_, _, _, _, h, s, h, s, s, s, f, s, s, s, _, _, _},
    {_, _, _, _, h, s, h, h, s, s, s, f, s, s, s, _, _},
    {_, _, _, _, h, h, s, s, s, s, f, f, f, f, _, _, _},
    {_, _, _, _, _, _, s, s, s, s, s, s, s, _, _, _, _},
    {_, _, _, _, _, g, g, g, b, g, g, _, _, _, _, _, _},
    {_, _, _, _, g, g, g, g, b, b, g, g, _, _, _, _, _},
    {_, _, _, _, g, g, g, b, b, y, b, b, _, _, _, _, _},
    {_, _, _, _, g, g, g, g, b, b, b, b, _, _, _, _, _},
    {_, _, _, _, b, g, g, s, s, b, b, b, _, _, _, _, _},
    {_, _, _, _, _, b, g, s, s, b, b, _, _, _, _, _, _},
    {_, _, _, _, _, _, b, b, b, h, h, h, _, _, _, _, _},
    {_, _, _, _, _, _, h, h, h, h, _, _, _, _, _, _, _},
};

//* LLETRES
const std::map<char, std::vector<std::vector<int>>> Sprites::diccionari = {
    {'1', {
        {_, _, w, w, _, _},
        {_, w, w, w, _, _},
        {_, _, w, w, _, _},
        {_, _, w, w, _, _},
        {_, _, w, w, _, _},
        {_, _, w, w, _, _},
        {w, w, w, w, w, w}}
    },
    {'2', {
        {_, w, w, w, w, w, _},
        {w, w, _, _, _, w, w},
        {_, _, _, _, w, w, w},
        {_, _, w, w, w, w, _},
        {_, w, w, w, w, _, _},
        {w, w, w, _, _, _, _},
        {w, w, w, w, w, w, w}}
    },
    {'3', {
        {w, w, w, w, w, w, w},
        {_, _, _, _, w, w, _},
        {_, _, _, w, w, _, _},
        {_, _, w, w, w, w, _},
        {_, _, _, _, _, w, w},
        {w, w, _, _, _, w, w},
        {_, w, w, w, w, w, _}}
    },
    {'4', {
        {_, _, _, w, w, w, _},
        {_, _, w, w, w, w, _},
        {_, w, w, _, w, w, _},
        {w, w, _, _, w, w, _},
        {w, w, w, w, w, w, w},
        {_, _, _, _, w, w, _},
        {_, _, _, _, w, w, _}}
    },
    {'5', {
        {w, w, w, w, w, w, _},
        {w, w, _, _, _, _, _},
        {w, w, w, w, w, w, _},
        {_, _, _, _, _, w, w},
        {_, _, _, _, _, w, w},
        {w, w, _, _, _, w, w},
        {_, w, w, w, w, w, _}}
    },
    {'6', {
        {_, _, w, w, w, w, w},
        {_, w, w, _, _, _, _},
        {w, w, _, _, _, _, _},
        {w, w, w, w, w, w, _},
        {w, w, _, _, _, w, w},
        {w, w, _, _, _, w, w},
        {_, w, w, w, w, w, _}}
    },
    {'7', {
        {w, w, w, w, w, w, w},
        {w, w, _, _, _, w, w},
        {_, _, _, _, w, w, _},
        {_, _, _, w, w, _, _},
        {_, _, w, w, _, _, _},
        {_, _, w, w, _, _, _},
        {_, _, w, w, _, _, _}}
    },
    {'8', {
        {_, w, w, w, w, w, _},
        {w, w, _, _, _, w, w},
        {w, w, _, _, _, w, w},
        {_, w, w, w, w, w, _},
        {w, w, _, _, _, w, w},
        {w, w, _, _, _, w, w},
        {_, w, w, w, w, w, _}}
    },
    {'9', {
        {_, w, w, w, w, w, _},
        {w, w, _, _, _, w, w},
        {w, w, _, _, _, w, w},
        {_, w, w, w, w, w, w},
        {_, _, _, _, _, w, w},
        {_, _, _, _, w, w, },
        {_, w, w, w, w, _, _}}
    },
    {'0', {
        {_, _, w, w, w, _, _},
        {_, w, _, _, w, w, _},
        {w, w, _, _, _, w, w},
        {w, w, _, _, _, w, w},
        {w, w, _, _, _, w, w},
        {_, w, w, _, _, w, _},
        {_, _, w, w, w, _, _}}
    },
    {'A', {
        {_, _, _, _, _, _, _},
        {_, _, _, _, _, _, _},
        {_, _, _, _, _, _, _},
        {_, _, _, _, _, _, _},
        {_, _, _, _, _, _, _},
        {_, _, _, _, _, _, _},
        {_, _, _, _, _, _, _}}
    },
};

//* PLATAFORMES