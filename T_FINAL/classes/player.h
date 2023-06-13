#ifndef PLAYER_H
#define PLAYER_H


#include "../src/lib/traits.h"
#include "sprite.h"
#include "spaceship.h"
#include <tuple>
#include "../src/lib/thread.h"
#include "../classes/window.h"

__BEGIN_API


class Player : public Spaceship {
    private:
        // Player's health
        int health = 5;
        // Player's score
        int score = 0;
        // Thread do jogador
        Thread *_player;
        // Variável booleana estática que sinaliza que o player está pronto para ser desenhado
        static bool _ready;
    public:
        // Construtor de Classe
        Player();
        // Destrutor da classe
        ~Player();
        // Método para movimentar o personagem
        void move(const std::string direction);
        // Método para rotacionar o personagem
        void rotate(const std::string direction);
        // Método para inciar o jogador
        void init();
        // Método para desenhar o jogador em uma determinada posição da tela
        static void spawn(int x, int y);
        // Obtendo a posição do jogador
        int getposition(int x, int y);
        // Seta a posição do jogador
        void setposition(int x, int y);
        // chamda de window
        Window* _window_obj;
};


__END_API

#endif