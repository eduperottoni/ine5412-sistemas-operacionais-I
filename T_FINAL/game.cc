#include "classes/game.h"
#include <typeinfo>
#include <functional>

__BEGIN_API

Thread* Game::_window_thread;
Window* Game::_window_obj;
Thread* Game::_keyboard_thread;
Keyboard* Game::_keyboard_obj;
Thread* Game::_controller_thread;
Controller* Game::_controller_obj;
Player* Game::_player_obj;
Thread* Game::_player_thread;
std::list<Enemy*> Game::_enemy_objects;
std::list<Thread*> Game::_enemy_threads;
StaticSprite* Game::_screen;

GameConfig* Game::_game_config;

Clock* Game::_clock_obj;

int NUMBER_OF_ENEMIES = 4;
float SCALE = 0.75;
float ENEMIES_SPEED = 100.f;
float SCREEN_SCALE = 1.5f;

void Game::configure(){
    _game_config = &GameConfig::get_instance();

    //TODO -> Aqui, inicializar as configurações utilizando os setters de GameConfig.
}

// void Game::_enemy_run() {
    

//     for (int i = 0; i < NUMBER_OF_ENEMIES; i++){
//         if (i % 2 == 0){
//             db<Game>(INF) << "[Game] Instanciando um novo enemy set path !\n";
            

//         } else {
//             // _enemy_obj = new Enemy(sprites, MovingSprite::Orientation::UP, _clock_obj);
//             db<Game>(INF) << "[Game] Chamando método run do player!\n";
//             // // _enemy_obj -> run();
//         }

//     }

//     for (auto enemy_object : _enemy_objects){
//         _enemy_threads.push_back(new Thread(&Enemy::run, enemy_object));
//     }
// }


void Game::_enemy_run(int i){
    map<Sprite::Orientation, string> sprites;
    sprites[Sprite::Orientation::RIGHT] = "src/images/space_ships/enemy_space_ship_right.png";
    sprites[Sprite::Orientation::LEFT] = "src/images/space_ships/enemy_space_ship_left.png";
    sprites[Sprite::Orientation::UP] = "src/images/space_ships/enemy_space_ship_up.png";
    sprites[Sprite::Orientation::DOWN] = "src/images/space_ships/enemy_space_ship_down.png";

    Enemy* new_enemy;
    if (i % 2 == 0){
        new_enemy = new EnemyRandom(SCALE, 0, ENEMIES_SPEED, sprites, MovingSprite::Orientation::UP, _clock_obj);
    } else {
        // FIXME INSERIR AQUI O OUTRO TIPO DE INIMIGO
        new_enemy = new EnemyRandom(SCALE, 0, ENEMIES_SPEED, sprites, MovingSprite::Orientation::UP, _clock_obj);
    }
    
    _enemy_objects.push_back(new_enemy);
    new_enemy->run();
}

void Game::_window_run() {
    db<Game>(INF) << "[Game] Instanciando uma nova janela!\n";
    std::list<sf::Sprite*> enemies_sprites_list;
    for (auto enemy : _enemy_objects) enemies_sprites_list.push_back(enemy -> get_sprite());
    _window_obj = new Window(_player_obj->get_sprite(), enemies_sprites_list, _screen->get_sprite(), _clock_obj);
    db<Game>(INF) << "[Game] Chamando método run da janela!\n";
    _window_obj -> run();
}

void Game::_keyboard_run() {
    db<Game>(INF) << "[Game] Instanciando um novo teclado!\n";
    _keyboard_obj = new Keyboard(_window_obj, _controller_obj);
    db<Game>(INF) << "[Game] Chamando método run do teclado!\n";
    _keyboard_obj -> run();
}

void Game::_controller_run() {
    db<Game>(INF) << "[Game] Instanciando um novo controller!\n";
    _controller_obj = new Controller(_player_thread, _enemy_threads, _player_obj -> get_move_queue());
    db<Game>(INF) << "[Game] Chamando método run do controller!\n";
    _controller_obj -> run();
}

void Game::_player_run() {
    map<Sprite::Orientation, string> sprites;
    sprites[Sprite::Orientation::RIGHT] = "src/images/space_ships/space_ship_right.png";
    sprites[Sprite::Orientation::LEFT] = "src/images/space_ships/space_ship_left.png";
    sprites[Sprite::Orientation::UP] = "src/images/space_ships/space_ship_up.png";
    sprites[Sprite::Orientation::DOWN] = "src/images/space_ships/space_ship_down.png";
    db<Game>(INF) << "[Game] Instanciando um novo player!\n";
    _player_obj = new Player(SCALE, 1, ENEMIES_SPEED, sprites, Sprite::Orientation::UP, _clock_obj);
    // _player_obj = new Player(scale, size, speed, paths, sprites, clock);
    db<Game>(INF) << "[Game] Chamando método run do player!\n";
    _player_obj -> run();
}

void Game::run(void* name){
    //Instancia um clock
    _clock_obj = new Clock();
    map<Sprite::Orientation, string> path;
    path[Sprite::Orientation::STATIC] = "src/images/screen/screen.png";
    _screen = new StaticSprite(SCREEN_SCALE, 0, path, Sprite::Orientation::STATIC);

    // _window_thread = new Window(_window_run(_player_object, _enemy_object, ...))
    db<Game>(INF) << "[Game] Iniciando a thread do player\n";
    _player_thread = new Thread(_player_run);

    db<Game>(INF) << "[Game] Iniciando a thread dos inimigos\n";
    for (int i = 0; i < NUMBER_OF_ENEMIES; i++){
        _enemy_threads.push_back(new Thread(_enemy_run, i)); 
    }

    db<Game>(INF) << "[Game] Iniciando a thread da janela\n";
    _window_thread = new Thread(_window_run);

    db<Game>(INF) << "[Game] Iniciando a thread do controller\n";
    _controller_thread = new Thread(_controller_run);

    // db<Game>(INF) << "[Game] Iniciando a thread do player\n";
    // _player_thread = new Thread(_player_run);

    db<Game>(INF) << "[Game] Iniciando a thread do teclado\n";
    _keyboard_thread = new Thread(_keyboard_run);

    db<Game>(INF) << "[Game] Chamando join\n";
    _window_thread -> join();
    _controller_thread -> join();
    _keyboard_thread -> join();
    _player_thread -> join();
    for (auto enemy_thread : _enemy_threads){
        enemy_thread -> join(); 
    }
    // realizar chamada da Thread Player
}

Game::~Game() {
    delete _window_obj;
    delete _window_thread;
}

__END_API