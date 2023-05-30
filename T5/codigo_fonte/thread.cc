#include "thread.h"

__BEGIN_API

// Inicializando os atributos estáticos da classe Thread
int Thread::_threads_identifier = 0;
Thread* Thread::_running = nullptr;
Thread::Ready_Queue Thread::_ready;
Thread Thread::_dispatcher;
Thread Thread::_main;
CPU::Context Thread::_main_context;
Thread::Ready_Queue Thread::_blocked;

Thread::~Thread(){
    delete _context;
}

void Thread::init(void (*main)(void *)) {
    db<Thread>(INF) << "[Debug] Thread::init() chamado\n";
    // Thread *main_thread = new Thread((void (*) (void*)) main, (void*)"main");
    new (&_main) Thread(main, (void *) "main");
    // Thread *dispatcher = new Thread((void (*) (void *)) &Thread::dispatcher, (void*) NULL);
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
        // std::cout << "Thread" << next_thread -> _id << "selecionada da fila \n";
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
    Thread::_exit_code = exit_code;
    _state = FINISHING;
    // Inicializa o exit_code

    db<Thread>(INF) << "[Debug] Finalizando Thread " << _id << "com exit_code = " << _exit_code << "\n";
    while (!_blocked.empty()) {
        _blocked.remove() -> object() -> resume();
    }
    yield();
}

void Thread::yield() {
    db<Thread>(TRC) << "[Debug] Execução de yield iniciada para a Thread\n";
    // Acessar thread atual
    Thread *current_thread = _running;
    // Atualizar prioridade da thread atual (se não for main e se não estiver finalizando)
    if (current_thread -> id() != _main.id() && current_thread -> _state != FINISHING && current_thread -> _state != BLOCKED && current_thread -> _state != WAITING) {
        db<Thread>(TRC) << "[Debug] Atualizando prioridade da thread " << current_thread -> id() << "\n";
        // Atualiza prioridade da thread que chamou
        unsigned int new_priority = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
        current_thread -> _ready_link.rank(new_priority);
        // Muda o estado da thread atual
        current_thread -> _state = READY;
        // Reinsere a Thread  atual na fila
        _ready.insert(&current_thread->_ready_link);
    }
    // Chama o dispatcher -> selecionará uma thread para execução
    db<Thread>(TRC) << "[Debug] Thread que está chamando a dispatcher " << current_thread -> id() << "\n";
    _dispatcher._state = RUNNING;
    _running = &_dispatcher;
    switch_context(current_thread, &_dispatcher);
}

int Thread::join() {
    db<Thread>(TRC) << "[Debug] Atualizando prioridade da thread " << this->id() << "\n";
    // this->suspend();
    // Chamar o suspend() da thread atual (running)
    if (_state != FINISHING){
        suspend();
        // Thread que está rodando chama yield() running -> yield | yield()
        yield();
        // Retorna o atributo _exit_code da thread chamadora do join
    }
    return _exit_code;
}

void Thread::suspend() {
    // coloca thread na fila de bloqueadas (running)
    unsigned int new_priority = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
    _running -> _blocked_link.rank(new_priority);
    // seta estado da thread como blocked (running)
    _running -> _state = BLOCKED;
    _blocked.insert(&_running -> _blocked_link);
}

void Thread::resume() {
    // Setar estado para pronto
    _state = READY;
    // Iserir na fila de prontos
    _ready.insert(&_ready_link);
}

void Thread::sleep() {
    _state = WAITING;
    yield();
}

void Thread::wakeup() {
    _state = READY;
    _ready.insert(&_ready_link);
    // chamada de yield para obter a nova prioridade da thread na fila
    yield();
}

// Semaphore::Sleeping_Queue::Element Thread::sleeping_link(){
//     return _sleeping_link;
// }
__END_API