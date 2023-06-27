#include "classes/spaceship.h"

__BEGIN_API

void Spaceship::shoot() {
    sf::FloatRect bounds = _sprite.getGlobalBounds();
    float owner_x_pos = _sprite.getPosition().x;
    float owner_y_pos = _sprite.getPosition().y;
    Orientation owner_orientation = _current_orientation;
    
    float bullet_x_pos;
    float bullet_y_pos;
    switch (owner_orientation)
    {
    case Orientation::UP:
        bullet_x_pos = owner_x_pos + bounds.width/2;
        bullet_y_pos = owner_y_pos;
        break;
    case Orientation::DOWN:
        bullet_x_pos = owner_x_pos + bounds.width/2;
        bullet_y_pos = owner_y_pos + bounds.height;
        break;
    case Orientation::LEFT:
        bullet_x_pos = owner_x_pos;
        bullet_y_pos = owner_y_pos + bounds.height/2;
        break;
    case Orientation::RIGHT:
        bullet_x_pos = owner_x_pos + bounds.width;
        bullet_y_pos = owner_y_pos + bounds.height/2;
        break;
    default:
        break;
    }
    std::map<Orientation, std::string> path;
    path[_current_orientation] = "src/images/space_ships/shot.png";
    Bullet* bullet = new Bullet(_sprite.getScale().x, 0, _speed*2, path, _current_orientation, _clock, bullet_x_pos, bullet_y_pos, 0);
    _bullet_list->push_back(bullet);
    db<Spaceship>(TRC) << "[SPACESHIP] tamanho da lista" << _bullet_list->size() << "\n";
    db<Spaceship>(TRC) << "[SPACESHIP] SHOOTING!!! \n";
}

__END_API