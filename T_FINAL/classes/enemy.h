#ifndef ENEMY_H
#define ENEMY_H

#include "../classes/keyboard.h"
#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "../classes/window.h"
#include "sprite.h"
#include "spaceship.h"

#include <iostream>
#include <random>
#include <tuple>

__BEGIN_API


class Enemy : 
    public Spaceship {
    private:
        const static int vel = 10;
        int move;

        // sf::Texture enemy_ship_down;
        // sf::Texture enemy_ship_right;
        // sf::Texture enemy_ship_left;
        // sf::Texture enemy_ship_up;
        // sf::Sprite enemy_ship_sprite;


    public:
        // Construtor de Classe
        Enemy(const std::map<Orientation, std::string>& paths)
        : MovingSprite(paths), Spaceship(paths){};
        // MovingSprite

        // getter da posição do sprite do inimigo
        int getter(int x, int y);
        // Destrutor da classe
        // ~Enemy();

        // Método para movimentar o personagem
        void run();
        
        // Método para obter um número entre 1 e 4 
        int random_num();
};

__END_API

#endif