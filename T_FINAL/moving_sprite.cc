#include "classes/moving_sprite.h"

__BEGIN_API

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
    _sprite.setTexture(_textures.at(orientation));
    float x_position = _sprite.getPosition().x;
    float y_position = _sprite.getPosition().y;
    _movement.x = 0;
    _movement.y = 0;
    float delta = _clock -> get_delta_time();
    switch (orientation)
    {
    case Orientation::LEFT:
        _movement.x -= _speed * delta;
        break;
    case Orientation::RIGHT:
        _movement.x += _speed * delta;
        break;
    case Orientation::UP:
        _movement.y -= _speed * delta;
        break;
    case Orientation::DOWN:
        _movement.y += _speed * delta;
        break;
    default:
        break;
    }
    _current_orientation = orientation;

    sf::FloatRect bounds = _sprite.getGlobalBounds();
    if (x_position < _limit_left) _sprite.setPosition(_limit_left, y_position);
    else if (y_position < _limit_up) _sprite.setPosition(x_position, _limit_up);
    else if (x_position + bounds.width > _limit_right) _sprite.setPosition(_limit_right - bounds.width, y_position);
    else if (y_position + bounds.height > _limit_down) _sprite.setPosition(x_position, _limit_down - bounds.height);
    else{
        _sprite.move(_movement);
    }
}

__END_API