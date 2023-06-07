#include "window.h"
#include "keyboard.h"
#include "src/lib/thread.h"

__USING_GAME

int main(void)
{
    Window window;

    window.run();

    //window_thread = new Thread(window.run());

    //Keyboard keyboard;

    //keyboard_thread = Thread(keyboard.run());
    return 0;
}
