#include "classes/enemy_random.h"

__BEGIN_API

int EnemyRandom::get_random_num(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 3);
    int randomNum = dist(gen);

    return randomNum;
}


void EnemyRandom::run() {
    GameConfig* game_config = &GameConfig::get_instance();
    int timer = 100;
    int timer_shoot = 80;
    int counter = 0;
    int counter_shoot = 0;
    while (*game_config -> get_game_state() != GameConfig::State::FINISHING) {
        if (_can_render){
            db<EnemyRandom>(INF) << "[EnemyRandom] GET CLOCK !" << counter << "\n";
            // verificar se o movimento está dentro da tela, com o tamanho da tela atual: TODO --> puxar o tamanho da tela por um metodo da classe 
            // if(this->enemy_ship_sprite.getPosition().x < _window->getsizex() && this->enemy_ship_sprite.getPosition().y < _window->getsizey()){
            counter++;
            counter_shoot++;

            if (counter_shoot > timer_shoot){
                counter_shoot = 0;
                Spaceship::shoot();
            }
            if (counter > timer) {
                counter = 0;
                int random_int = get_random_num();
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
        
        // Spaceship::shoot();
        // _sprite.setPosition(50, 50);

        // } // caso contrario, realiza o respaw do inimigo na posicao inicial 
        // else{
        //     db<Enemy>(INF) << "[Enemy] Sprite fora da tela! \n";
        // }
        // Chamando yield ao final da chamada
        Thread::yield();
    }
    db<EnemyRandom>(INF) << "[Enemy] SAINDO DO RUN DO INIMIGO" << "\n";
}

__END_API