#ifndef ENEMY_RANDOM_H
#define ENEMY_RANDOM_H

#include "../classes/enemy.h"
#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "../classes/window.h"
#include "../classes/bullet.h"
#include "sprite.h"
#include "spaceship.h"

#include <iostream>
#include <random>
#include <tuple>

__BEGIN_API


class EnemyRandom : virtual public Enemy {
    private:

        sf::Texture enemy_ship_down;
        sf::Texture enemy_ship_right;
        sf::Texture enemy_ship_left;
        sf::Texture enemy_ship_up;
        sf::Sprite enemy_ship_sprite;


    public:

        EnemyRandom(float scale, int size, float speed, const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock, int x, int y, std::list<Bullet*>* bullet_list, int quadrante)
        : Sprite(scale, size, paths, initial_orientation, x, y), 
        MovingSprite(scale, size, speed, paths, initial_orientation, clock, x, y, quadrante),
        Spaceship(scale, size, speed, paths, initial_orientation, clock, x, y, bullet_list, quadrante),
        Enemy(scale, size, speed, paths, initial_orientation, clock, x, y, bullet_list, quadrante) {
            std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << "/n";
        };

        // Método para movimentar o personagem
        void run() override;

        int get_random_num();

        // Método para o tiro do inimigo
        void shoot();
        
        // Método para obter um número entre 1 e 4 
        int random_num();
};

__END_API

#endif