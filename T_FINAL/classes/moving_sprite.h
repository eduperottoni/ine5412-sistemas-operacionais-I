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
class MovingSprite : virtual public Sprite {
    public:
        MovingSprite(float scale, int size, float speed, const map<Sprite::Orientation, string>& paths, Sprite::Orientation initial_orientation, Clock* clock) 
        : Sprite(scale, size, paths, initial_orientation) {
            _clock = clock;
            _speed = speed;
            cout << "MovingSprite construido";
        };
        // ~MovingSprite();

        // Moves the Sprite (sets the texture and the position)
        void move(Orientation orientation);

        // Sets the position of the object
        // void set_position(tuple<int, int>);

    protected:
        float _speed;
        sf::Vector2f _movement;
        Clock* _clock;
};

__END_API

#endif