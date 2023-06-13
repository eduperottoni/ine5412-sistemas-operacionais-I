#include "classes/player.h"
__BEGIN_API

// Construtor de Player
Player::Player(){
    db<Player>(INF) << "[Jogador] Construindo jogador!\n";
    _player = new Thread(spawn);    
    // Chamada de join
    _player->join();
    // Chamada de init do desenho
    init();
}


void Player::init(){
    db<Player>(INF) << "[Jogador] Desenhando Jogador\n";

}


void Player::move(const std::string direction){

}

void Player::rotate(const std::string direction){

}

void Player::spawn() {

}

Player::~Player(){
    // deleta a thread de jogador
    delete _player;
}

__END_API