#ifndef PLAYER_H
#define PLAYER_H


#include "../src/lib/traits.h"
#include "sprite.h"
#include "spaceship.h"
#include <tuple>
#include "../src/lib/thread.h"

__BEGIN_API


class Player : public Spaceship {
    private:
        int health;
        // Player's score
        int score;
        // Thread do jogador
        Thread *_player;
        // Variável booleana estática que sinaliza que o player está pronto para ser desenhado
        static bool _ready;
    public:
        Player(){ }

        // Destrutor da classe
        ~Player();

        void move(const std::string direction);
        void rotate(const std::string direction);
        // Método para inciar o jogador
        void init();
        // Método para pintar o jogador
        void spawn();
};


__END_API

#endif