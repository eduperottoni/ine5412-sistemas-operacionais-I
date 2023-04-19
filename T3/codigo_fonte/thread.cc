#include "thread.h"

__BEGIN_API

// Inicializando os atributos estáticos da classe Thread
int Thread::_threads_identifier = 0;
int Thread::_active_threads = 0;
Thread* Thread::_running = nullptr;
Thread::Ready_Queue Thread::_ready;
Thread Thread::_dispatcher;
Thread Thread::_main;
CPU::Context _main_context;

Thread::~Thread(){

}

void Thread::init(void (*main)(void *)) {
    db<Thread>(INF) << "[Debug] Thread::init() chamado\n";
    Thread *main_thread = new Thread((void (*) (char*)) main, (char*)"main");
    Thread *dispatcher = new Thread((void (*) (void *)) &Thread::dispatcher, (void*) NULL);
    _main = *main_thread;
    _dispatcher = *dispatcher;

    Thread *empty_thread = new Thread();

    switch_context(empty_thread , &_main);
}

void Thread::dispatcher(){
    db<Thread>(TRC) << "[Debug] Dispatcher chamado";
    // Seleciona a próxima Thread a ser executada
    // Muda estado da próxima Thread
    // Troca contexto do dispatcher para a próxima thread
    
    while(_active_threads > 2){

    }
}

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


void Thread::yield() {
    // Acessar thread atual
    // Atualizar prioridade da thread atual
    // Muda o estado da thread atual
    // Reinsere a Thread atual na fila
    // Chama o dispatcher
}

__END_API