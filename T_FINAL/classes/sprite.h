#ifndef SPRITE_H
#define SPRITE_H

#include "../src/lib/traits.h"
#include "../src/lib/debug.h"
#include <tuple>

__BEGIN_API

class Sprite {
    public:
    private:
        
        int scale;
        int size;
        std::tuple<int, int> position;
};

__END_API

#endif