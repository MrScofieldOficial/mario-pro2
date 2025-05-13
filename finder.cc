#include "finder.hh"

using namespace pro2;
using namespace std;

#include "platform.hh"
template class Finder<Platform>;
#include "coffee.hh"
template class Finder<Coffee>;

template <typename T>
void Finder<T>::add(T *t) {
    Rect rect = t->get_rect();
    obj_rect_map_[t] = rect;
    
    // Afegir al mapa de coordenades X
    x_start_map_[rect.right].insert(t);
}

template <typename T>
void Finder<T>::remove(T *t) {
    // Si existeix
    auto it = obj_rect_map_.find(t);
    if (it != obj_rect_map_.end()) {
        Rect rect = it->second;
        // Elimina l'objecte del mapa de coordenades X
        x_start_map_[rect.right].erase(t);
        if (x_start_map_[rect.right].empty()) {
            x_start_map_.erase(rect.right);
        }
        
        // Elimina del mapa de rectangles
        obj_rect_map_.erase(t);
    }
}

template <typename T>
void Finder<T>::update(T *t) {
    remove(t);
    add(t);
}

template <typename T>
set<T*> Finder<T>::query(Rect rect) {
    set<T*> result;
    
    auto it = x_start_map_.lower_bound(rect.left);
    bool inside = true;
    while (it != x_start_map_.end() && inside) {
        for (T* obj : it->second) {
            Rect& obj_rect = obj_rect_map_.at(obj);
            inside = (obj_rect.left <= rect.right);
            // Comprovo si esta dins
            if (inside &&
                (obj_rect.left <= rect.right || obj_rect.right >= rect.left) &&
                (obj_rect.top <= rect.bottom || obj_rect.bottom >= rect.top)) {
                
                result.insert(obj);
            }
        }
        ++it;
    }

    return result;
}

/*


*/