#ifndef MOVING_SPRITE_H
#define MOVING_SPRITE_H


#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "sprite.h"
#include <tuple>
#include <map>
#include <string>


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
        // MovingSprite(){};
        MovingSprite(const map<Orientation, string>& paths);
        // ~MovingSprite();

        // Moves the Sprite (sets the texture and the position)
        void move(Orientation orientation);

        void init();

        // Pegar a posição atual do sprite
        // std::tuple<float,float> getposition(){return std::make_tuple(_current_sprite.getPosition().x,_current_sprite.getPosition().y);}

        // Returns the current sprite, that contains the correct texture.
        sf::Sprite& get_current_sprite();

        // Sets the position of the object
        // void set_position(tuple<int, int>);

    protected:
        int _speed;
        Orientation _orientation;
        sf::Sprite _current_sprite;
        
        map<Orientation, sf::Texture> _textures;
};

__END_API

#endif