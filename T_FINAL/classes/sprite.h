#ifndef SPRITE_H
#define SPRITE_H

#include "traits.h"
#include "debug.h"
#include <tuple>

__BEGIN_GAME

class Sprite {
    public:
    private:
        
        int scale;
        int size;
        std::tuple<int, int> position;
};

__END_GAME

#endif