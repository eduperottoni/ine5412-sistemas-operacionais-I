#include "thread.h"

__BEGIN_API

// Inicializando os atributos estáticos da classe Thread
int Thread::_threads_identifier = 0;
int Thread::_active_threads = 0;
Thread* Thread::_running = nullptr;

int Thread::id(){
	return _id;
}

int Thread::switch_context(Thread * prev, Thread * next) {
    // Thread que está executando será a próxima
    _running = next;
    db<Thread>(INF) << "[Debug] Trocando contexto: Thread " + std::to_string(prev -> id()) + " -> Thread " + std::to_string(next -> id()) + "\n";
    // CPU::switch_context() já retorna int
    return CPU::switch_context(prev-> context(), next -> context());
}

void Thread::thread_exit (int exit_code) {
    delete _context;
    db<Thread>(INF) << "[Debug] Finalizando Thread " + std::to_string(_id) + "\n";
    --_active_threads;
}

__END_API