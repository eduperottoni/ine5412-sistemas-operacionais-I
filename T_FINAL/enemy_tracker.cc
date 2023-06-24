#include "classes/enemy_tracker.h"

__BEGIN_API

void EnemyTracker::run(){
    int timer = 100;
    int timer_shoot = 30;
    int counter = 0;
    int counter_shoot = 0;

    while (true) {
        db<EnemyRandom>(INF) << "[EnemyRandom] GET CLOCK !" << counter << "\n";
        counter++;
        counter_shoot++;

        if (counter_shoot > timer_shoot) {
            counter_shoot = 0;
            Spaceship::shoot();
        }

        if (counter > timer) {
            counter = 0;
            // Obter a posição atual do jogador
            sf::Vector2f playerPosition = _player_sprite->getPosition();

            // Obter a posição atual do inimigo
            sf::Vector2f enemyPosition = _sprite.getPosition();

            // Calcular a direção para o jogador
            float deltaX = playerPosition.x - enemyPosition.x;
            float deltaY = playerPosition.y - enemyPosition.y;
            Orientation newOrientation;

            if (std::abs(deltaX) > std::abs(deltaY)) {
                // Movimentar na direção horizontal
                newOrientation = (deltaX > 0) ? Orientation::RIGHT : Orientation::LEFT;
            } else {
                // Movimentar na direção vertical
                newOrientation = (deltaY > 0) ? Orientation::DOWN : Orientation::UP;
            }

            MovingSprite::move(newOrientation);
        } else {
            MovingSprite::move(_current_orientation);
        }

        // Chamando yield ao final da chamada
        Thread::yield();
    }
}

__END_API