#include "classes/sprite.h"

__BEGIN_API

sf::Texture Sprite::load_texture(const string& path)
{
    sf::Texture texture;
    texture.loadFromFile(path);
    return texture;
}

sf::Sprite* Sprite::get_sprite()
{
    return &_sprite;
}

Sprite::Sprite(float scale, int size, const map<Orientation, string>& paths, Orientation initial_orientation, int x, int y)
{
    for(const auto& item : paths){
        if (!_textures[item.first].loadFromFile(item.second)){
            throw std::invalid_argument("Erro no carregamento de texturas");
        }
    }
    _scale = scale;
    _sprite.setTexture(_textures.at(initial_orientation));
    _sprite.setPosition(x, y);
    _position = std::make_tuple(x, y);
    _sprite.scale(scale, scale);
    _current_orientation = initial_orientation;
    cout << "Sprite construído";
}

void Sprite::reset_position() {
    _sprite.setPosition(std::get<0>(_position), std::get<1>(_position));
}
__END_API

