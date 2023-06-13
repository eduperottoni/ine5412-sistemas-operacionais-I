#ifndef game_h
#define game_h

#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "../classes/window.h"
#include "../classes/player.h"
__BEGIN_API

class Game
{
private:
    static Thread* _window_thread;
    static Window* _window_obj;
    static Thread* _player;

    static void window_run(){
        db<Game>(INF) << "[Debug] Instanciando uma nova janela!\n";
        _window_obj = new Window();
        db<Game>(INF) << "[Debug] Chamando método run da janela!\n";
        _window_obj -> run();
    }
public:
    Game() {}
    ~Game() {}
    
    static void run(void* name) {
        db<Game>(INF) << "[Debug] Inciando a thread da janela\n";
        _window_thread = new Thread(window_run);
        db<Game>(INF) << "[Debug] Chamando join\n";
        _window_thread -> join();
        // realizar chamada da Thread Player
    }  
};


__END_API


#endif