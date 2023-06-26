#ifndef PLAYER_H
#define PLAYER_H

#include "keyboard.h"
#include "../src/lib/traits.h"
#include "sprite.h"
#include "spaceship.h"
#include <tuple>
#include "../src/lib/thread.h"
#include <queue>
#include "../classes/game_config.h"

__BEGIN_API


class Player : virtual public Spaceship {
    private:
        // Kills counter
        int _kills;
        // Player's health
        int _health;
        // Player's score
        int _score;
        // Current player sprite
        sf::Sprite _current_sprite;
        // Keyboard event queue
        static std::queue<Keyboard::Move> _move_queue;


    public:
        // Construtor de Classe
        Player(int health, float scale, int size, float speed, const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock, int x, int y, std::list<Bullet*>* bullet_list)
        : Spaceship(scale, size, speed, paths, initial_orientation, clock, x, y, bullet_list), MovingSprite(scale, size, speed, paths, initial_orientation, clock, x, y),
        Sprite(scale, size, paths, initial_orientation, x, y) {
            _kills = 0;
            _health = health;
            _score = 0;
        };

        void run();

        std::queue<Keyboard::Move>* get_move_queue();

        void increment_score(int value);

        void decrement_health();

        void increment_kill();

        int get_score();

        int get_kills();

        int get_health();

        // sf::Sprite get_current_sprite();

        // sf::Sprite get_sprite(Sprite::Orientation orientation){
        //     return 
        // }
        // // Destrutor da classe
        // ~Player();
        // // Método para movimentar o personagem
        // void move(const std::string direction);
        // // Método para rotacionar o personagem
        // void rotate(const std::string direction);
        // // Método para inciar o jogador
        // void init();
        // // Método para desenhar o jogador em uma determinada posição da tela
        // static void spawn(int x, int y);
        // // Obtendo a posição do jogador
        // int getposition(int x, int y);
        // // Seta a posição do jogador
        // void setposition(int x, int y);
};


__END_API

#endif