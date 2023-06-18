#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "../src/lib/traits.h"
#include "keyboard.h"
#include <queue>

__BEGIN_API


class Controller {
private:
    static std::queue<Keyboard::Move> _action_queue;

public:
    Controller() {};
    ~Controller();
    void run();
    std::queue<Keyboard::Move>* get_action_queue();
};


__END_API


#endif