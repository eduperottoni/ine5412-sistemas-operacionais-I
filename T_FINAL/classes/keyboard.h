#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../src/lib/traits.h"
#include <tuple>
#include <SFML/Graphics.hpp>
#include "../src/lib/thread.h"
#include <queue>

__BEGIN_API

class Controller;
class Window;
class Player;

class Keyboard {
public:

    void run();

    enum Move {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SHOOT,
        EXIT,
        PAUSE,
        UNPAUSE,
    };

    Keyboard(Window* window, Controller* controller, Player* player);

private:
    void read_key();
    sf::RenderWindow* _sf_window;
    std::queue<Keyboard::Move>* _action_queue;
    std::queue<Keyboard::Move>* _player_queue;
};

__END_API

#endif