#include "classes/bullet.h"

__BEGIN_API

bool Bullet::out_of_screen(){
    int WIDTH_OF_SCREEN = 1086;
    int HEIGHT_OF_SCREEN = 746;
    sf::FloatRect bounds = _sprite.getGlobalBounds();
    float x_position = _sprite.getPosition().x;
    float y_position = _sprite.getPosition().y;
    switch (_current_orientation)
    {
    case Orientation::UP:
        return y_position <= - bounds.height;
        break;
    case Orientation::DOWN:
        return y_position >= HEIGHT_OF_SCREEN;
    case Orientation::LEFT:
        return x_position <= 0;
    case Orientation::RIGHT:
        return x_position >= WIDTH_OF_SCREEN;
    default:
        break;
    }
}

// Herda método de movimentação da classe pai
void Bullet::update(){
    // if (!out_of_screen()){
    MovingSprite::move(_current_orientation);
    // }
    db<Bullet>(INF) << "[Game] ORIENTAÇÃO:" << _current_orientation <<"\n";
}

__END_API
