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
public:
    static void run(void* name);
    static void window_run();
};

__END_API


#endif