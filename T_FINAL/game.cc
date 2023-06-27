#include "classes/game.h"
#include "classes/controller.h"
#include <typeinfo>
#include <functional>

__BEGIN_API

Thread* Game::_window_thread;
Thread* Game::_keyboard_thread;
Thread* Game::_controller_thread;
Thread* Game::_player_thread;
Thread* Game::_collision_checker_thread;

CollisionChecker* Game::_collision_checker_obj;
Window* Game::_window_obj;
Keyboard* Game::_keyboard_obj;
Controller* Game::_controller_obj;
Player* Game::_player_obj;
std::list<Enemy*> Game::_enemy_objects;
std::list<Thread*> Game::_enemy_threads;

GameConfig* Game::_game_config;

Clock* Game::_clock_obj;
Game::Level Game::_level;

std::list<Bullet*> Game:: _player_bullet_list;
std::list<Bullet*> Game:: _enemies_bullet_list;


void Game::set_level(Level level) {_level = level;}
Game::Level Game::get_level() {
    return _level;
}

void Game::_configure(){
    _game_config = &GameConfig::get_instance();
    _game_config -> set_frame_limit(50);    
    _game_config -> set_key_repeat_enabled(true);
    _game_config -> set_video_size(std::make_tuple(1086, 746));
    _game_config -> set_window_title("Spaceships Game");
    _game_config -> set_sprites_scale(0.75);
    _game_config -> set_enemies_speed_lvl_1(50.f);
    _game_config -> set_enemies_speed_lvl_2(75.f);
    _game_config -> set_enemies_speed_lvl_3(100.f);
    _game_config -> set_screen_sprite_scale(2);
    _game_config -> set_start_panel(std::make_tuple(850, 100));
    _game_config -> set_player_speed(250.f);
    _game_config -> set_font_size(50);
    _game_config -> set_kills_to_lvl_2(4);
    _game_config -> set_kills_to_lvl_3(8);
    _game_config -> set_player_health(3);
    _game_config -> set_number_of_enemies(4);
    _game_config -> set_game_state(GameConfig::State::RUNNING);

    //TODO -> Aqui, inicializar as configurações utilizando os setters de GameConfig.
}



void Game::_enemy_run(int i) {
    map<Sprite::Orientation, string> sprites;
    sprites[Sprite::Orientation::RIGHT] = "src/images/space_ships/enemy_space_ship_right.png";
    sprites[Sprite::Orientation::LEFT] = "src/images/space_ships/enemy_space_ship_left.png";
    sprites[Sprite::Orientation::UP] = "src/images/space_ships/enemy_space_ship_up.png";
    sprites[Sprite::Orientation::DOWN] = "src/images/space_ships/enemy_space_ship_down.png";
    Enemy* new_enemy_obj;
    if (i == 0) {
        new_enemy_obj = new EnemyRandom(_game_config->get_sprites_scale(), 0, _game_config -> get_enemies_speed_lvl_1(), sprites, Sprite::Orientation::UP, _clock_obj, 100, 100, &_enemies_bullet_list, 1);
    } else if (i == 1) {
        // FIXME INSERIR AQUI O OUTRO TIPO DE INIMIGO
        new_enemy_obj = new EnemyTracker(_game_config->get_sprites_scale(), 0, _game_config -> get_enemies_speed_lvl_1(), sprites, Sprite::Orientation::UP, _clock_obj, 650, 100, &_enemies_bullet_list, _player_obj->get_sprite(), 2);
    } else if (i == 2) {
        new_enemy_obj = new EnemyRandom(_game_config->get_sprites_scale(), 0, _game_config -> get_enemies_speed_lvl_1(), sprites, Sprite::Orientation::UP, _clock_obj, 650, 650, &_enemies_bullet_list, 4);
    } else {
        new_enemy_obj = new EnemyTracker(_game_config->get_sprites_scale(), 0, _game_config -> get_enemies_speed_lvl_1(), sprites, Sprite::Orientation::UP, _clock_obj, 100, 650, &_enemies_bullet_list, _player_obj->get_sprite(), 3);
    }
    
    _enemy_objects.push_back(new_enemy_obj);
    new_enemy_obj -> run();
    delete new_enemy_obj;

    auto it = _enemy_threads.begin();
    std::advance(it, i);
    if (it != _enemy_threads.end()) {
        (*it) -> thread_exit(0);
    }
}

