#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../src/lib/traits.h"
#include "../src/lib/debug.h"
#include "moving_sprite.h"
#include <tuple>

__BEGIN_API

class Spaceship : virtual public MovingSprite {
    public:
        Spaceship(){};
        Spaceship(const std::map<Orientation, std::string>& paths)
        : MovingSprite(paths){};
        void shoot();
        void die();
    private:
};

__END_API

#endif