#include "classes/window.h"
#include "classes/player.h"
#include "classes/window.h"

__BEGIN_API

Window::Window()
{
    db<Window>(TRC) << "[Debug] Construindo a janela e carregando as texturas \n";
    load_and_bind_textures();
}

void Window::draw_texture(unsigned int texture, int length, int height, float angle)
{
}

void Window::run()
{
    db<Window>(TRC) << "[Debug] Rodando a janela !\n";
    sf::RenderWindow window(sf::VideoMode(900, 560), "Brick Game");
    window.setFramerateLimit(30);

    //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
    //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
    window.setKeyRepeatEnabled(false);

    space_ship_sprite.setPosition(220, 365);

    while (window.isOpen())
    {
        window.clear();
        window.draw(maze_sprite);
        
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                 window.close();
                 break;
            
            // key pressed
            case sf::Event::KeyPressed:
                // // Player será movido para cima ou para baixo
                // _player->move();
                // // PLayer será movido para a esquerda ou para a direita
                // _player->rotate();
                
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    db<Window>(TRC) <<"[Debug] Tecla a esquerda \n";
                    space_ship_sprite.setTexture(space_ship_left);
                    space_ship_sprite.setPosition(space_ship_sprite.getPosition().x - 10, space_ship_sprite.getPosition().y);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    db<Window>(TRC) <<"[Debug] Tecla a direita \n";
                    space_ship_sprite.setTexture(space_ship_right);    
                    space_ship_sprite.setPosition(space_ship_sprite.getPosition().x + 10, space_ship_sprite.getPosition().y);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    db<Window>(TRC) <<"[Debug] Tecla para baixo \n";
                    space_ship_sprite.setTexture(space_ship_down);
                    space_ship_sprite.setPosition(space_ship_sprite.getPosition().x, space_ship_sprite.getPosition().y + 10);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    db<Window>(TRC) <<"[Debug] Tecla para cima \n";
                    space_ship_sprite.setTexture(space_ship_up);
                    space_ship_sprite.setPosition(space_ship_sprite.getPosition().x, space_ship_sprite.getPosition().y - 10);

                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    db<Window>(TRC) <<"[Debug] Tiro orientado \n";
                    // Chamda de método para direcionar o tiro
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    db<Window>(TRC) <<"[Debug] Jogo pausado !\n";
                    // Chamada de Pause

                }
                else
                    std::cout << "Keyboard pressed = " << event.key.code << std::endl;
                break;

                default:
                    break;
            
            }
        }
    
        window.draw(space_ship_sprite);
        
        // enemy_ship_sprite.setPosition(245, 150);
        // window.draw(enemy_ship_sprite);

        // shot_sprite.setPosition(204, 400);
        // window.draw(shot_sprite);
        
        window.display();
    }
    
}

void Window::load_and_bind_textures()
{
    // Bind map textures
    if(!maze_tex.loadFromFile("sprites/maze/screen.png")){
        db<Window>(INF) << "[Debug] Não foi possível obter o arquivo\n";
    }else{
        db<Window>(INF) << "[Debug] Desenhando a Arena\n";
    }
    maze_sprite.setTexture(maze_tex);
    maze_sprite.scale(1.5, 1.5);

    if(!shot_tex.loadFromFile("sprites/space_ships/shot.png")){
        db<Window>(INF) << "[Debug] Não foi possível obter o o arquivo\n";
    }else {
        db<Window>(INF) << "[Debug] Desenhando o tiro\n";
    };
    shot_sprite.setTexture(shot_tex);
    shot_sprite.scale(-0.5, -0.5);

    if(!space_ship_up.loadFromFile("sprites/space_ships/space_ship1.png")){
        db<Window>(INF) << "[Debug] Não foi possível obter o arquivo\n";
    }else {
        db<Window>(INF) << "[Debug] Desenhando a nave\n";
    };
    space_ship_sprite.setTexture(space_ship_up);
    space_ship_sprite.scale(0.85, 0.85);

    if(!space_ship_left.loadFromFile("sprites/space_ships/space_ship2.png")){
        db<Window>(INF) << "[Debug] Não foi possível obter o arquivo\n";
    }else {
        db<Window>(INF) << "[Debug] Desenhando a nave\n";
    };
    space_ship_sprite.setTexture(space_ship_up);
    space_ship_sprite.scale(0.85, 0.85);

    if(!space_ship_down.loadFromFile("sprites/space_ships/space_ship3.png")){
        db<Window>(INF) << "[Debug] Não foi possível obter o arquivo\n";
    }else {
        db<Window>(INF) << "[Debug] Desenhando a nave\n";
    };
    space_ship_sprite.setTexture(space_ship_up);
    space_ship_sprite.scale(0.85, 0.85);

    if(!space_ship_right.loadFromFile("sprites/space_ships/space_ship4.png")){
        db<Window>(INF) << "[Debug] Não foi possível obter o arquivo\n";
    }else {
        db<Window>(INF) << "[Debug] Desenhando a nave\n";
    };
    space_ship_sprite.setTexture(space_ship_up);
    space_ship_sprite.scale(0.85, 0.85);

    if(!enemy_ship_tex.loadFromFile("sprites/space_ships/enemy_space_ship1.png")){
        db<Window>(INF) << "[Debug] Não foi possível obter o arquivo\n";
    } else {
        db<Window>(INF) << "[Debug] Desenhando um inimigo\n";
    };
    enemy_ship_sprite.setTexture(enemy_ship_tex);
    enemy_ship_sprite.scale(0.85,0.85);
}

__END_API