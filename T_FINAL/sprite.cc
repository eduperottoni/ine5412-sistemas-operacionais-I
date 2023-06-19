#include "classes/sprite.h"

__BEGIN_API

sf::Texture Sprite::load_texture(const string& path)
{
    sf::Texture texture;
    texture.loadFromFile(path);
    return texture;
}

__END_API

