#include <vector>
#include "game.hh"
#include "window.hh"

using namespace std;

const int WIDTH = 480, HEIGHT = 320;
const int ZOOM = 3;
const int FPS = 48;

// bool inciar_partida(pro2::Window window) {
//     Game game(WIDTH, HEIGHT);

//     while (window.next_frame() && !game.is_finished() && !game.is_restared()) {
//         game.update(window);
//         game.paint(window);
//     }
//     std::cout << "Is restarted?: " << (game.is_restared() ? "yes" : "no") << std::endl;
//     return game.is_restared();
// }

int main() {
    pro2::Window window("Mario & Luigi tornada a la uni", WIDTH, HEIGHT, ZOOM);
    window.set_fps(FPS);

    Game game(WIDTH, HEIGHT);
    while (window.next_frame() && !game.is_finished()) {
        //  && !game.is_restared()
        game.update(window);
        game.paint(window);
    }

    // if (inciar_partida(window)) {
    //     inciar_partida(window);
    // }
}