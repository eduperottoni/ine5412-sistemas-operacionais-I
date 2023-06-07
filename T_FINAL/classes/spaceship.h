#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "traits.h"
#include "debug.h"
#include "moving_sprite.h"
#include <tuple>

__BEGIN_GAME

class Spaceship : public MovingSprite {
    public:
        void shoot();
        void die();
    private:
};

__END_GAME

#endif