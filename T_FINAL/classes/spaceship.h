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
        Spaceship(float scale, int size, float speed, const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock, int x, int y)
        : MovingSprite(scale, size, speed, paths, initial_orientation, clock, x, y), Sprite(scale, size, paths, initial_orientation, x, y) {
            std::map<Orientation, std::string> path;
            path[Orientation::STATIC] = "src/images/space_ships/shot.png";
            _bullet = new Bullet(scale, 0, speed*2, path, Orientation::STATIC, clock, x, y);
            db<Spaceship>(TRC) << "[SPACESHIP] SHOOTING!!! \n";
            _ready_to_shoot = true;

            // float scale, int size, float speed, const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock, int x, int y
        };
        virtual void run() = 0;
        void shoot();
        Bullet* get_bullet();

        // virtual void die() = 0;
    protected:
        Bullet* _bullet;
        bool _ready_to_shoot;
};

__END_API

#endif