#include "classes/player.h"

__BEGIN_API

std::queue<Keyboard::Move> Player::_move_queue;

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

int Player::get_health(){
    return _health;
}

void Player::set_health(int health) {
    _health = health;
}

void Player::set_kills(int kills) {
    _kills = kills;
}

void Player::set_score(int score) {
    _score = score;
}

void Player::run() {
    GameConfig* game_config = &GameConfig::get_instance();
    while (*game_config->get_game_state() != GameConfig::State::FINISHING) {
        db<Player>(TRC) << "[PLAYER] INICIO DA THREAD PLAYER\n";
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
    db<Player>(TRC) << "[PLAYER] FIM DA THREAD PLAYER\n";
}

std::queue<Keyboard::Move>* Player::get_move_queue(){
    db<Player>(TRC) << "[CONTROLLER] Entrei no getter do _move_queue! \n";
    return &_move_queue;
}

__END_API