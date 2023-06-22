#include "classes/enemy.h"

__BEGIN_API

//Enemy space ship textures

// void Enemy::Enemy(){
//        db<Enemy>(INF) << "[Enemy] Chamada de run!\n"; 
//     
//     Thread::yield();
// }

void Enemy::shoot(){
    while(true){
        db<Enemy>(INF) << "[Enemy] Chamada de tiro !\n";
        break;

        Thread::yield();
    }
}

// Enemy::~Enemy(){
//     // deleta o inimigo
//     delete this;
// }

__END_API
