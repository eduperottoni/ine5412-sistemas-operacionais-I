#ifndef PLAYER_H
#define PLAYER_H


#include "traits.h"
#include "sprite.h"
#include "spaceship.h"
#include <tuple>

__BEGIN_GAME


class Player : public Spaceship {
    private:
        int health;
    public:
        Player(){ }
        void move(const std::string direction);
        void rotate(const std::string direction);

};


__END_GAME

#endif