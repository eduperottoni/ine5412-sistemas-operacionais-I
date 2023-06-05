#ifndef main_class_h
#define main_class_h

#include <iostream>
#include "cpu.h"
#include "traits.h"
#include "thread.h"
#include "semaphore.h"
#include "game.h"

__BEGIN_API

class Main
{
public:
    Main() {}

        static void run(void * name);
};

__END_API

#endif
