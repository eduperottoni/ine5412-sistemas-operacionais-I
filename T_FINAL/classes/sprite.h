#ifndef SPRITE_H
#define SPRITE_H

#include "../src/lib/traits.h"
#include "../src/lib/debug.h"
#include <tuple>
#include <string>
#include <SFML/Graphics.hpp>
#include <png.h>
#include <iostream>


using namespace std;
__BEGIN_API

class Sprite {
    public:
        // Carrega e devolve a textura
        sf::Texture load_texture(const string& path);
    protected:
        int scale;
        int size;
        std::tuple<int, int> position;
};

__END_API

#endif