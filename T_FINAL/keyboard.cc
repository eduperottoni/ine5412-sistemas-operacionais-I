#include "classes/keyboard.h"
#include "classes/controller.h"
#include "classes/window.h"
#include "classes/player.h"

__BEGIN_API

Keyboard::Keyboard(Window* window, Controller* controller, Player* player) {
    db<Keyboard>(INF) << "[Keyboard] Construtor do teclado!\n";
    
    // _sf_window = window -> get_sf_window();
    if (controller != nullptr) {
        _action_queue = (controller->get_action_queue());
        db<Keyboard>(INF) << "[Keyboard] _action_queue setado!\n";
    } else {
        db<Keyboard>(INF) << "[Keyboard] Ponteiro para Queue nulo!\n";
    }
    if (window != nullptr) {
        _sf_window = (window->get_sf_window());
        db<Keyboard>(INF) << "[Keyboard] _sf_window setado!\n";
    } else {
        // Handle the case when the window pointer is null
        db<Keyboard>(INF) << "[Keyboard] Ponteiro para Window nulo!\n";
    }
    if (player != nullptr) {
        _player_queue = (player -> get_move_queue());
        db<Keyboard>(INF) << "[Keyboard] _player_queue setado!\n";
    } else {
        db<Keyboard>(INF) << "[Keyboard] Ponteiro para _player_queue nulo!\n";
    }
}

void Keyboard::read_key() {

}

void Keyboard::run()
{
    while (_sf_window->isOpen()) {
        sf::Event event;
        db<Keyboard>(INF) << "[Keyboard] Entrei no run!\n";
        while (_sf_window -> pollEvent(event)) {
            db<Keyboard>(INF) << "[Keyboard] Entrei no loop!\n";
            switch (event.type) {
            case sf::Event::Closed:
                _sf_window -> close();
                break;
            
            // key pressed
            case sf::Event::KeyPressed:
                // // Player será movido para cima ou para baixo
                // _player->move();
                // // PLayer será movido para a esquerda ou para a direita
                // _player->rotate();
                
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    // Encapsulamento de funções, não funcional
                    // _player->move("Left");
                    _player_queue -> push(Move::LEFT);
                    db<Keyboard>(TRC) <<"[Window] Tecla a esquerda \n";
                    // space_ship_sprite.setTexture(space_ship_left);
                    // space_ship_sprite.setPosition(space_ship_sprite.getPosition().x - 10, space_ship_sprite.getPosition().y);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    // _player->move("Right");
                    // fila.push(KeyAction::RIGHT)
                    _player_queue -> push(Move::RIGHT);
                    db<Keyboard>(TRC) <<"[Window] Tecla a direita \n";
                    // space_ship_sprite.setTexture(space_ship_right);    
                    // space_ship_sprite.setPosition(space_ship_sprite.getPosition().x + 10, space_ship_sprite.getPosition().y);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    // _player->rotate("Down");
                    _player_queue -> push(Move::DOWN);
                    db<Keyboard>(TRC) <<"[Window] Tecla para baixo \n";
                    // space_ship_sprite.setTexture(space_ship_down);
                    // space_ship_sprite.setPosition(space_ship_sprite.getPosition().x, space_ship_sprite.getPosition().y + 10);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    // _player->rotate("Up");
                    _player_queue -> push(Move::UP);
                    db<Keyboard>(TRC) <<"[Window] Tecla para cima \n";
                    // space_ship_sprite.setTexture(space_ship_up);
                    // space_ship_sprite.setPosition(space_ship_sprite.getPosition().x, space_ship_sprite.getPosition().y - 10);

                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    _player_queue -> push(Move::SHOOT);
                    db<Keyboard>(TRC) <<"[Window] Tiro orientado \n";
                    // Chamar o Tiro aqui
                    // shot_sprite.setTexture(shot_tex);
                    // shot_sprite.setPosition(space_ship_sprite.getPosition().x + 10, space_ship_sprite.getPosition().y + 10);
                    // Chamada de método para direcionar o tiro
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    _action_queue -> push(Move::EXIT);
                    db<Keyboard>(TRC) <<"[Window] Jogo pausado !\n";
                    // Chamada de Pause
                    // Botando todas as Threads na fila de suspensos
                    
                }
                else
                    std::cout << "Keyboard pressed = " << event.key.code << std::endl;
                break;

                default:
                    break;
            }
        }
        Thread::yield();
    }
}


__END_API