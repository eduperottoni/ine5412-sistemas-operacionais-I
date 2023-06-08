#include "src/lib/thread.h"

__BEGIN_API

// Inicializando os atributos estáticos da classe Thread
int Thread::_threads_identifier = 0;
Thread* Thread::_running = nullptr;
Thread::Ready_Queue Thread::_ready;
Thread::Blocked_List Thread::_blocked_list;
Thread Thread::_dispatcher;
Thread Thread::_main;
CPU::Context Thread::_main_context;

Thread::~Thread(){
    delete _context;
    _context = nullptr;
}

unsigned int Thread::get_time(){
    unsigned int time = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
    return time;
}

void Thread::init(void (*main)(void *)) {
    db<Thread>(INF) << "[Debug] Thread::init() chamado\n";
    new (&_main) Thread(main, (void *) "main");
    new (&_dispatcher) Thread((void (*) (void*)) &Thread::dispatcher, (void*) NULL);
    // Using main_context to switch_context()
    new (&_main_context) CPU::Context();

    _main._state = RUNNING;
    _running = &_main;

    CPU::switch_context(&_main_context, _main._context);
}

void Thread::dispatcher(){
    db<Thread>(TRC) << "[Debug] Executando dispatcher\n";
    while(!_ready.empty()){
        // Seleciona a próxima Thread a ser executada
        Thread* next_thread = _ready.remove()->object();
        // Muda estado da próxima Thread
        next_thread -> _state = RUNNING;
        // Troca estado de dispatcher
        _dispatcher._state = READY;
        // Troca contexto do dispatcher para a próxima thread
        _running = next_thread;
        switch_context(&_dispatcher, next_thread);
    }
    // delete _empty_thread;
    _dispatcher._state = FINISHING;
    _main._state = RUNNING;
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
    return CPU::switch_context(prev -> context(), next -> context());
}

void Thread::thread_exit (int exit_code) {
    // Inicializa o exit_code
    _exit_code = _id;
    // Seta estado como finalizando
    _state = State::FINISHING;
    // Chama resume da thread que está esperando por seu final
    if (_blocked_thread != nullptr) _blocked_thread -> resume();

    db<Thread>(INF) << "[Debug] Finalizando Thread " << _id << "com exit_code = " << _exit_code << "\n";
    // Sede o processador
    yield();
}

void Thread::yield() {
    db<Thread>(TRC) << "[Debug] Execução de yield iniciada para a Thread " << _running -> id() << "\n";
    // Acessar thread atual
    Thread *current_thread = _running;
    // Atualizar prioridade da thread atual (se não for main e se não estiver finalizando)
    if (current_thread -> id() != _main.id() && current_thread -> _state != FINISHING && current_thread -> _state != BLOCKED && current_thread -> _state != WAITING) {
        db<Thread>(TRC) << "[Debug] Atualizando prioridade da thread " << current_thread -> id() << "\n";
        // Atualiza prioridade da thread que chamou
        unsigned int new_priority = get_time();
        current_thread -> _link.rank(new_priority);
        // Muda o estado da thread atual
        current_thread -> _state = READY;
        // Reinsere a Thread  atual na fila
        _ready.insert(&current_thread->_link);
    }
    // Chama o dispatcher -> selecionará uma thread para execução
    db<Thread>(TRC) << "[Debug] Thread que está chamando a dispatcher " << current_thread -> id() << "\n";
    _dispatcher._state = RUNNING;
    _running = &_dispatcher;
    switch_context(current_thread, &_dispatcher);
}

int Thread::join() {
    db<Thread>(TRC) << "[DEBUG] Join called to Thread " << _id << "\n";

    if (_state != State::FINISHING){
        _blocked_thread = _running;
        _running -> suspend();
    }
    // Retorna o atributo _exit_code da thread chamadora do join
    return _exit_code;
}

void Thread::suspend() {
    db<Thread>(TRC) << "[DEBUG] Suspending thread " << _id << "\n";

    // Se a thread a ser suspensa não está em execução
    if (_running != this){
        // Tira da fila global de prontos
        _ready.remove(&_link);
    }

    // Seta estado da thread como blocked
    _state = State::BLOCKED;
    // Coloca na fila global de bloqueados
    unsigned int new_priority = get_time();
    _link.rank(new_priority);
    _blocked_list.insert(&_link);
    
    // Join foi chamado
    if(_running == this){
        yield();
    }
}

void Thread::resume() {
    db<Thread>(TRC) << "[DEBUG] Resuming thread " << _id << "\n";
    // Tira da fila global de bloqueados
    _blocked_list.remove(&_link);
    // Seta estado para pronto
    _state = State::READY;
    // Insere na fila de prontos
    _ready.insert(&_link);
}

void Thread::sleep() {
    db<Thread>(TRC) << "[DEBUG] Thread " << _id << " sleeping" << "\n";
    // Seta estado como WAITING e sede o processador
    _state = State::WAITING;
    yield();
}

void Thread::wakeup() {
    // Seta estado como READY e insere na lista de prontos
    db<Thread>(TRC) << "[DEBUG] Waking up Thread " << _id << "\n";
    _state = State::READY;
    _ready.insert(&_link);
    yield();
}

__END_API