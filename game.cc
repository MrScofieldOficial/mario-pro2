#include <random>
#include <cmath>
#include "game.hh"
#include "utils.hh"
#include "sprites.hh"
using namespace pro2;
const int k = 16;

Game::Game(int width, int height)
    : mario_({3 * k, 20 * k}, 0),
      luigi_({3 * k, 16 * k}, 'W', 'A', 'D', 1),
      finished_(false),
      paused_(false),
      following_(true),
      cooldown_keys_(0),
      total_coffees_(0),
      win_condition_(false),
      game_over_(false),
      in_stop_(false),
      stop_id_(0),
      mario_in_stop_(false),
      luigi_in_stop_(false),
      bus_pos_({0, 0}),
      teleport(false),
      bus_moving_(false)
{
    init_platforms();
    init_coffees();
    init_clouds();
    busos_ = {
        Bus({15, 15}, "2", "0", k),
        Bus({28, -3}, "2", "1", k),
        Bus({9, 7}, "7", "0", k),
        Bus({351, 13}, "7", "1", k),
    };

    // Afegir totes les plataformes al finder
    for (Platform& platform : platforms_) {
        platform_finder_.add(&platform);
    }
    
    // Afegir tots els cafes al finder
    for (Coffee& coffee : cafes_) {
        coffee_finder_.add(&coffee);
    }
}

void Game::init_platforms() {
    platforms_ = {
        Platform(-1, 0, 0, 23, "cracked", k), Platform(0, 30, 20, 23, "cracked", k),
        Platform(0, 6, 16, 17, "cloud", k),   Platform(13, 27, 17, 18, "brick", k),
        Platform(23, 36, 14, 15, "brick", k), Platform(5, 24, 9, 10, "brick", k),
        Platform(27, 12, "cloud", k),         Platform(17, 19, 4, 5, "brick", k),
        Platform(20, 35, 1, 2, "cloud", k),   Platform(22, 33, 0, 1, "cloud", k),
        Platform(28, 32, -1, 0, "cloud", k),  Platform(24, 26, -1, 0, "cloud", k)
    };
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(23 + i * 17, 36 + i * 17, 14 + (i % 2), 15 + (i % 2), "brick", k));
    }
}

void Game::init_coffees() {
    cafes_ = {
        Coffee({27 * k, 11 * k}, 0),
        Coffee({26 * k, 13 * k}, 4),
    };
    for (int i = 1; i < 20; i++) {
        add_coffees(cafes_, {20 + 17 * i, 10}, 5, -2);
    }
    add_coffees(cafes_, {18 , 8}, 5, 0, 5);
    add_coffees(cafes_, {21, 16}, 4, 0, 4);
}


void Game::init_clouds() {
    clouds_ = {
        Cloud({21 * k, 12 * k}, 0), Cloud({24 * k, 7 * k}, 1),
    };
    add_clouds(3*k, -10*k, 400*k, 10*k, 500, 150);
}

// Afegeix cafes en paràbola o linia recta de manera senzilla
// En linia millor que num = width - 1 i en paràbola num = 5
void Game::add_coffees(std::vector<Coffee>& cafes_, pro2::Pt center, int width, int height, int num) {
    center.x *= k;
    center.y *= k;
    width *= k;
    height *= k;
    for (int i = 0; i < num; ++i) {
        float normalized_x = (i / (num - 1.0)) * 2.0 - 1.0;  // Normalitza la x del cafe dins l'interval [-1, 1]
        int x = center.x + (normalized_x * (width / 2));  // Calcula la x del cafe proporcional a la seva posició normalitzada
        int y = center.y - (normalized_x * normalized_x * height);  // Calcula la imatge de f(x) = height * x^2
        cafes_.push_back(Coffee({x, y}, i % (num * 2 )));
    }
}

bool Game::is_far_enough(const pro2::Pt& p, int min_dist) {
    for (const Cloud& c : clouds_) {
        pro2::Pt dist = p - c.pos();
        if (dist.x * dist.x + dist.y * dist.y < min_dist * min_dist) {
            return false;
        }
    }
    return true;
}

// Afegeix nuvols al fons
void Game::add_clouds(int left, int top, int right, int bottom, int num_clouds, int min_dist) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(left, right);
    std::uniform_int_distribution<> dis_y(top, bottom);

    int attempts = 0;
    const int max_attempts = 1000;
    while (clouds_.size() < num_clouds && attempts < max_attempts) {
        pro2::Pt candidate = {dis_x(gen), dis_y(gen)};
        if (is_far_enough(candidate, min_dist)) {
            clouds_.push_back(Cloud(candidate, attempts % 2));
        }
        attempts++;
    }
}

