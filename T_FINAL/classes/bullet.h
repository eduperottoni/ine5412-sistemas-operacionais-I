#ifndef BULLET_H
#define BULLET_H


#include "../src/lib/traits.h"
#include "sprite.h"
#include "moving_sprite.h"
#include <tuple>

__BEGIN_API


class Bullet : public MovingSprite {
public:
    Bullet(float scale, int size, float speed, const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock, int x, int y)
        : MovingSprite(scale, size, speed, paths, initial_orientation, clock, x, y), Sprite(scale, size, paths, initial_orientation, x, y){
            
        };
private:
};


__END_API

#endif