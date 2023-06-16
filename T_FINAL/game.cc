#include "classes/game.h"
#include <typeinfo>

__BEGIN_API

Thread* Game::_window_thread;
Window* Game::_window_obj;
Keyboard* Game::_keyboard_obj;
Thread* Game::_keyboard_thread;


void Game::_window_run() {
    db<Game>(INF) << "[Game] Instanciando uma nova janela!\n";
    _window_obj = new Window();
    std::cout << "Type: " << typeid(_window_obj).name() << std::endl;
    db<Game>(INF) << "[Game] Chamando método run da janela!\n";
    _window_obj -> run();
}

void Game::_keyboard_run() {
    db<Game>(INF) << "[Game] Instanciando um novo teclado!\n";
    _keyboard_obj = new Keyboard(_window_obj);
    db<Game>(INF) << "[Game] Chamando método run do teclado!\n";
    _keyboard_obj -> run();
}

void Game::run(void* name){
    db<Game>(INF) << "[Game] Inciando a thread da janela\n";
    _window_thread = new Thread(_window_run);
    db<Game>(INF) << "[Game] Inciando a thread do teclado\n";
    _keyboard_thread = new Thread(_keyboard_run);
    db<Game>(INF) << "[Game] Chamando join\n";
    _window_thread -> join();
    // realizar chamada da Thread Player
}

Game::~Game(){
    delete _window_obj;
    delete _window_thread;
}

__END_API