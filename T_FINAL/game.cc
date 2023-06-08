#include "classes/game.h"

__BEGIN_API

Thread* Game::_window_thread;
Window* Game::_window_obj;

void Game::window_run() {
    std::cout << "Aqui 4" << std::endl;
    _window_obj = new Window();
    std::cout << "Aqui 5" << std::endl;

    _window_obj->run();
}

void Game::run(void* name) {
    std::cout << "Aqui 2" << std::endl;
    _window_thread = new Thread(window_run);
    std::cout << "Aqui 3" << std::endl;

    _window_thread -> join();
    //window_thread = new Thread(&window->run);
}

__END_API