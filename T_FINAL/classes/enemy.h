#ifndef ENEMY_H
#define ENEMY_H

#include "../classes/keyboard.h"
#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "../classes/moving_sprite.h"
#include "../classes/bullet.h"
#include "sprite.h"
#include "spaceship.h"

#include <iostream>
#include <random>
#include <tuple>

__BEGIN_API


class Enemy : 
    virtual public Spaceship {
    public:
        // Construtor de Classe
        Enemy(float scale, int size, float speed, const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock, int x, int y, std::list<Bullet*>* bullet_list,  int quadrante)
        : Sprite(scale, size, paths, initial_orientation, x, y), MovingSprite(scale, size, speed, paths, initial_orientation, clock, x, y, quadrante), Spaceship(scale, size, speed, paths, initial_orientation, clock, x, y, bullet_list, quadrante){};


        // Método para movimentar o personagem
        virtual void run() = 0;

        // Método para o tiro do inimigo
        void shoot();
};

__END_API

#endif