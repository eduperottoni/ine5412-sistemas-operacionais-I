#include "classes/game.h"
#include <typeinfo>

__BEGIN_API

Thread* Game::_window_thread;
Window* Game::_window_obj;
Thread* Game::_keyboard_thread;
Keyboard* Game::_keyboard_obj;
Thread* Game::_controller_thread;
Controller* Game::_controller_obj;
Player* Game::_player_obj;
Thread* Game::_player_thread;


//Player* Game::_player_obj;
//Thread* Game::_player_thread;

void Game::_window_run() {
    db<Game>(INF) << "[Game] Instanciando uma nova janela!\n";
    _window_obj = new Window(_player_obj -> get_sprite());
    std::cout << "Type: " << typeid(_window_obj).name() << std::endl;
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
    _player_obj = new Player(sprites);
    db<Game>(INF) << "[Game] Chamando método run do player!\n";
    _player_obj -> run();
}

void Game::run(void* name){
    // _window_thread = new Window(_window_run(_player_object, _enemy_object, ...))
    db<Game>(INF) << "[Game] Iniciando a thread do player\n";
    _player_thread = new Thread(_player_run);
    db<Game>(INF) << "[Game] Iniciando a thread da janela\n";
    _window_thread = new Thread(_window_run);
    db<Game>(INF) << "[Game] Iniciando a thread do controller\n";
    _controller_thread = new Thread(_controller_run);
    db<Game>(INF) << "[Game] Iniciando a thread do teclado\n";
    _keyboard_thread = new Thread(_keyboard_run);
    db<Game>(INF) << "[Game] Chamando join\n";
    _window_thread -> join();
    _controller_thread -> join();
    _keyboard_thread -> join();
    // realizar chamada da Thread Player
}

Game::~Game() {
    delete _window_obj;
    delete _window_thread;
}

__END_API