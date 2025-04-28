#include "game.hh"
#include "utils.hh"
using namespace pro2;
const int k = 16;

Game::Game(int width, int height)
    : mario_({width / 2, 14 * k}, 0),
      luigi_({width / 2 - 3 * k, 14 * k}, 'W', 'A', 'D', 1),
      platforms_{
          Platform(9 * k, 27 * k, 18 * k, 19 * k),  Platform(0 * k, 18 * k, 22 * k, 23 * k),
          Platform(23 * k, 36 * k, 14 * k, 15 * k), Platform(5 * k, 24 * k, 9 * k, 10 * k),
          Platform(27 * k, 28 * k, 13 * k, 14 * k),
      },
      cafes_ {
        Coffee ({27 * k, 12 * k}), 
        Coffee({26 * k, 13 * k}),
      },
      finished_(false),
      paused_(false),
      following_(true),
      cooldown_keys_(0),
      total_coffees_(0) {
        for (int i = 1; i < 20; i++) {
            platforms_.push_back(Platform(23 * k + i * 18 * k, 36 * k + i * 18 * k, 14 * k, 15 * k));
            add_coffees(cafes_, 20 + 18 * i, 9, 5, -2, 5);
        }
        // for (int i = 0; i < 4; i++) {
        //     cafes_.push_back(Coffee({19 * k + i * k, 17 * k}));
        // }
        add_coffees(cafes_, 18 , 8, 5, 0, 5);
        add_coffees(cafes_, 21, 17, 4, 0, 4);
        


      }

//todo preguntar com funciona i si ho puc afegir o es massa avançat per pro2
void Game::add_coffees(std::vector<Coffee>& cafes_, int center_x, int center_y, int width, int height, int num) {
    center_x *= k;
    center_y *= k;
    width *= k;
    height *= k;
    for (int i = 0; i < num; ++i) {
        // Calculate the x position based on the number of coins
        float normalized_x = (i / (num - 1.0)) * 2.0 - 1.0;  // Normalize i to range [-1, 1]
        int x = center_x + (normalized_x * (width / 2));  // Spread coins over width
        
        // Calculate the y position to form the arch
        int y = center_y - (normalized_x * normalized_x * height);  // Arch height
        
        cafes_.push_back(Coffee({x, y}));
    }
}


void Game::reiniciar(pro2::Window& window) {
    const int width = window.width();
    const int height = window.height();
    mario_.set_pos(mario_.get_original_pos());
    luigi_.set_pos(luigi_.get_original_pos());
    paused_ = false;
    following_ = true;
    Pt pos = mario_.pos();
    pos.x -= window.width() / 2;
    pos.y -= window.height() / 2;
    window.set_camera_topleft(pos);

    for (Coffee& c : cafes_){
        c.colected = false;
    }
    total_coffees_ = 0;
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if (window.is_key_down('R') && cooldown_keys_ > 15) {
        cooldown_keys_ = 0;
        reiniciar(window);
    }
    if (window.is_key_down(80) && cooldown_keys_ > 15) {
        cooldown_keys_ = 0;
        paused_ = !paused_;  // toggle
    }
    ++cooldown_keys_;
    if (window.is_key_down(67) && cooldown_keys_ > 15) {
        cooldown_keys_ = 0;
        following_ = !following_;  // toggle
        Pt pos;
        if (following_) {
            pos = mario_.pos();
        } else {
            pos = luigi_.pos();
        }
        pos.x -= window.width() / 2;
        pos.y -= window.height() / 2;
        window.set_camera_topleft(pos);
    }
}

void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);
    luigi_.update(window, platforms_);
}

void Game::update_camera(pro2::Window& window) {
    Pt pos;
    if (following_) {
        pos = mario_.pos();
    } else {
        pos = luigi_.pos();
    }

    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = 0, dy = 0;
    if (pos.x > right) {
        dx = pos.x - right;
    } else if (pos.x < left) {
        dx = pos.x - left;
    }
    if (pos.y < top) {
        dy = pos.y - top;
    } else if (pos.y > bottom) {
        dy = pos.y - bottom;
    }

    //* Per mantenir el mario al centre de la pantalla
    // dx = pos.x - cam.x;
    // dy = pos.y - cam.y;

    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    if (!paused_) {
        update_objects(window);
        update_camera(window);
    }
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);

    const Pt  cam = window.camera_center();
    const int width = window.width();
    const int height = window.height();

    for (const Platform& p : platforms_) {
        p.paint(window);
    }
    
    for (Coffee& c : cafes_){
        c.update(window, mario_.pos(), luigi_.pos(), total_coffees_);
        if (!c.colected)
            c.paint(window);
    }
    mario_.paint(window);
    luigi_.paint(window);

    //* Pintar recuadre
    pro2::Color col;
    if (following_) {
        col = red;
    } else {
        col = green;
    }
    const int left = cam.x - width / 2;
    const int right = cam.x + width / 2;
    const int top = cam.y - height / 2;
    const int bottom = cam.y + height / 2;
    paint_hline(window, left, right, top, col);
    paint_hline(window, left, right, bottom - 1, col);
    paint_vline(window, left, top, bottom, col);
    paint_vline(window, right - 1, top, bottom, col);

    paint_num_of_coffee(window, total_coffees_, cam);

    //todo fer que la pantalla de pausa posi el joc més fosc (rectangle negre translucid) (no se com fer que sigui translucid)
    // if (paused_) {
    //     Rect pause = {left, top, right, bottom};
    //     paint_rect(window, pause, 0x47FFFF47);
    // }
}
