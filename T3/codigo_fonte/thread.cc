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
    Thread *main_thread = new Thread((void (*) (void*)) main, (void*)"main");
    Thread *dispatcher = new Thread((void (*) (void *)) &Thread::dispatcher, (void*) NULL);
    _main = *main_thread;
    _dispatcher = *dispatcher;

    Thread *empty_thread = new Thread();
    empty_thread -> _context = new CPU::Context();

    _running = &_main;
    switch_context(empty_thread , &_main);
    delete empty_thread -> _context;
}

void Thread::dispatcher(){
    while(_active_threads > 2){
        db<Thread>(TRC) << "[Debug] Executando dispatcher\n";
        // Seleciona a próxima Thread a ser executada
        Thread* next_thread = _ready.remove()->object();
        // std::cout << "Thread" << next_thread -> _id << "selecionada da fila \n";
        // Muda estado da próxima Thread
        next_thread -> _state = State::RUNNING;
        // Troca estado de dispatcher
        _dispatcher._state = State::READY;
        // Troca contexto do dispatcher para a próxima thread
        _running = next_thread;
        switch_context(&_dispatcher, next_thread);
    }
    _dispatcher._state = State::FINISHING;
    switch_context(&_dispatcher, &_main);
}

int Thread::id(){
	return _id;
}

int Thread::switch_context(Thread * prev, Thread * next) {
    // Thread que está executando será a próxima
    _running = next;
    db<Thread>(INF) << "[Debug] Trocando contexto: Thread " << prev -> id() << " -> Thread " << next -> id() << "\n";
    // CPU::switch_context() já retorna int
    return CPU::switch_context(prev-> context(), next -> context());
}

void Thread::thread_exit (int exit_code) {
    delete _context;
    db<Thread>(INF) << "[Debug] Finalizando Thread " << _id << "\n";
    --_active_threads;
    Thread *empty_thread = new Thread();
    empty_thread -> _context = new CPU::Context();

    _running = &_dispatcher;
    switch_context(empty_thread , &_dispatcher);
}


void Thread::yield() {
    db<Thread>(TRC) << "[Debug] Execução de yield iniciada\n";
    // Acessar thread atual
    Thread *current_thread = _running;
    // Atualizar prioridade da thread atual (se não for main e se não estiver finalizando)
    if (current_thread -> id() != _main.id() && current_thread -> _state != State::FINISHING) {
        db<Thread>(TRC) << "[Debug] Atualizando prioridade da thread " << current_thread -> id() << "\n";
        // Atualiza prioridade da thread que chamou
        int new_priority = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        current_thread -> _link.rank(new_priority);
        // Muda o estado da thread atual
        current_thread -> _state = State::READY;
        // Reinsere a Thread  atual na fila
        _ready.insert(&current_thread->_link);
    }
    // Chama o dispatcher -> selecionará uma thread para execução
    _dispatcher._state = State::RUNNING;
    _running = &_dispatcher;
    switch_context(current_thread, &_dispatcher);
}

__END_API