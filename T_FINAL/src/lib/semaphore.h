#ifndef semaphore_h
#define semaphore_h

#include "cpu.h"
#include "thread.h"
#include "traits.h"
#include "debug.h"
#include "list.h"

__BEGIN_API

class Semaphore
{
public:
    typedef Ordered_List<Thread> Sleeping_Queue;

    Semaphore(int v = 1);
    ~Semaphore();

    void p();
    void v();
private:
    // Atomic operations
    int finc(volatile int & number);
    int fdec(volatile int & number);

    // Thread operations
    void sleep();
    void wakeup();
    void wakeup_all();

private:
    //DECLARAÇÃO DOS ATRIBUTOS DO SEMÁFORO
    // Fila do semáforo
    Sleeping_Queue _sleeping;
    // Contador do semáforo
    int _counter;
};

__END_API

#endif

