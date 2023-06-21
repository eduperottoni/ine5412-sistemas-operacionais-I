#include "classes/moving_sprite.h"

__BEGIN_API


// Construtor de Player
// MovingSprite::MovingSprite() {
//     db<MovingSprite>(INF) << "[MovingSprite] Construindo Moving Sprite!\n";
//     init();
// }

void MovingSprite::init(){
    db<MovingSprite>(INF) << "[MovingSprite] Desenhando Moving Sprite\n";
    // Verificações a ser realizadas (a discutir):
    // Verificação se há espaço em pilha para desenhar o jogador
    // Verificação se o sprite está disponível para desenhar
    // Spawn no meio da tela
    // spawn(450,100);
}

// void MovingSprite::spawn(int x, int y) {
//     db<MovingSprite>(INF) << "[MovingSprite] Chamada de spawn !\n";
//     _current_sprite.setTexture(_textures.at(UP));
//     float x_position = x;
//     float y_position = y;
//     _current_sprite.setPosition(x_position, y_position);    
// }

void MovingSprite::move(Orientation orientation)
{
    _current_sprite.setTexture(_textures.at(orientation));
    float x_position = _current_sprite.getPosition().x;
    float y_position = _current_sprite.getPosition().y;
    
    switch (orientation)
    {
    case Orientation::LEFT:
        db<MovingSprite>(INF) << "[MovingSprite] Orientação do sprite "<< Orientation::LEFT <<"\n";
        x_position -= _speed;
        break;
    case Orientation::RIGHT:
        db<MovingSprite>(INF) << "[MovingSprite] Orientação do sprite "<< Orientation::RIGHT <<"\n";
        x_position += _speed;
        break;
    case Orientation::UP:
        db<MovingSprite>(INF) << "[MovingSprite] Orientação do sprite "<< Orientation::UP<<"\n";
        y_position += _speed;
        break;
    case Orientation::DOWN:
        db<MovingSprite>(INF) << "[MovingSprite] Orientação do sprite "<< Orientation::DOWN<<"\n";
        y_position -= _speed;
        break;
    default:
        break;
    }
    _current_sprite.setPosition(x_position, y_position);
}

sf::Sprite& MovingSprite::get_current_sprite()
{
    return _current_sprite;
}

MovingSprite::MovingSprite(const map<Orientation, string>& paths)
{
    for(const auto& item : paths){
        if (!_textures[item.first].loadFromFile(item.second)){
            db<MovingSprite>(INF) << "[MovingSprite] Erro no carregamento de texturas !\n";
        }
    }
    _current_sprite.setTexture(_textures.at(Orientation::UP));
    db<MovingSprite>(INF) << "[MovingSprite] MovingSprite construido !\n";
}

__END_API