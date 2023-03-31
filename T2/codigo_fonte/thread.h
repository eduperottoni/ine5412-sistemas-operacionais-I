#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "traits.h"
#include "debug.h"

__BEGIN_API

class Thread
{
protected:
    typedef CPU::Context Context;

public:
    Thread() {}
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
    * Retorna contexto da thread chamadora
    */
    Context* context() { return _context; }

private:
    int _id;
    Context * volatile _context;
    static Thread * _running;

    /*
     * Conta quantas threads estão ativas
     */ 
    static int _active_threads;

    /*
    * Faz o incremento de ID's para atribuição de IDs únicos para as threads
    */
    static int _threads_identifier;
};

template<typename ... Tn>
Thread::Thread(void (* entry)(Tn ...), Tn ... an) {
    db<Thread>(TRC) << "[Debug] Thread " + std::to_string(_threads_identifier) + " criada\n";
    _context = new CPU::Context(entry, an...);
    _id = _threads_identifier++;
    _active_threads++;
}

__END_API

#endif
