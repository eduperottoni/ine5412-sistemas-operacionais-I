#ifndef game_h
#define game_h

#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "../classes/window.h"

__BEGIN_API

class Game
{
private:
    static Thread* _window_thread;
    static Window* _window_obj;
    static void window_run(){
        std::cout << "Aqui 4" << std::endl;
        _window_obj = new Window();
        std::cout << "Aqui 5" << std::endl;
        _window_obj -> run();   
    }
public:
    Game() {}
    ~Game() {}
    
    static void run(void* name) {
        std::cout << "Aqui 2" << std::endl;
        _window_thread = new Thread(window_run);
        std::cout << "Aqui 3" << std::endl;
        _window_thread -> join();
    }  
};


__END_API


#endif