#include "window.h"
#include "player.h"
#include <list>

__BEGIN_GAME

Window::Window()
{
    load_and_bind_textures();
}

void Window::draw_texture(unsigned int texture, int length, int height, float angle)
{
}

void Window::run()
{
    sf::RenderWindow window(sf::VideoMode(900, 560), "SFML works!");

    window.setFramerateLimit(60);
    
    //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
    //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
    window.setKeyRepeatEnabled(false);

    space_ship_sprite.setPosition(220, 365);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                 window.close();
                 break;
            
            // key pressed
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    space_ship_sprite.setTexture(space_ship_left);
                    std::cout << "Keyboard esquerda!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    space_ship_sprite.setTexture(space_ship_right);
                    std::cout << "Keyboard direita!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    space_ship_sprite.setTexture(space_ship_down);
                    std::cout << "Keyboard para baixo!" << std::endl;
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    space_ship_sprite.setTexture(space_ship_up);
                    std::cout << "Keyboard para cima!" << std::endl;
                } else
                    std::cout << "Keyboard pressed = " << event.key.code << std::endl;
                break;
            default:
                break;
            }    
        }

        window.clear();
        window.draw(maze_sprite);
        
        
        window.draw(space_ship_sprite);
        space_ship_sprite.setPosition(space_ship_sprite.getPosition().x - 1, space_ship_sprite.getPosition().y - 1);
        
        enemy_ship_sprite.setPosition(245, 150);
        window.draw(enemy_ship_sprite);

        shot_sprite.setPosition(204, 400);
        window.draw(shot_sprite);
        
        window.display();
    }
}

void Window::load_and_bind_textures()
{
    // Bind map textures
    maze_tex.loadFromFile("src/images/screen/screen.png");
    maze_sprite.setTexture(maze_tex);
    maze_sprite.scale(1.5, 1.5);

    shot_tex.loadFromFile("src/images/space_ships/shot.png");
    shot_sprite.setTexture(shot_tex);
    shot_sprite.scale(0.5, 0.5);

    space_ship_up.loadFromFile("src/images/space_ships/space_ship1.png");
    space_ship_sprite.setTexture(space_ship_up);
    space_ship_sprite.scale(0.75, 0.75);

    space_ship_left.loadFromFile("src/images/space_ships/space_ship2.png");

    space_ship_down.loadFromFile("src/images/space_ships/space_ship3.png");

    space_ship_right.loadFromFile("src/images/space_ships/space_ship4.png");

    enemy_ship_tex.loadFromFile("src/images/space_ships/enemy_space_ship1.png");
    enemy_ship_sprite.setTexture(enemy_ship_tex);
    enemy_ship_sprite.scale(0.5, 0.5);

    // Player* player = new Player()
}

__END_GAME
