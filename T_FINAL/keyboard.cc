#include "classes/keyboard.h"
#include "classes/controller.h"
#include "classes/window.h"
#include "classes/player.h"

__BEGIN_API

Keyboard::Keyboard(Window* window, Controller* controller) {
    db<Keyboard>(INF) << "[Keyboard] Construtor do teclado!\n";

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
        db<Keyboard>(INF) << "[Keyboard] Ponteiro para Window nulo!\n";
    }
}

void Keyboard::read_key() {

}

void Keyboard::run()
{
    while (_sf_window->isOpen()) {
        db<Keyboard>(TRC) <<"[Keyboard] ENTRANDO NA THREAD DO TECLADO \n";
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
                    _action_queue -> push(Move::LEFT);
                    db<Keyboard>(TRC) <<"[Keyboard] Tecla a esquerda \n";
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    _action_queue -> push(Move::RIGHT);
                    db<Keyboard>(TRC) <<"[Keyboard] Tecla a direita \n";
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    _action_queue -> push(Move::DOWN);
                    db<Keyboard>(TRC) <<"[Keyboard] Tecla para baixo \n";
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    _action_queue -> push(Move::UP);
                    db<Keyboard>(TRC) <<"[Keyboard] Tecla para cima \n";

                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    _action_queue -> push(Move::SHOOT);
                    db<Keyboard>(TRC) <<"[Keyboard] Tiro orientado \n";
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    _action_queue -> push(Move::P);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    db<Keyboard>(TRC) <<"[Keyboard] Q \n";
                    _action_queue -> push(Move::QUIT);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                    db<Keyboard>(TRC) <<"[Keyboard] RESET \n";
                    _action_queue -> push(Move::RESET);
                } else {
                    std::cout << "Keyboard pressed = " << event.key.code << std::endl;
                }
                break;
            default:
                break;
            }
        }
        db<Keyboard>(TRC) <<"[Keyboard] SAINDO DA THREAD TECLADO \n";
        Thread::yield();
    }
}


__END_API
