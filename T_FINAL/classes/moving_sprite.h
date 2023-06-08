#ifndef MOVING_SPRITE_H
#define MOVING_SPRITE_H


#include "../src/lib/traits.h"
#include "sprite.h"
#include <tuple>

__BEGIN_API

class MovingSprite : public Sprite {
    public:
        void move();
    private:
        int speed;
};

__END_API

#endif