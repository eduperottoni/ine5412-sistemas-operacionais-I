#include "classes/controller.h"

__BEGIN_API

std::queue<Keyboard::Move> Controller::_action_queue;


void Controller::run() {
    while (true) {
        if (!_action_queue.empty()) {
            Keyboard::Move move = _action_queue.front();
            _action_queue.pop();
            db<Controller>(TRC) << "[CONTROLLER] NOT EMPTY \n";
            switch (move) {
                case Keyboard::Move::EXIT:
                    db<Controller>(TRC) << "[CONTROLLER] EXIT \n";
                    break;
                case Keyboard::Move::SHOOT:
                    db<Controller>(TRC) << "[CONTROLLER] SHOOT \n";
                    break;
                case Keyboard::Move::PAUSE:
                    db<Controller>(TRC) << "[CONTROLLER] PAUSE \n";
                    break;
                case Keyboard::Move::UNPAUSE:
                    db<Controller>(TRC) << "[CONTROLLER] UNPAUSE \n";
                    break;
                }
            } else {
            db<Controller>(TRC) << "[CONTROLLER] EMPTY\n";
        }
        Thread::yield();
    }
}


Controller::~Controller() {
}

std::queue<Keyboard::Move>* Controller::get_action_queue(){
    db<Controller>(TRC) << "[CONTROLLER] Entrei no getter do _action_queue! \n";
    return &_action_queue;
}


__END_API
