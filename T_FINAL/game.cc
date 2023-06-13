#include "classes/game.h"

__BEGIN_API

Thread* Game::_window_thread;
Window* Game::_window_obj;

Game::~Game(){
    delete _window_obj;
    delete _window_thread;
}

__END_API