void Game::centrar_camera (pro2::Pt character_pos, pro2::Window& window) {
    character_pos.x -= window.width() / 2;
    character_pos.y -= window.height() / 2;
    window.set_camera_topleft(character_pos);
    pro2::Pt cam = window.camera_center();
    if (cam.y + window.height() / 2 > 22.5 * k) {
        window.set_camera_topleft({cam.x - window.width() / 2, int(22.5 * k) - window.height()});
    }
    if (cam.x - window.width() / 2 < 0) {
        window.set_camera_topleft({0, cam.y - window.height() / 2});
    }
}

// Torna a l'estat inicial
void Game::reiniciar(pro2::Window& window) {
    const int width = window.width();
    const int height = window.height();
    mario_.set_pos(mario_.get_original_pos());
    luigi_.set_pos(luigi_.get_original_pos());
    mario_.reset_rush();
    luigi_.reset_rush();
    mario_.not_wait();
    luigi_.not_wait();
    paused_ = false;
    following_ = true;
    centrar_camera(mario_.pos(), window);

    for (Coffee& c : cafes_) {
        c.set_colect(false);
    }
    total_coffees_ = 0;
    game_over_ = false;

    for (Cloud& c : clouds_) {
        c.reset_pos();
    }
}

// Llegeix les inputs dels jugadors
void Game::process_keys(pro2::Window& window) {
    ++cooldown_keys_;
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if (window.is_key_down('R') && cooldown_keys_ > 15) {
        cooldown_keys_ = 0;
        reiniciar(window);
    }
    if (window.is_key_down(' ') && cooldown_keys_ > 10) {
        cooldown_keys_ = 0;
        if (in_stop_ && !(mario_.get_wait() || luigi_.get_wait())) {
            bus_moving_ = true;
            int current_id = stop_id_ % 10, current_stop_num = stop_id_ / 10;
            int i = 0;
            while (i < busos_.size()) {
                if (busos_[i].get_num() == current_stop_num && busos_[i].get_id() != current_id) {
                    stop_pos_ = busos_[i].get_pos();
                }
                i++;
            }
            if (mario_in_stop_) {
                mario_.wait();
            }
            if (luigi_in_stop_) {
                luigi_.wait();
            }
            // win_condition_ = !win_condition_;  // toggle
            // paused_ = !paused_;  // toggle
        } 
    }
    if (window.is_key_down('P') && cooldown_keys_ > 15) {
        cooldown_keys_ = 0;
        paused_ = !paused_;  // toggle
    }
    if (window.is_key_down('C') && cooldown_keys_ > 15) {
        cooldown_keys_ = 0;
        following_ = !following_;  // toggle
        if (following_) {
            centrar_camera(mario_.pos(), window);
        } else {
            centrar_camera(luigi_.pos(), window);
        }
    }
}

// Actualitza tots els objectes
void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_, cafes_, total_coffees_);
    luigi_.update(window, platforms_, cafes_, total_coffees_);
    if ((mario_.pos().y > 25 * k) || luigi_.pos().y > 25 * k) {
        game_over_ = true;
    }

    Pt camera_center = window.camera_center();
    Rect visible_area = {
        camera_center.x - window.width() / 2,  // left
        camera_center.y - window.height() / 2, // top
        camera_center.x + window.width() / 2,  // right
        camera_center.y + window.height() / 2  // bottom
    };

    visible_platforms_ = platform_finder_.query(visible_area);
    visible_coffee_ = coffee_finder_.query(visible_area);

    // Check Coffee interactions
    pro2::Rect mario_hit_box = mario_.get_hit_box(), luigi_hit_box = luigi_.get_hit_box();
    for (Coffee* coffee : visible_coffee_) {
        if (!coffee->is_colected()) {
            coffee->set_colect(coffee->can_collect_coffee(mario_hit_box, luigi_hit_box), total_coffees_);
        }
    }
    int temp_id = 0;
    bool temp_in = false;
    for (Bus& b : busos_) {
        temp_id = b.update(mario_.get_hit_box());
        if (temp_id != 0) {
            stop_id_ = temp_id;
            temp_in = true;
            mario_in_stop_ = true;
            bus_pos_.y = b.get_pos().y + 9;

        }
        temp_id = b.update(luigi_.get_hit_box());
        if (temp_id != 0) {
            stop_id_ = temp_id;
            temp_in = true;
            luigi_in_stop_ = true;
            bus_pos_.y = b.get_pos().y + 9;
        }
    }
    in_stop_ = temp_in;
    if (!in_stop_) {
        stop_id_ = 0;
        mario_in_stop_ = false;
        luigi_in_stop_ = false;
        bus_moving_ = false;
    }    
    if (bus_moving_ && !teleport) {
        if (mario_in_stop_ && bus_pos_.x + 10 >= mario_.pos().x) {
            mario_.set_pos({stop_pos_.x + k, stop_pos_.y + 2*k});
            if (following_) centrar_camera(mario_.pos(), window);
            bus_pos_.x = mario_.pos().x - 50;
            teleport = true;
        }
        if (luigi_in_stop_ && bus_pos_.x + 10 >= luigi_.pos().x) {
            luigi_.set_pos({stop_pos_.x + k, stop_pos_.y + 2*k});
            if (!following_) centrar_camera(luigi_.pos(), window);
            bus_pos_.x = luigi_.pos().x - 50;
            teleport = true;
        }

    }
    if ((mario_in_stop_ && !mario_.get_wait()) || (luigi_in_stop_ && !luigi_.get_wait())) {
        bus_moving_ = false;
    }


    // Update clouds pos for paralax effect
    for (Cloud& c : clouds_) {
        c.update(window, window.camera_center());
    }
}

