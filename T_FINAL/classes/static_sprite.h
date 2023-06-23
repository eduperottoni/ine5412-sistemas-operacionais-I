#ifndef STATIC_SPRITE_H
#define STATIC_SPRITE_H

#include "../src/lib/traits.h"
#include "../src/lib/debug.h"
#include "sprite.h"
#include <tuple>

__BEGIN_API

class StaticSprite : public Sprite {
    public:
        StaticSprite(float scale, int size, const map<Sprite::Orientation, string>& paths, Sprite::Orientation initial_orientation, int x, int y)
        : Sprite(scale, size, paths, initial_orientation, x, y) {};
    private:
};

__END_API

#endif