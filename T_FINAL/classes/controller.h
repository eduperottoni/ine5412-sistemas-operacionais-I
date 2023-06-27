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
#include "../classes/game_config.h"

__BEGIN_API

class Controller {
public:

    Controller(Thread* player_thread, std::list<Thread*> enemy_threads, std::list<Enemy*>* enemy_objects, std::queue<Keyboard::Move>* player_queue, Player* player_object, std::list<Bullet*>* player_bullet_list, std::list<Bullet*>* enemies_bullet_list, Thread* collision_thread, Thread* window_thread) {
        _player_thread = player_thread;
        for (auto enemy_thread : enemy_threads) {
            _enemy_threads.push_back(enemy_thread);
        }
        _collision_thread = collision_thread;
        _player_queue = player_queue;
        _window_thread = window_thread;
        _enemies_bullet_list = enemies_bullet_list;
        _player_bullet_list = player_bullet_list;
        _enemy_objects = enemy_objects;
        _player_object = player_object;
        _game_config = &GameConfig::get_instance();
    };
    
    ~Controller();
    void run();
    std::queue<Keyboard::Move>* get_action_queue();
    std::queue<CollisionChecker::Collision*>* get_collision_queue();
    // void remove_from_index(int index_to_remove, std::list* list);
    void handle_bullet_enemy_collision(int id_bullet, int id_enemy);
    void handle_bullet_bullet_collision(int id_player_bullet, int id_enemy_bullet);
    void handle_bullet_player_collision(int id_player, int id_enemy);
    void handle_player_enemy_collision(int id_player, int id_enemy);


private:

    static std::queue<Keyboard::Move> _action_queue;
    static std::queue<Keyboard::Move>* _player_queue;
    static std::queue<CollisionChecker::Collision*> _collision_queue;
    static Thread* _player_thread;
    static Thread* _collision_thread;
    static Thread* _window_thread;
    static std::list<Thread*> _enemy_threads;
    static std::list<Enemy*>* _enemy_objects;
    static Player* _player_object;

    static std::list<Bullet*>* _player_bullet_list;
    static std::list<Bullet*>* _enemies_bullet_list;


    static void clear();

    static void reset();

    void _update_level();
    static void _resume_threads();
    static void _suspend_threads();

    static GameConfig* _game_config;

    static void _update_bullet_list(std::list<Bullet*>* bullet_list);
};


__END_API


#endif