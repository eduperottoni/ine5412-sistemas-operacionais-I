#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../src/lib/traits.h"
#include "../src/lib/debug.h"
#include "moving_sprite.h"
#include <tuple>

__BEGIN_API

class Spaceship : public MovingSprite {
    public:
        void shoot();
        void die();
    private:
};

__END_API

#endif