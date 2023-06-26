#ifndef game_h
#define game_h

#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "../classes/window.h"
#include "../classes/player.h"
#include "../classes/keyboard.h"
#include "../classes/clock.h"
#include "../classes/game_config.h"
#include "../classes/enemy.h"
#include "../classes/enemy_random.h"
#include "../classes/static_sprite.h"
#include "../classes/enemy_tracker.h"
#include "../classes/collision_checker.h"
#include <list>


__BEGIN_API

class Controller;
class Game
{
public:
    enum Level{
        LEVEL_1,
        LEVEL_2,
        LEVEL_3
    };

    enum State{
        READY,
        RUNNING,
        PAUSED,
        OVER
    };

    Game() {
        _level = Level::LEVEL_1;
    };
    ~Game();



    static void run(void* name);
    static std::list<sf::Sprite*> get_enemies_sprites_list();
    static void set_level(Level level);
    static Level get_level();


private:

    static Window* _window_obj;
    static Keyboard* _keyboard_obj;
    static Player* _player_obj;
    static CollisionChecker* _collision_checker_obj;
    static Thread* _window_thread;
    static Thread* _player_thread;
    static Thread* _keyboard_thread;
    static Thread* _controller_thread;
    static Thread* _collision_checker_thread;
    static Controller* _controller_obj;
    static Clock* _clock_obj;
    static list<Enemy*> _enemy_objects;
    static list<Thread*> _enemy_threads;

    static GameConfig* _game_config;
    static Level _level;

    static void _window_run();
    static void _keyboard_run();
    static void _player_run();
    static void _controller_run();
    static void _enemy_run(int i);
    static void _collision_checker_run();
    static void _configure();

    static std::list<Bullet*> _player_bullet_list;
    static std::list<Bullet*> _enemies_bullet_list;
};


__END_API


#endif