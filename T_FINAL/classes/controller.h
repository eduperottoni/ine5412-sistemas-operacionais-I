#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "../src/lib/traits.h"
#include "keyboard.h"
#include <queue>
#include <list>

__BEGIN_API

class Controller {
public:
    enum State{
        READY,
        RUNNING,
        PAUSED,
        OVER
    };

    Controller(Thread* player_thread, std::list<Thread*> enemy_threads, std::queue<Keyboard::Move>* player_queue) {
        _player_thread = player_thread;
        for (auto enemy_thread : enemy_threads) {
            _enemy_threads.push_back(enemy_thread);
        }
        _game_state = RUNNING;
        _player_queue = player_queue;
    };
    
    ~Controller();
    void run();
    std::queue<Keyboard::Move>* get_action_queue();
    

    //static State* get_state();

    //void set_state();

private:

    static std::queue<Keyboard::Move> _action_queue;
    static std::queue<Keyboard::Move>* _player_queue;
    Thread* _player_thread;
    std::list<Thread*> _enemy_threads;
    static State _game_state;

};


__END_API


#endif