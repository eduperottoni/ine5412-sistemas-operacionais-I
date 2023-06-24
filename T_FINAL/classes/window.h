#ifndef WINDOW_H
#define WINDOW_H

#include "../src/lib/traits.h"
#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>
#include "../src/lib/traits.h"
#include "clock.h"
#include "static_sprite.h"
#include "bullet.h"
#include <list>

__BEGIN_API

class Window 
{
friend class Player;
public:
    Window(sf::Sprite* sprite, std::list<sf::Sprite*> enemies_sprites_list, std::list<Bullet*>* bullet_list, Clock* clock);
    ~Window();
    void run();

    void draw_texture(unsigned int texture, int length, int height, float angle);

    void pause();
    sf::RenderWindow* get_sf_window();

protected:
    void load_and_bind_textures();

private:
    static std::list<Bullet*>* _bullet_list;
    sf::Sprite* _player_sprite;
    sf::Sprite* _screen_sprite;
    static StaticSprite* _screen;
    static StaticSprite* _ready;
    static StaticSprite* _score;
    sf::Text _text;
    sf::Font _font;
    std::list<sf::Sprite*> _enemies_sprites_list;
    sf::RenderWindow _sf_window;

    Clock* _clock;


    // Maze Texture
    sf::Texture maze_tex;
    sf::Sprite maze_sprite;
    
    //Shot texture
    sf::Texture shot_tex;
    sf::Sprite shot_sprite;
    
    //Space ship texture
    sf::Texture space_ship_up;
    sf::Texture space_ship_down;
    sf::Texture space_ship_right;
    sf::Texture space_ship_left;
    sf::Sprite space_ship_sprite;

    //Enemy space ship texture
    sf::Texture enemy_ship_tex;
    sf::Sprite enemy_ship_sprite;
};

__END_API


#endif