std::list<sf::Sprite*> Game::get_enemies_sprites_list() {
    std::list<sf::Sprite*> enemies_sprites_list;
    for (auto enemy : _enemy_objects) enemies_sprites_list.push_back(enemy -> get_sprite());
    return enemies_sprites_list;
}

void Game::_collision_checker_run() {
    std::list<sf::Sprite*> enemies_sprites_list = get_enemies_sprites_list();
    _collision_checker_obj = new CollisionChecker(_player_obj->get_sprite(), &enemies_sprites_list, &_player_bullet_list, &_enemies_bullet_list, _controller_obj->get_collision_queue());
    _collision_checker_obj -> run();
    delete _collision_checker_obj;
    _collision_checker_thread -> thread_exit(0);
}

void Game::_window_run() {
    std::list<sf::Sprite*> enemies_sprites_list = get_enemies_sprites_list();
    _window_obj = new Window(_player_obj, enemies_sprites_list, &_player_bullet_list, &_enemies_bullet_list, _clock_obj);
    _window_obj -> run();
    delete _window_obj;
    _window_thread -> thread_exit(0);
}

void Game::_keyboard_run() {
    _keyboard_obj = new Keyboard(_window_obj, _controller_obj);
    db<Game>(INF) << "[Game] Chamando método run do teclado!\n";
    _keyboard_obj -> run();
    delete _keyboard_obj;
    _keyboard_thread -> thread_exit(0);
}

void Game::_controller_run() {
    _controller_obj = new Controller(_player_thread, _enemy_threads, &_enemy_objects, _player_obj -> get_move_queue(), _player_obj, &_player_bullet_list, &_enemies_bullet_list, _collision_checker_thread, _window_thread);
    _controller_obj -> run();
    delete _controller_obj;
    _controller_thread -> thread_exit(0);
}

void Game::_player_run() {
    map<Sprite::Orientation, string> sprites;
    sprites[Sprite::Orientation::RIGHT] = "src/images/space_ships/space_ship_right.png";
    sprites[Sprite::Orientation::LEFT] = "src/images/space_ships/space_ship_left.png";
    sprites[Sprite::Orientation::UP] = "src/images/space_ships/space_ship_up.png";
    sprites[Sprite::Orientation::DOWN] = "src/images/space_ships/space_ship_down.png";
    _player_obj = new Player(
        _game_config -> get_player_health(),
        _game_config -> get_sprites_scale(),
        1,
        _game_config -> get_player_speed(),
        sprites, 
        Sprite::Orientation::UP,
        _clock_obj, 
        300, 
        300,
        &_player_bullet_list,
        0);
    // _player_obj = new Player(scale, size, speed, paths, sprites, clock);
    _player_obj -> run();
    delete _player_obj;
    _player_thread -> thread_exit(0);
}

void Game::run(void* name){
    _configure();
    //Instancia um clock
    _clock_obj = new Clock();

    // _window_thread = new Window(_window_run(_player_object, _enemy_object, ...))
    _player_thread = new Thread(_player_run);

    for (int i = 0; i < _game_config->get_number_of_enemies(); i++){
        _enemy_threads.push_back(new Thread(_enemy_run, i));
    }
    
    // db<Game>(INF) << "[Game] Iniciando a thread do collision checker\n";
    // _collision_checker_thread = new Thread(_collision_checker_run);

    _window_thread = new Thread(_window_run);

    _collision_checker_thread = new Thread(_collision_checker_run);

    _controller_thread = new Thread(_controller_run);

    _keyboard_thread = new Thread(_keyboard_run);

    _player_thread -> join();
    delete _player_thread;

    for (auto enemy_thread : _enemy_threads){
        enemy_thread -> join();
        delete enemy_thread;
    }
    _window_thread -> join();
    delete _window_thread;
    _collision_checker_thread -> join();
    delete _collision_checker_thread;
    _controller_thread -> join();
    delete _controller_thread;

    _keyboard_thread -> join();
    delete _keyboard_thread;
    // realizar chamada da Thread Player
}

Game::~Game() {
}

__END_API