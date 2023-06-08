#include "classes/keyboard.h"
#include "src/lib/thread.h"

__BEGIN_API

Keyboard::Keyboard() {

}

void Keyboard::read_key() {

}

void Keyboard::run()
{
    //while (window.isOpen()) {
        //read_key();
    Thread::yield();
    //}
}


__END_API
