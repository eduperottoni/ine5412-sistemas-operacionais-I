#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include "list.h"
#include <ctime> 
#include <chrono>

__BEGIN_API

class Thread
{
protected:
    typedef CPU::Context Context;
public:

    typedef Ordered_List<Thread> Ready_Queue;
    typedef Ordered_List<Thread> Blocked_List;

    // Thread State
    enum State {
        RUNNING,
        READY,
        FINISHING,
        BLOCKED,
        WAITING
    };

    /*
     * Construtor vazio. Necessário para inicialização, mas sem importância para a execução das Threads.
     */ 
    Thread() { }

    /*
     * Cria uma Thread passando um ponteiro para a função a ser executada
     * e os parâmetros passados para a função, que podem variar.
     * Cria o contexto da Thread.
     * PS: devido ao template, este método deve ser implementado neste mesmo arquivo .h
     */ 
    template<typename ... Tn>
    Thread(void (* entry)(Tn ...), Tn ... an);

    /*
     * Retorna a Thread que está em execução.
     */ 
    static Thread * running() { return _running; }

    /*
     * Método para trocar o contexto entre duas thread, a anterior (prev)
     * e a próxima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno é negativo se houve erro, ou zero.
     */ 
    static int switch_context(Thread * prev, Thread * next);

    /*
     * Termina a thread.
     * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar à main. 
     */  
    void thread_exit (int exit_code);

    /*
     * Retorna o ID da thread.
     */ 
    int id();

    /*
     * NOVO MÉTODO DESTE TRABALHO.
     * Daspachante (disptacher) de threads. 
     * Executa enquanto houverem threads do usuário.
     * Chama o escalonador para definir a próxima tarefa a ser executada.
     */
    static void dispatcher(); 

    /*
     * NOVO MÉTODO DESTE TRABALHO.
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher.
     */ 
    static void init(void (*main)(void *));

    /*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
     * para ser executada.
     */
    static void yield(); 

    /*
     * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
     */ 
    ~Thread();

    /*
     * Retorna o tempo atual 
    */
    static unsigned int get_time();

    /*
     * Qualquer outro método que você achar necessário para a solução.
     */
    Context* context() { return _context; }

    /*
     * Faz o join da thread 
     */
    int join();

    /*
     * Retorna a trhead para a fila de prontos
    */
    void resume();

    /*
     *  Suspende a thread
    */
    void suspend();

    /*
     * Sets the thread's state as WAITING 
    */
    void sleep();

    /**
     * Sets the thread's state as READY
    */
    void wakeup();

private:
    int _id;
    Context * volatile _context;
    static Thread * _running;
    static Thread _main;
    static CPU::Context _main_context;
    static Thread _dispatcher;
    static Ready_Queue _ready;
    static Blocked_List _blocked_list;

    Thread * _blocked_thread;
    Ready_Queue::Element _link;

    volatile State _state;
    int _exit_code;

    /*
    * Faz o incremento de ID's para atribuição de IDs únicos para as threads
    */
    static int _threads_identifier;

};

template<typename ... Tn>
inline Thread::Thread(void (* entry)(Tn ...), Tn ... an)
{
    /* inicialização de _link */
    db<Thread>(TRC) << "[Debug] Thread " + std::to_string(_threads_identifier) + " criada\n";
    // atribui id para as threads
    _id = _threads_identifier++;
    // cria o contexto para a thread
    _context = new CPU::Context(entry, an...);
    // cria o elemento compatível com a lista
    unsigned int priority = get_time();
    _link = Ready_Queue::Element(this, priority);
    // _blocked_link = Blocked_List::Element(this, priority);
    _blocked_thread = nullptr;
    // seta estado inicial da thread
    _state = State::READY;
    // insere thread na fila de prontos (exceto main e dispatcher)
    if (_id != 0 && _id != 1) {
        // std::cout << "Inserindo thread " << _id << "na fila"; 
        _ready.insert(&_link);
    }
}


__END_API

#endif
