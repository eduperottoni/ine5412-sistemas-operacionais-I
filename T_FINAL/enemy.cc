#include "classes/enemy.h"

__BEGIN_API

//Enemy space ship texture
sf::Texture enemy_ship_down;
sf::Texture enemy_ship_right;
sf::Texture enemy_ship_left;
sf::Texture enemy_ship_up;
static sf::Sprite enemy_ship_sprite;
// Enemy::vel; 

// Construtor de Enemy
Enemy::Enemy(Keyboard * keyboard) {
    db<Enemy>(INF) << "[Enemy] Construindo inimigo!\n";
}

void Enemy::move(const std::string direction){

    if(direction == "Left") {
        db<Enemy>(TRC) <<"[Enemy] Direção a esquerda \n";
        // carrega a sprite do jogador para a esquerda
       enemy_ship_sprite.setTexture(enemy_ship_left);
       enemy_ship_sprite.setPosition(enemy_ship_sprite.getPosition().x - vel, enemy_ship_sprite.getPosition().y);
    } else if(direction == "Right") {
        db<Enemy>(TRC) <<"[Enemy] Direção a direita \n";
        // // carrega a sprite do jogador para a direita
        enemy_ship_sprite.setTexture(enemy_ship_right);
        enemy_ship_sprite.setPosition(enemy_ship_sprite.getPosition().x + vel, enemy_ship_sprite.getPosition().y);
    }

     db<Enemy>(INF) << "[Enemy] Chamada de yield !\n";
    Thread::yield();
}

void Enemy::rotate(const std::string direction){
    if(direction == "Down") {
        db<Enemy>(TRC) <<"[Enemy] Direção a baixo \n";
        // carregar a sprite do jogador para baixo
        enemy_ship_sprite.setTexture(enemy_ship_down);
        enemy_ship_sprite.setPosition(enemy_ship_sprite.getPosition().x, enemy_ship_sprite.getPosition().y - vel);
                
    } else if(direction == "Up") {
        db<Enemy>(TRC) <<"[Enemy] Direção a cima \n";
        // carregar a sprite do jogador para cima
        enemy_ship_sprite.setTexture(enemy_ship_up);
        enemy_ship_sprite.setPosition(enemy_ship_sprite.getPosition().x, enemy_ship_sprite.getPosition().y + vel);
    }
     db<Enemy>(INF) << "[Enemy] Chamada de yield !\n";
    Thread::yield();
}

void Enemy::spawn(int x, int y) {
    db<Enemy>(INF) << "[Enemy] Chamada de spawn !\n";
    // Seta textura inicial
    enemy_ship_sprite.setTexture(enemy_ship_up);
    // Seta a escala da textura
    enemy_ship_sprite.scale(-0.5, -0.5);
    // Posição incial de spawn do jogador
    enemy_ship_sprite.setPosition(x,y);

    db<Enemy>(INF) << "[Enemy] Chamada de yield !\n";
    while (true)
    {
        Thread::yield();;
    }
    
}

Enemy::~Enemy(){
    // deleta o inimigo
    delete this;
}

__END_API
