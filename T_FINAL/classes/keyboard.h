#ifndef KEYBOARD_H
#define KEYBOARD_H


#include "../src/lib/traits.h"
#include "sprite.h"
#include <tuple>

__BEGIN_API


class Keyboard {
public:
    Keyboard();

    void run();

private:
    void read_key();

};

__END_API

#endif