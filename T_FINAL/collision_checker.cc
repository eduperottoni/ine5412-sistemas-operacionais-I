#include "classes/collision_checker.h"

__BEGIN_API

void CollisionChecker::run(){
    while (true){
        db<CollisionChecker>(INF) << "[CollisionChecker] CollisionChecker dá oi!\n";
        Thread::yield();
    }
}

__END_API