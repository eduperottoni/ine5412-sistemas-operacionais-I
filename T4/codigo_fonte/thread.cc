#include "thread.h"

__BEGIN_API

// Inicializando os atributos estáticos da classe Thread
int Thread::_threads_identifier = 0;
Thread* Thread::_running = nullptr;
Thread::Ready_Queue Thread::_ready;
Thread Thread::_dispatcher;
Thread Thread::_main;
CPU::Context Thread::_main_context;

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

    _main._state = State::RUNNING;
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
        next_thread -> _state = State::RUNNING;
        // Troca estado de dispatcher
        _dispatcher._state = State::READY;
        // Troca contexto do dispatcher para a próxima thread
        _running = next_thread;
        switch_context(&_dispatcher, next_thread);
    }
    // delete _empty_thread;
    _dispatcher._state = State::FINISHING;
    _main._state = State::RUNNING;
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
    db<Thread>(INF) << "[Debug] Finalizando Thread " << _id << "\n";
    
    _exit_code = _id;
    _state = State::FINISHING;
    // Inicializa o exit_code
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
    if (current_thread -> id() != _main.id() && current_thread -> _state != State::FINISHING && current_thread -> _state != State::BLOCKED) {
        db<Thread>(TRC) << "[Debug] Atualizando prioridade da thread " << current_thread -> id() << "\n";
        // Atualiza prioridade da threead que chamou
        // int new_priority = ++_tempo;
        unsigned int new_priority = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
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

int Thread::join() {
    // Chamar o suspend() da thread atual (running)
    if (_state != State::FINISHING){
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
    _blocked.insert(&_running -> _blocked_link);
    // seta estado da thread como blocked (running)
    _running -> _state = State::BLOCKED;
}

void Thread::resume() {
    // Setar estado para pronto
    _state = State::READY;
    // Iserir na fila de prontos
    _ready.insert(&_link);
}
__END_API