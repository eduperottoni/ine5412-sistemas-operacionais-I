#include "classes/keyboard.h"
#include "classes/controller.h"
#include "classes/window.h"
#include "classes/player.h"

__BEGIN_API

Keyboard::Keyboard(Window* window, Controller* controller) {
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
        sf::Event event;
        while (_sf_window -> pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                _sf_window -> close();
                break;
            
            // key pressed
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    _action_queue -> push(Move::LEFT);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    _action_queue -> push(Move::RIGHT);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    _action_queue -> push(Move::DOWN);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    _action_queue -> push(Move::UP);

                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    _action_queue -> push(Move::SHOOT);
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    _action_queue -> push(Move::P);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    _action_queue -> push(Move::QUIT);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                    _action_queue -> push(Move::RESET);
                } else {
                    std::cout << "Keyboard pressed = " << event.key.code << std::endl;
                }
                break;
            default:
                break;
            }
        }
        Thread::yield();
    }
}

__END_API
