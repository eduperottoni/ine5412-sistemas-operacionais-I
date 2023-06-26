#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "../src/lib/traits.h"
#include "../src/lib/list.h"
#include "keyboard.h"
#include "collision_checker.h"
#include <queue>
#include <list>
#include "../classes/enemy.h"
#include "../classes/player.h"

__BEGIN_API

class Controller {
public:
    enum State{
        READY,
        RUNNING,
        PAUSED,
        OVER
    };

    Controller(Thread* player_thread, std::list<Thread*> enemy_threads, std::list<Enemy*>* enemy_objects, std::queue<Keyboard::Move>* player_queue, Player* player_object, std::list<Bullet*>* player_bullet_list, std::list<Bullet*>* enemies_bullet_list) {
        _player_thread = player_thread;
        for (auto enemy_thread : enemy_threads) {
            _enemy_threads.push_back(enemy_thread);
        }
        _game_state = RUNNING;
        _player_queue = player_queue;
        _enemies_bullet_list = enemies_bullet_list;
        _player_bullet_list = player_bullet_list;
        _enemy_objects = enemy_objects;
        _player_object = player_object;
    };
    
    ~Controller();
    void run();
    std::queue<Keyboard::Move>* get_action_queue();
    

    //static State* get_state();

    //void set_state();

private:

    static std::queue<Keyboard::Move> _action_queue;
    static std::queue<Keyboard::Move>* _player_queue;
    static std::queue<CollisionChecker::Collision>* _collision_queue;
    static Thread* _player_thread;
    static std::list<Thread*> _enemy_threads;
    static State _game_state;
    static std::list<Enemy*>* _enemy_objects;
    static Player* _player_object;

    static std::list<Bullet*>* _player_bullet_list;
    static std::list<Bullet*>* _enemies_bullet_list;

    static void _update_bullet_list(std::list<Bullet*>* bullet_list);
    //List<Bullet*> _bullet_list;
};


__END_API


#endif