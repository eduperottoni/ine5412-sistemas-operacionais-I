#ifndef MOVING_SPRITE_H
#define MOVING_SPRITE_H


#include "../src/lib/traits.h"
#include "sprite.h"
#include <tuple>
#include <map>
#include <string>


__BEGIN_API

using namespace std;
class MovingSprite : public Sprite {
    public:
        enum Orientation {
            UNIQUE,
            RIGHT,
            LEFT,
            UP,
            DOWN
        };
        MovingSprite(const map<Orientation, string>& paths);
        // ~MovingSprite();

        void move();
        sf::Sprite& get_current_sprite(){
            return _current_sprite;
        }

    protected:
        int _speed;
        Orientation _orientation;
        sf::Sprite _current_sprite;
        map<Orientation, sf::Texture> _textures;
};

__END_API

#endif