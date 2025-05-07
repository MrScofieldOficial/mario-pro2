#ifndef GEOMETRY_HH
#define GEOMETRY_HH

namespace pro2 {

/**
 * @brief Representa un punt en 2D amb coordenades enters.
 */
struct Pt {
    int x = 0;
    int y = 0;
};

/**
 * @brief Compara dos punts per poder-los usar com a clau en estructures ordenades.
 *
 * Primer compara la coordenada x. Si són iguals, compara la y.
 *
 * @param a Primer punt.
 * @param b Segon punt.
 * 
 * @return Cert si a < b segons l'ordre lexicogràfic.
 */
inline bool operator<(const Pt& a, const Pt& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

/**
 * @brief Multiplica un punt per un valor.
 *
 * @param p Punt a multiplicar.
 * @param factor Valor pel qual multiplicar.
 * 
 * @return Punt resultant.
 */
inline Pt operator*(const Pt& p, int factor) {
    return {p.x * factor, p.y * factor};
}

/**
 * @brief Multiplica un valor  per un punt.
 *
 * @param factor Valor pel qual multiplicar.
 * @param p Punt a multiplicar.
 * 
 * @return Punt resultant.
 */
inline Pt operator*(int factor, const Pt& p) {
    return p * factor;
}

/**
 * @brief Representa un rectangle mitjançant els seus límits.
 *
 * Els valors representen les vores: esquerra, superior, dreta i inferior.
 */
struct Rect {
    int left, top, right, bottom;
};

} 

#endif
