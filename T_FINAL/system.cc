#include "src/lib/system.h"

__BEGIN_API

void System::init(void (*main)(void *)) {
    db<System>(INF) << "[Debug] System::init() chamado\n";
    setvbuf (stdout, 0, _IONBF, 0);
    Thread::init(main);
}

__END_API