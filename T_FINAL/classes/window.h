#ifndef WINDOW_H
#define WINDOW_H

#include "../src/lib/traits.h"
#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>
#include "../src/lib/traits.h"
#include "clock.h"

__BEGIN_API

class Window 
{
friend class Player;
public:
    Window(sf::Sprite* sprite, Clock* clock);
    ~Window();
    void run();

    void draw_texture(unsigned int texture, int length, int height, float angle);

    void pause();

    sf::Vector2u getWindowSize(const sf::RenderWindow& window) {
        return window.getSize();
    }
    
    sf::RenderWindow* get_sf_window();

protected:
    void load_and_bind_textures();

private:
    sf::Sprite* _player_sprite;
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
    sf::Texture enemy_ship_down;
    sf::Texture enemy_ship_right;
    sf::Texture enemy_ship_left;
    sf::Texture enemy_ship_up;
    sf::Sprite enemy_ship_sprite;
};

__END_API


#endif