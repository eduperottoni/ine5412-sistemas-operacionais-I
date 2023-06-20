#ifndef BULLET_H
#define BULLET_H


#include "../src/lib/traits.h"
#include "sprite.h"
#include "moving_sprite.h"
#include <tuple>

__BEGIN_API


class Bullet : public MovingSprite {
public:
    Bullet(const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock)
        : MovingSprite(paths, initial_orientation, clock){
            _speed = 100.f;
        };
private:
};


__END_API

#endif