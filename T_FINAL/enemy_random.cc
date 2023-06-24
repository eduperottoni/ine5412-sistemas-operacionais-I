#include "classes/enemy_random.h"

__BEGIN_API

int EnemyRandom::get_random_num(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 3);
    int randomNum = dist(gen);

    return randomNum;
}


void EnemyRandom::run(){
    while (true) {

        // verificar se o movimento está dentro da tela, com o tamanho da tela atual: TODO --> puxar o tamanho da tela por um metodo da classe 
        // if(this->enemy_ship_sprite.getPosition().x < _window->getsizex() && this->enemy_ship_sprite.getPosition().y < _window->getsizey()){
        int random_int = get_random_num();
        db<EnemyRandom>(INF) << "[Enemy] Chamada de run com int = " << random_int << "\n";
        switch (random_int)
        {
        case 2:
            // movimento do inimigo 
            MovingSprite::move(Orientation::UP);           
            break;
        
        case 3:   
            MovingSprite::move(Orientation::DOWN);  
            break;
        
        case 1:
            MovingSprite::move(Orientation::LEFT);                
            break;
        
        case 0:
            MovingSprite::move(Orientation::RIGHT);
            break;
        
        default:
            break;
        }
        // Spaceship::shoot();
        // _sprite.setPosition(50, 50);

        // } // caso contrario, realiza o respaw do inimigo na posicao inicial 
        // else{
        //     db<Enemy>(INF) << "[Enemy] Sprite fora da tela! \n";
        // }
        // Chamando yield ao final da chamada
        Thread::yield();
    }
}

__END_API