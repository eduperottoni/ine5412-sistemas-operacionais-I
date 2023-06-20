#ifndef ENEMY_H
#define ENEMY_H

#include "../classes/keyboard.h"
#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "sprite.h"
#include "spaceship.h"
#include <tuple>

__BEGIN_API


class Enemy : 
    public Spaceship {
    private:
        const static int vel = 10;

        // sf::Texture enemy_ship_down;
        // sf::Texture enemy_ship_right;
        // sf::Texture enemy_ship_left;
        // sf::Texture enemy_ship_up;
        // sf::Sprite enemy_ship_sprite;


    public:
        // Construtor de Classe
        Enemy();
        // Destrutor da classe
        ~Enemy();
        // Método para movimentar o personagem
        void move(const std::string direction);
        // Método para rotacionar o personagem
        void rotate(const std::string direction);
        // Método para realizar o spawn em uma determinada posição da tela
        void spawn(int x, int y);
        // Obtendo a posição do jogador
        int getposition(int x, int y);
        // Seta a posição do jogador
        void setposition(int x, int y);
        // chamda de window
        Window * _window_obj;
        Enemy * _enemy;
};

__END_API

#endif