// Actualitza la posició de la càmera
void Game::update_camera(pro2::Window& window) {
    Pt pos;
    if (following_) {
        pos = mario_.pos();
    } else {
        pos = luigi_.pos();
    }

    const Pt cam = window.camera_center();
    const int left = cam.x - window.width() / 4.5;
    const int right = cam.x + window.width() / 4.5;
    const int bottom = cam.y + window.height() / 4.5;
    const int top = cam.y - window.height() / 5.5;

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

    if (cam.y + window.height() / 2 > 22.5 * k) {
        dy = 0;
        window.set_camera_topleft({cam.x - window.width() / 2, int(22.5 * k) - window.height()});
    }
    if (cam.x - window.width() / 2 < 0) {
        dx = 0;
        window.set_camera_topleft({0, cam.y - window.height() / 2});
    }

    window.move_camera({dx, dy});
}

// Actualitza el estat del joc
void Game::update(pro2::Window& window) {
    process_keys(window);
    if (!paused_) {
        update_camera(window);
        update_objects(window);
    }
}

// Dibuixa a la pantalla
void Game::paint(pro2::Window& window) {
    // Cel
    window.clear(sky_blue);

    //Núvols
    for (const Cloud& c : clouds_) {
        c.paint(window);
    }

    // No interactuables / fons
    paint_sprite(window, {9 * k, 18 * k}, Sprites::signs_sprites.at("right_arrow"), false);
    paint_sprite(window, {31 * k, 12 * k}, Sprites::signs_sprites.at("left_arrow"), false);

    // Plataformes
    for (const Platform* p : visible_platforms_) {
        p->paint(window);
    }

    // Parades de bus
    for (const Bus& b : busos_) {
        b.paint(window);
    }

    // Cafes
    for (Coffee* c : visible_coffee_){
        if (!c->is_colected()) {
            c->paint(window);
        }
    }



    // Personatges i enemics
    mario_.paint(window);
    luigi_.paint(window);

    // Bus
    const Pt  cam = window.camera_center();
    int sprite_width = Sprites::bus.at("bus")[0].size();
    if (bus_moving_) {
        bus_pos_.x += 7;
    } else {
        bus_pos_.x = cam.x - window.width()/2 - sprite_width;
        teleport = false;
    }
    paint_sprite(window, bus_pos_, Sprites::bus.at("bus"), false);
    


    // Recuadre
    pro2::Color col;
    if (following_) {
        col = red;
    } else {
        col = green;
    }
    const int width = window.width();
    const int height = window.height();
    const int left = cam.x - width / 2;
    const int right = cam.x + width / 2;
    const int top = cam.y - height / 2;
    const int bottom = cam.y + height / 2;

    paint_hline(window, left, right, top, col);
    paint_hline(window, left, right, top + 1, col);
    paint_hline(window, left, right, bottom - 1, col);
    paint_hline(window, left, right, bottom - 2, col);
    paint_vline(window, left, top, bottom, col);
    paint_vline(window, left + 1, top, bottom, col);
    paint_vline(window, right - 1, top, bottom, col);
    paint_vline(window, right - 2, top, bottom, col);

    // Comptador de cafes
    paint_num_of_coffee(window, total_coffees_, cam);

    // Rush restant
    mario_.paint_rush_bar(window, cam, total_coffees_);

    // Instruccions per les parades de bus
    if (in_stop_ && !(mario_.get_wait() || luigi_.get_wait())) {
        pro2::Rect rect = {cam.x - 150, cam.y + 126, cam.x + 150, cam.y + 142};
        paint_rect(window, rect, 0xb7aa00);
        paint_rect_outline(window, rect, 0xf7ea40);
        blinking_text(window, cam, "PITJA ESPAI PER CANVIAR DE PARADA");
    }

    // Pantalla de pausa
    if (paused_ && !win_condition_) {
        paint_pause_screen(window, cam);
    }
    // Pantalla de joc perdut
    if (game_over_) {
        paused_ = true;
        paint_game_over_screen(window, cam);
    }
    // Pantalla de joc guanyat
    if (win_condition_) {
        paused_ = true;
        paint_win_screen(window, cam);
    }
}