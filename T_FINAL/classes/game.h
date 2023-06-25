#ifndef game_h
#define game_h

#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "../classes/window.h"
#include "../classes/player.h"
#include "../classes/keyboard.h"
#include "../classes/controller.h"
#include "../classes/clock.h"
#include "../classes/game_config.h"
#include "../classes/enemy.h"
#include "../classes/enemy_random.h"
#include "../classes/static_sprite.h"
#include "../classes/enemy_tracker.h"
#include <list>


__BEGIN_API

class Game
{
public:

    Game() {};
    ~Game();
    
    static void configure();

    static void run(void* name);
    static std::list<sf::Sprite*> get_enemies_sprites_list();

private:

    static Window* _window_obj;
    static Keyboard* _keyboard_obj;
    static Player* _player_obj;
    static Thread* _window_thread;
    static Thread* _player_thread;
    static Thread* _keyboard_thread;
    static Thread* _controller_thread;
    static Controller* _controller_obj;
    static Clock* _clock_obj;
    static list<Enemy*> _enemy_objects;
    static list<Thread*> _enemy_threads;

    static GameConfig* _game_config;

    static void _window_run();
    static void _keyboard_run();
    static void _player_run();
    static void _controller_run();
    static void _enemy_run(int i);

    static std::list<Bullet*> _bullet_list;
};


__END_API


#endif