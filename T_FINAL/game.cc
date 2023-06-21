#include "classes/game.h"
#include <typeinfo>

__BEGIN_API

Thread* Game::_window_thread;
Window* Game::_window_obj;

Thread* Game::_keyboard_thread;
Keyboard* Game::_keyboard_obj;

Thread* Game::_controller_thread;
Controller* Game::_controller_obj;

Enemy* Game::_enemy_obj;
Thread* Game::_enemy_thread0;

Player* Game::_player_obj;
Thread* Game::_player_thread;

GameConfig* Game::_game_config;

Clock* Game::_clock_obj;

void Game::configure(){
    _game_config = &GameConfig::get_instance();

    //TODO -> Aqui, inicializar as configurações utilizando os setters de GameConfig.
}

void Game::_window_run() {
    db<Game>(INF) << "[Game] Instanciando uma nova janela!\n";
    _window_obj = new Window(_player_obj->get_sprite(), _clock_obj);
    std::cout << "Type: " << typeid(_window_obj).name() << std::endl;
    db<Game>(INF) << "[Game] Chamando método run da janela!\n";
    if (_window_obj != nullptr) {
    _window_obj -> run();
    }
}

void Game::_keyboard_run() {
    db<Game>(INF) << "[Game] Instanciando um novo teclado!\n";
    _keyboard_obj = new Keyboard(_window_obj, _controller_obj);
    db<Game>(INF) << "[Game] Chamando método run do teclado!\n";
    if (_keyboard_obj != nullptr) {
        _keyboard_obj -> run();
    }
}

void Game::_controller_run() {
    db<Game>(INF) << "[Game] Instanciando um novo controller!\n";
    _controller_obj = new Controller();
    db<Game>(INF) << "[Game] Chamando método run do controller!\n";
    _controller_obj -> run();
}

void Game::_player_run() {
    map<MovingSprite::Orientation, string> sprites;
    sprites[MovingSprite::Orientation::RIGHT] = "src/images/space_ships/space_ship_right.png";
    sprites[MovingSprite::Orientation::LEFT] = "src/images/space_ships/space_ship_left.png";
    sprites[MovingSprite::Orientation::UP] = "src/images/space_ships/space_ship_up.png";
    sprites[MovingSprite::Orientation::DOWN] = "src/images/space_ships/space_ship_down.png";
    db<Game>(INF) << "[Game] Instanciando um novo player!\n";
    _player_obj = new Player(sprites, MovingSprite::Orientation::UP, _clock_obj);
    db<Game>(INF) << "[Game] Chamando método run do player!\n";
    _player_obj -> run();
}

void Game::_enemy_run(){
    map<MovingSprite::Orientation, string> sprites;
    sprites[MovingSprite::Orientation::RIGHT] = "src/images/space_ships/space_ship_right.png";
    sprites[MovingSprite::Orientation::LEFT] = "src/images/space_ships/space_ship_left.png";
    sprites[MovingSprite::Orientation::UP] = "src/images/space_ships/space_ship_up.png";
    sprites[MovingSprite::Orientation::DOWN] = "src/images/space_ships/space_ship_down.png";
    db<Game>(INF) << "[Game] Instanciando um novo player!\n";
    _player_obj = new Player(sprites, MovingSprite::Orientation::UP, _clock_obj);
    db<Game>(INF) << "[Game] Chamando método run do player!\n";
    _player_obj -> run();
}

void Game::run(void* name){
    //Instancia um clock
    _clock_obj = new Clock();

    // _window_thread = new Window(_window_run(_player_object, _enemy_object, ...))
    db<Game>(INF) << "[Game] Iniciando a thread do player\n";
    _player_thread = new Thread(_player_run);

    db<Game>(INF) << "[Game] Iniciando a thread da janela\n";
    _window_thread = new Thread(_window_run);
    
    db<Game>(INF) << "[Game] Iniciando a thread do controller\n";
    _controller_thread = new Thread(_controller_run);

    // db<Game>(INF) << "[Game] Chamando join\n";
    // _controller_thread->join();
    
    db<Game>(INF) << "[Game] Iniciando a thread do teclado\n";
    _keyboard_thread = new Thread(_keyboard_run);
    
    db<Game>(INF) << "[Game] Chamando inimigo\n";
    _enemy_thread0 = new Thread(_enemy_run);

    db<Game>(INF) << "[Game] Chamando join\n";                                                                                                  
    _window_thread -> join();
    _controller_thread -> join();
    _keyboard_thread -> join();    
    _enemy_thread0->join();
}


// Game::~Game() {
//     delete _window_obj;
//     delete _window_thread;
//     delete _enemy_thread0;
// }


__END_API