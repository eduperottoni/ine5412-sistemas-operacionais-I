#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../src/lib/traits.h"
#include "sprite.h"
#include "window.h"
#include <tuple>
#include <SFML/Graphics.hpp>

__BEGIN_API


class Keyboard {
public:
    Keyboard(Window* window);

    void run();

private:
    void read_key();
    sf::RenderWindow* _sf_window;
};

__END_API

#endif