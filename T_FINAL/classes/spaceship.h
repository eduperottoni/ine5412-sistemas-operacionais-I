#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../src/lib/traits.h"
#include "../src/lib/debug.h"
#include "moving_sprite.h"
#include <tuple>

__BEGIN_API

class Spaceship : virtual public MovingSprite {
    public:
        Spaceship(float scale, int size, float speed, const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock)
        : MovingSprite(scale, size, speed, paths, initial_orientation, clock), Sprite(scale, size, paths, initial_orientation) {};
        virtual void run() = 0;
        // virtual void shoot() = 0;
        // virtual void die() = 0;
    private:
};

__END_API

#endif