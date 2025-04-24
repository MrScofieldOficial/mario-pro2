#include "game.hh"
#include "utils.hh"
using namespace pro2;

Game::Game(int width, int height)
    : mario_({width / 2, 150}),
      luigi_({width / 2 - 30, 150}, 'W', 'A', 'D'),
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
          Platform(50, 200, 150, 161),
      },
      finished_(false),
      paused_(false) {
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if (window.is_key_down(80) && !window.was_key_pressed(80)) {
        paused_ = !paused_; //toggle
    }
}

void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);
    luigi_.update(window, platforms_);
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 3;
    const int right = cam.x + window.width() / 3;
    const int top = cam.y - window.height() / 3;
    const int bottom = cam.y + window.height() / 3;

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

    const Pt cam = window.camera_center();

    Rect rect;
    rect.top = cam.y - 10;
    rect.right = cam.x + 10;
    rect.bottom = cam.y + 10;
    rect.left = cam.x - 10;
    //* Per fer que el rectangle faci pampallugues
    // if (window.frame_count() % 4 == 0)
       paint_rect(window, rect, yellow);
    

    for (const Platform& p : platforms_) {
        p.paint(window);
    }
    mario_.paint_mario(window);
    luigi_.paint_mario(window);

    const int left = cam.x - window.width() / 2;
    const int right = cam.x + window.width() / 2;
    const int top = cam.y - window.height() / 2;
    const int bottom = cam.y + window.height() / 2;

    const pro2::Color col = red;
    paint_hline(window, left, right, top, col);
    paint_hline(window, left, right, bottom - 1, col);
    paint_vline(window, left, top, bottom, col);
    paint_vline(window, right - 1, top, bottom, col);
}
