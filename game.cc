#include "game.hh"
#include "utils.hh"
using namespace pro2;

Game::Game(int width, int height)
    : mario_({width / 2, 150}, 0),
      luigi_({width / 2 - 30, 150}, 'W', 'A', 'D', 1),
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
          Platform(70, 220, 110, 121),
      },
      finished_(false),
      paused_(false),
      following_(true),
      cooldown_toggles_(0) {
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }
}

void Game::reiniciar(pro2::Window& window) {
    const int width = window.width();
    const int height = window.height();
    mario_.set_pos(mario_.get_original_pos());
    luigi_.set_pos(luigi_.get_original_pos());
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if (window.is_key_down('R')) {
        reiniciar(window);
    }
    if (window.is_key_down(80) && !window.was_key_pressed(80) && cooldown_toggles_ > 15) {
        cooldown_toggles_ = 0;
        paused_ = !paused_;  // toggle
    }

    ++cooldown_toggles_;
    if (window.is_key_down(67) && !window.was_key_pressed(67) && cooldown_toggles_ > 15) {
        cooldown_toggles_ = 0;
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
}
