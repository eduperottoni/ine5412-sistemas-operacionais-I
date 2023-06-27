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
        if (!_move_queue.empty()) {
            Keyboard::Move move = _move_queue.front();
            _move_queue.pop();
            switch (move) {
            case Keyboard::Move::UP:
                MovingSprite::move(Orientation::UP);
                break;
            case Keyboard::Move::DOWN:
                MovingSprite::move(Orientation::DOWN);
                break;
            case Keyboard::Move::LEFT:
                MovingSprite::move(Orientation::LEFT);
                break;
            case Keyboard::Move::RIGHT:
                MovingSprite::move(Orientation::RIGHT);
                break;
            case Keyboard::Move::SHOOT:
                if (_ready_to_shoot) {
                    shoot();
                }
                break;
            default:
                break;
            }
        }
        Thread::yield();
    }
}

std::queue<Keyboard::Move>* Player::get_move_queue(){
    return &_move_queue;
}

__END_API