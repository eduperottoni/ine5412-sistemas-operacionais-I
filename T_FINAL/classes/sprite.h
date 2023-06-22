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
        enum Orientation {
            STATIC,
            RIGHT,
            LEFT,
            UP,
            DOWN
        };
        // Carrega e devolve a textura
        sf::Texture load_texture(const string& path);
        sf::Sprite* get_sprite();
        Sprite(float scale, int size, const map<Orientation, string>& paths, Sprite::Orientation initial_orientation);

    protected:
        float scale;
        int size;
        std::tuple<int, int> position;
        sf::Sprite _sprite;
        map<Orientation, sf::Texture> _textures;
};

__END_API

#endif