#include "classes/window.h"
#include "keyboard.h"
#include "src/lib/system.h"
#include "src/lib/thread.h"
#include "classes/game.h"

__USING_API


int main(void)
{
    System::init(&Game::run);
    return 0;

    // Keyboard keyboard;

    // keyboard.run();

    //window_thread = new Thread(window.run());

    //Keyboard keyboard;

    //keyboard_thread = Thread(keyboard.run());
    return 0;
}
