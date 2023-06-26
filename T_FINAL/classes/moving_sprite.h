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
        MovingSprite(float scale, int size, float speed, const map<Sprite::Orientation, string>& paths, Sprite::Orientation initial_orientation, Clock* clock, int x, int y) 
        : Sprite(scale, size, paths, initial_orientation, x, y) {
            _clock = clock;
            _speed = speed;
            _can_render = true;
            cout << "MovingSprite construido";
        };
        // ~MovingSprite();

        // Moves the Sprite (sets the texture and the position)
        void move(Orientation orientation);

        // Enable/disable the Sprite
        void set_can_render(bool can_render);

        void set_speed(float speed);

    protected:
        float _speed;
        bool _can_render;
        double _time_off;
        sf::Vector2f _movement;
        Clock* _clock;
};

__END_API

#endif