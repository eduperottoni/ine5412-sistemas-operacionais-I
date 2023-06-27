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
        MovingSprite(float scale, int size, float speed, const map<Sprite::Orientation, string>& paths, Sprite::Orientation initial_orientation, Clock* clock, int x, int y, int quadrante) 
        : Sprite(scale, size, paths, initial_orientation, x, y) {
            _clock = clock;
            _speed = speed;
            _can_render = true;
            cout << "MovingSprite construido";
            if (quadrante == 0) {
                _limit_left = 0;
                _limit_right = 1086 - 320;
                _limit_up = 0;
                _limit_down = 746;
            } else if (quadrante == 1) {
                _limit_left = 0;
                _limit_right = (1086 - 320)/2;
                _limit_up = 0;
                _limit_down = (746)/2;
            } else if (quadrante == 2) {
                _limit_left = (1086 - 320)/2;
                _limit_right = 1086 - 320;
                _limit_up = 0;
                _limit_down = 746/2;
            } else if (quadrante == 3) {
                _limit_left = 0;
                _limit_right = (1086 - 320)/2;
                _limit_up = 746/2;
                _limit_down = 746;
            } else if (quadrante == 4) {
                _limit_left = (1086-320)/2;
                _limit_right = 1086 - 320;
                _limit_up = 746/2;
                _limit_down = 746;
            }
        };
        // ~MovingSprite();

        // Moves the Sprite (sets the texture and the position)
        void move(Orientation orientation);

        // Enable/disable the Sprite
        void set_can_render(bool can_render);

        void set_speed(float speed);

    protected:
        int _limit_left;
        int _limit_right;
        int _limit_up;
        int _limit_down;
        float _speed;
        bool _can_render;
        double _time_off;
        sf::Vector2f _movement;
        Clock* _clock;
};

__END_API

#endif