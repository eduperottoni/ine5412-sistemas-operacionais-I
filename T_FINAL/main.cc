#include "classes/window.h"
#include "classes/keyboard.h"
#include "src/lib/system.h"
#include "src/lib/thread.h"
#include "classes/game.h"

__USING_API


int main(void)
{
    System::init(&Game::run);
    return 0;
}
