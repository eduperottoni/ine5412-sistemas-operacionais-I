#include "classes/moving_sprite.h"

__BEGIN_API
/*

// Construtor de Player
MovingSprite::MovingSprite() {
    db<MovingSprite>(INF) << "[MovingSprite] Construindo Moving Sprite!\n";
    init();
}

void MovingSprite::init(){
    db<MovingSprite>(INF) << "[MovingSprite] Desenhando Moving Sprite\n";
    // Verificações a ser realizadas (a discutir):
    // Verificação se há espaço em pilha para desenhar o jogador
    // Verificação se o sprite está disponível para desenhar
    // Spawn no meio da tela
    spawn(450,100);
}


void MovingSprite::move(const std::string direction){

}

void MovingSprite::rotate(const std::string direction){
}

void MovingSprite::spawn(int x, int y) {
    db<MovingSprite>(INF) << "[MovingSprite] Chamada de spawn !\n";


}

MovingSprite::~MovingSprite(){
}
*/

MovingSprite::MovingSprite(const map<Orientation, string>& paths)
{
    for(const auto& item : paths){
        if (!_textures[item.first].loadFromFile(item.second)){
            throw std::invalid_argument("Erro no carregamento de texturas");
        }
    }
    _current_sprite.setTexture(_textures.at(Orientation::UP));
    cout << "MovingSprite construido";
}

__END_API