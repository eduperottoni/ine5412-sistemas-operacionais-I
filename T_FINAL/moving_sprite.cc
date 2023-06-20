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
    db<MovingSprite>(TRC) << "[MovingSprite] rodando método move \n";
    _sprite.setTexture(_textures.at(orientation));
    float x_position = _sprite.getPosition().x;
    float y_position = _sprite.getPosition().y;
    db<MovingSprite>(TRC) << x_position << "\n";
    db<MovingSprite>(TRC) << y_position << "\n";
    _movement.x = 0;
    _movement.y = 0;
    float delta = _clock -> get_delta_time();
    switch (orientation)
    {
    case Orientation::LEFT:
        // y_position -= _speed;
        _movement.x -= _speed * delta;
        break;
    case Orientation::RIGHT:
        // x_position += _speed;
        _movement.x += _speed * delta;
        break;
    case Orientation::UP:
        // y_position -= _speed;
        _movement.y -= _speed * delta;
        break;
    case Orientation::DOWN:
        // y_position += _speed;
        _movement.y += _speed * delta;
        break;
    default:
        break;
    }
    
    // _sprite.setPosition(x_position, y_position);

    sf::FloatRect bounds = _sprite.getGlobalBounds();
    if (x_position < 0.f) _sprite.setPosition(0.f, y_position);
    else if (y_position < 0.f) _sprite.setPosition(x_position, 0.f);
    // TODO ARRUMAR ISSO AQUI
    else if (x_position + bounds.width > 900) _sprite.setPosition(900 - bounds.width, y_position);
    else if (y_position + bounds.height > 560) _sprite.setPosition(x_position, 560 - bounds.height);
    else _sprite.move(_movement);
}

sf::Sprite* MovingSprite::get_sprite()
{
    return &_sprite;
}

MovingSprite::MovingSprite(const map<Orientation, string>& paths, Orientation initial_orientation, Clock* clock)
{
    for(const auto& item : paths){
        if (!_textures[item.first].loadFromFile(item.second)){
            db<MovingSprite>(INF) << "[MovingSprite] Erro no carregamento de texturas !\n";
        }
    }
    _sprite.setTexture(_textures.at(initial_orientation));
    _clock = clock;
    cout << "MovingSprite construido";
}

__END_API