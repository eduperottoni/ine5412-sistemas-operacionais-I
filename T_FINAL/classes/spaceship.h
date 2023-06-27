#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../src/lib/traits.h"
#include "../src/lib/debug.h"
#include "moving_sprite.h"
#include "bullet.h"
#include <tuple>

__BEGIN_API

class Spaceship : virtual public MovingSprite {
    public:
        Spaceship(float scale, int size, float speed, const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock, int x, int y, std::list<Bullet*>* bullet_list, int quadrante)
        : MovingSprite(scale, size, speed, paths, initial_orientation, clock, x, y, quadrante), Sprite(scale, size, paths, initial_orientation, x, y) {
            db<Spaceship>(TRC) << "[SPACESHIP] SHOOTING!!! \n";
            _ready_to_shoot = true;
            _bullet_list = bullet_list;
            // float scale, int size, float speed, const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock, int x, int y
        };
        virtual void run() = 0;
        void shoot();

        // virtual void die() = 0;
    protected:
        // Bullet* _bullet;
        bool _ready_to_shoot;
        std::list<Bullet*>* _bullet_list;
};

__END_API

#endif