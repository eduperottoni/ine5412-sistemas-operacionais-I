#include "thread.h"

__BEGIN_API

// Thread id: Feito
int Thread::id(){
	return _id;
}

int Thread::switch_context(Thread * prev, Thread * next) {
    // Thread que está executando será a próxima
    _running = next;
    return CPU::switch_context(prev-> context(), next -> context());
}

void Thread::thread_exit (int exit_code) {
    delete _context;
    --_thread_counter;
}

__END_API