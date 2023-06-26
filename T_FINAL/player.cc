#include "classes/player.h"

__BEGIN_API

std::queue<Keyboard::Move> Player::_move_queue;

// sf::Sprite Player::get_current_sprite()
// {
//     return _current_sprite;
// }
// Construtor de Player
//     db<Player>(INF) << "[Jogador] Construindo jogador!\n";
//     // Chamada da Thread do Jogador
//     // _player = new Thread();    
//     // Chamada de join
//     // _player->join();
//     // Chamada de init do desenho
//     init();
// }

void Player::increment_score(int value){
    _score += value;
}

void Player::increment_kill(){
    _kills++;
}

void Player::decrement_health() {
    _health--;
}

int Player::get_score(){
    return _score;
}

int Player::get_kills(){
    return _kills;
}

void Player::run() {
    while (true) {
        if (!_move_queue.empty()) {
            Keyboard::Move move = _move_queue.front();
            _move_queue.pop();
            switch (move) {
            case Keyboard::Move::UP:
                db<Player>(TRC) << "[Player] UP \n";
                MovingSprite::move(Orientation::UP);
                break;
            case Keyboard::Move::DOWN:
                db<Player>(TRC) << "[Player] DOWN \n";
                MovingSprite::move(Orientation::DOWN);
                break;
            case Keyboard::Move::LEFT:
                db<Player>(TRC) << "[Player] LEFT \n";
                MovingSprite::move(Orientation::LEFT);
                break;
            case Keyboard::Move::RIGHT:
                db<Player>(TRC) << "[Player] RIGHT \n";
                MovingSprite::move(Orientation::RIGHT);
                break;
            case Keyboard::Move::SHOOT:
                db<Controller>(TRC) << "[PLAYER] SHOOT \n";
                if (_ready_to_shoot) {
                    shoot();
                }
                break;
            default:
                break;
            }
        } else {
            db<Player>(TRC) << "[PLAYER] EMPTY\n";
        }
        Thread::yield();
    }
}

std::queue<Keyboard::Move>* Player::get_move_queue(){
    db<Player>(TRC) << "[CONTROLLER] Entrei no getter do _move_queue! \n";
    return &_move_queue;
}


// void Player::init(){
//     db<Player>(INF) << "[Jogador] Desenhando Jogador\n";
//     // Verificações a ser realizadas (a discutir):
//     // Verificação se há espaço em pilha para desenhar o jogador
//     // Verificação se o sprite está disponível para desenhar
//     // Spawn no meio da tela
//     spawn(450,100);
// }


// void Player::move(const std::string direction){

//     if(direction == "Left") {
//         db<Window>(TRC) <<"[Jogador] Tecla a esquerda \n";
//         // carrega a sprite do jogador para a esquerda
//        space_ship_sprite.setTexture(space_ship_left);
//        space_ship_sprite.setPosition(space_ship_sprite.getPosition().x - 10, space_ship_sprite.getPosition().y);
//     } else if(direction == "Right") {
//         db<Window>(TRC) <<"[Jogador] Tecla a direita \n";
//         // carrega a sprite do jogador para a direita
//         space_ship_sprite.setTexture(space_ship_right);
//         space_ship_sprite.setPosition(space_ship_sprite.getPosition().x + 10, space_ship_sprite.getPosition().y);
//     }        

// }

// void Player::rotate(const std::string direction){
//     if(direction == "Down") {
//         db<Window>(TRC) <<"[Jogador] Tecla para baixo \n";
//         // carregar a sprite do jogador para baixo
//         space_ship_sprite.setTexture(space_ship_down);
//         space_ship_sprite.setPosition(space_ship_sprite.getPosition().x, space_ship_sprite.getPosition().y - 10);
                
//     } else if(direction == "Up") {
//         db<Window>(TRC) <<"[Jogador] Tecla para cima \n";
//         // carregar a sprite do jogador para cima
//         space_ship_sprite.setTexture(space_ship_up);
//         space_ship_sprite.setPosition(space_ship_sprite.getPosition().x, space_ship_sprite.getPosition().y + 10);
//     }
// }

// void Player::spawn(int x, int y) {
//     db<Player>(INF) << "[Jogador] Chamada de spawn !\n";
//     // Seta textura inicial
//     space_ship_sprite.setTexture(space_ship_up);
//     // Seta a escala da textura
//     space_ship_sprite.scale(-0.5, -0.5);
//     // Posição incial de spawn do jogador
//     space_ship_sprite.setPosition(x,y);


// }

// Player::~Player(){
//     // deleta a thread de jogador
//     delete _player;
// }

__END_API