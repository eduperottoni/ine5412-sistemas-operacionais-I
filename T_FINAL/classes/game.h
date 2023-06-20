#ifndef game_h
#define game_h

#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "../classes/window.h"
#include "../classes/player.h"
#include "../classes/keyboard.h"
#include "../classes/controller.h"
#include "../classes/enemy.h"
__BEGIN_API

class Game
{
private:
    static Window* _window_obj;
    static Keyboard* _keyboard_obj;
    static Player* _player_obj;
    static Enemy* _enemy_obj;
    static Controller* _controller_obj;

    static Thread* _enemy_thread0;
    static Thread* _window_thread;
    static Thread* _player_thread;
    static Thread* _keyboard_thread;
    static Thread* _controller_thread;

    static void _window_run();
    static void _keyboard_run();
    static void _player_run();
    static void _controller_run();
    static void _enemy_run();


public:
    Game() {}
    ~Game();
    
    static void run(void* name);
};


__END_API


#endif