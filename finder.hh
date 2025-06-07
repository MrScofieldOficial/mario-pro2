#ifndef FINDER_HH
#define FINDER_HH

#include "geometry.hh"
#include "platform.hh"
#include "coffee.hh"
#include <set>
#include <map>

using namespace std;
using namespace pro2;

template <typename T>
class Finder {
private:
    // Mapa que, donat el top-left d'un quadrat, retorna els objectes que hi ha dins
    map<Pt, set<T*>> obj_map_;

    // Mida dels quadrats que conformen el món
    int n_const_ = 50;

public:
    Finder() {}

    set<Pt> find_squares(T* t);
    void add(T* t);
    void remove(T* t);
    void update(T* t);

    /**
    * @brief Retorna el conjunt d'objectes amb rectangles 
    *        total o parcialment dins de 'rect'.
    *
    * @param rect El rectangle de cerca
    *
    * @returns Un conjunt de punters a objectes que tenen un 
    *          rectangle parcial o totalment dins de 'rect'
    */
    set<T*> query(Rect rect);
};

template <typename T>
set<Pt> Finder<T>::find_squares(T* t) {
    set<Pt> rects_inside;

    Rect obj_hitbox = t->get_rect();
    int left = obj_hitbox.left;
    int right = obj_hitbox.right;
    int top = obj_hitbox.top;
    int bottom = obj_hitbox.bottom;

    Pt top_left = {left - (left % n_const_), top - (top % n_const_)};
    Pt bottom_right = {right - (right % n_const_), bottom - (bottom % n_const_)};

    for (int i = top_left.x; i <= bottom_right.x; i += n_const_) {
        for (int j = top_left.y; j <= bottom_right.y; j += n_const_) {
            rects_inside.insert({i, j});
        }
    }

    return rects_inside;
}

template <typename T>
void Finder<T>::add(T* t) {
    set<Pt> rects_in = find_squares(t);

    for (const Pt& pt : rects_in) {
        obj_map_[pt].insert(t);
    }
}

template <typename T>
void Finder<T>::remove(T* t) {
    set<Pt> rects_in = find_squares(t);

    for (Pt& pt : rects_in) {
        auto it = obj_map_.find(pt);
        if (it != obj_map_.end()) {
            it->second.erase(t);
            if (it->second.empty()) {
                obj_map_.erase(it);
            }
        }
    }
}

template <typename T>
void Finder<T>::update(T* t) {
    remove(t);
    add(t);
}

template <typename T>
set<T*> Finder<T>::query(Rect rect) {
    set<T*> result;

    Pt top_left = {rect.left - (rect.left % n_const_), rect.top - (rect.top % n_const_)};
    Pt bottom_right = {rect.right - (rect.right % n_const_), rect.bottom - (rect.bottom % n_const_)};

    for (int i = top_left.x; i <= bottom_right.x; i += n_const_) {
        for (int j = top_left.y; j <= bottom_right.y; j += n_const_) {
            auto it = obj_map_.find({i, j});
            if (it != obj_map_.end()) {
                for (T* obj : it->second) {
                    Rect obj_rect = obj->get_rect();
                    if (obj_rect.left <= rect.right && obj_rect.right >= rect.left &&
                        obj_rect.top <= rect.bottom && obj_rect.bottom >= rect.top) {
                        result.insert(obj);
                    }
                }
            }
        }
    }

    return result;
}

#endif // FINDER_HH
