#ifndef GEOMETRY_HH
#define GEOMETRY_HH

namespace pro2 {

struct Pt {
    int x = 0, y = 0;
};

/**
 * @brief Compara dos punts del pla
 * 
 * La comparació és necessària per poder fer servir `Pt` com la clau d'un `map`.
 * La comparació utilitza primer la coordenada `x` (com si fos més "important"), 
 * i, quan les `x`s són iguals, la coordenada `y`.
 */
inline bool operator<(const Pt& a, const Pt& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

/**
 * @brief Multiplica un punt per un valor
 */
inline Pt operator*(const Pt& p, int factor) {
    return {p.x * factor, p.y * factor};
}

/**
 * @brief Multiplica un valor per un punt
 */
inline Pt operator*(int factor, const Pt& p) {
    return p * factor;
}


struct Rect {
    int left, top, right, bottom;
};

}

#endif