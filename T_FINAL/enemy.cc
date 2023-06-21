#include "classes/enemy.h"

__BEGIN_API

//Enemy space ship texture
sf::Texture enemy_ship_down;
sf::Texture enemy_ship_right;
sf::Texture enemy_ship_left;
sf::Texture enemy_ship_up;
static sf::Sprite enemy_ship_sprite;
MovingSprite *_movinsp;

// void Enemy::Enemy(){
//        db<Enemy>(INF) << "[Enemy] Chamada de run!\n"; 
//     
//     Thread::yield();
// }

int Enemy::random_num(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 4);
    int randomNum = dist(gen);

    return randomNum;
}

void Enemy::run(){
    while (true){
        // verificar se o movimento está dentro da tela, com o tamanho da tela atual
        db<Enemy>(INF) << "[Enemy] posição atual do sprite inimigo: " << this->getposition() << "\n";
        // verificar se o sprite está tocando outro sprite, caso este seja outro enemy realiza o respawn do enemy, caso seja o player, deletar o player.
        // if(this->getposition()){
            
            move = Enemy::random_num();
            db<Enemy>(INF) << "[Enemy] Chamada de número: " << move << "\n";
            // switch (move)
            // {
            // case move == 1:
            //     /* code */
            //     break;
            
            // default:
            //     break;
            // }
        // }


        // Chamando yield ao final da chamada
        Thread::yield();
    }
}

// Enemy::~Enemy(){
//     // deleta o inimigo
//     delete this;
// }

__END_API
