#ifndef MOVING_SPRITE_H
#define MOVING_SPRITE_H


#include "../src/lib/traits.h"
#include "sprite.h"
#include <tuple>
#include <map>
#include <string>
#include "clock.h"

__BEGIN_API

using namespace std;
class MovingSprite : public Sprite {
    public:
        enum Orientation {
            RIGHT,
            LEFT,
            UP,
            DOWN
        };
        MovingSprite(const map<Orientation, string>& paths, Orientation initial_orientation, Clock* clock);
        // ~MovingSprite();

        // Moves the Sprite (sets the texture and the position)
        void move(Orientation orientation);

        // Returns the current sprite, that contains the correct texture.
        sf::Sprite* get_sprite();

        // Sets the position of the object
        // void set_position(tuple<int, int>);

    protected:
        float _speed;
        sf::Vector2f _movement;
        sf::Sprite _sprite;
        Clock* _clock;
        
        map<Orientation, sf::Texture> _textures;
};

__END_API

#endif