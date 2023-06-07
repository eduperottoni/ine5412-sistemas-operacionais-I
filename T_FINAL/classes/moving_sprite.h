#ifndef MOVING_SPRITE_H
#define MOVING_SPRITE_H


#include "traits.h"
#include "sprite.h"
#include <tuple>

__BEGIN_GAME

class MovingSprite : public Sprite {
    public:
        void move();
    private:
        int speed;
};

__END_GAME

#endif