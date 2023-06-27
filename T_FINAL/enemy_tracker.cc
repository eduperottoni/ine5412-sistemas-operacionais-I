#include "classes/enemy_tracker.h"

__BEGIN_API

// void EnemyTracker::run() {
//     int posX = 0 * (1086 / 2);
//     int posY = 0 * (746 / 2);
//     int direction = 1; // 1 para a direita, -1 para a esquerda
//     int speed = 2;

//     while (true) {
//         // Movimento horizontal
//         posX += speed * direction;
//         if (posX <= 0 * (1086 / 2) ||
//             posX >= (0 + 1) * (1086 / 2)) {
//             direction *= -1; // Inverte a direção quando atingir os limites do quadrante
//         }

//         // Movimento vertical
//         posY += speed;
//         if (posY >= (0 + 1) * (746 / 2)) {
//             posY = 0 * (746 / 2); // Reinicia a posição no início do quadrante
//         }

//         // Atualizar a posição do inimigo na tela
//         _sprite.setPosition(posX, posY);

//         // Aguardar um curto intervalo antes de atualizar a posição novamente
//         // std::this_thread::sleep_for(std::chrono::milliseconds(50));
//         Thread::yield();
//     }
// }


void EnemyTracker::run(){
    GameConfig* game_config = &GameConfig::get_instance();
    int timer = 100;
    int timer_shoot = 80;
    int counter = 0;
    int counter_shoot = 0;

    while (*game_config -> get_game_state() != GameConfig::State::FINISHING) {
        if (_can_render) {
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
        } else {
            double timestamp = _clock->get_current_time();
            if (timestamp - _time_off >= 2){
                db<EnemyRandom>(INF) << "[Enemy] PASSOU OS DOIS SEGUNDOS" << "\n";
                _sprite.setScale(_scale, _scale);
                _can_render = true;
            }
        }
        // Chamando yield ao final da chamada
        Thread::yield();
    }
    db<EnemyRandom>(INF) << "[EnemyRandom] SAINDO DA THREAD ENEMY_TRACKER !" << counter << "\n";
}

__END_API