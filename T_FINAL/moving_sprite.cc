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

void MovingSprite::set_can_render(bool can_render){ 
    _can_render = can_render;
    if (!_can_render){
        _time_off = _clock->get_current_time();
        _sprite.scale(0.f, 0.f);
    }
}

void MovingSprite::set_speed(float speed){ 
    _speed = speed;
}



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
        // _movement.x -= _speed;
        _movement.x -= _speed * delta;
        break;
    case Orientation::RIGHT:
        // x_position += _speed;
        // _movement.x -= _speed;
        _movement.x += _speed * delta;
        break;
    case Orientation::UP:
        // y_position -= _speed;
        // _movement.y -= _speed;
        _movement.y -= _speed * delta;
        break;
    case Orientation::DOWN:
        // y_position += _speed;
        // _movement.y += _speed;
        _movement.y += _speed * delta;
        break;
    default:
        break;
    }
    _current_orientation = orientation;
    
    // _sprite.setPosition(x_position, y_position);

    sf::FloatRect bounds = _sprite.getGlobalBounds();
    if (x_position < 0.f) _sprite.setPosition(0.f, y_position);
    else if (y_position < 0.f) _sprite.setPosition(x_position, 0.f);
    // TODO ARRUMAR ISSO AQUI
    else if (x_position + bounds.width > 1086 - 320) _sprite.setPosition(1086 - 320 - bounds.width, y_position);
    else if (y_position + bounds.height > 746 + 260) _sprite.setPosition(x_position, 746 + 260 - bounds.height);
    else{
        _sprite.move(_movement);
    }

    // 1086, 746
    db<MovingSprite>(TRC) << "[MovingSprite] posição do sprite"<< _sprite.getPosition().x << _sprite.getPosition().y<<"\n";
}

// MovingSprite::MovingSprite(float scale, int size, float speed, const map<Sprite::Orientation, string>& paths, Sprite::Orientation initial_orientation, Clock* clock)
// {
//     _clock = clock;
//     _speed = speed;
//     cout << "MovingSprite construido";
// }

__END_API