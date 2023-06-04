#include "semaphore.h"
#include "thread.h"

__BEGIN_API

Semaphore::Semaphore(int v){
    _counter = v;
}

Semaphore::~Semaphore(){
    // acorda todas as threads na deleção do Semáforo
    if (!_sleeping.empty()) wakeup_all();
}

void Semaphore::p() {
    db<Semaphore>(TRC) << "[DEBUG] Semaphore counter before P() = " << _counter << "\n";
    
    if (fdec(_counter) < 1) sleep();
}

void Semaphore::v() {
    if (finc(_counter) < 0) wakeup();
    
    db<Semaphore>(TRC) << "[DEBUG] Semaphore counter after V() = " << _counter << "\n";
}

void Semaphore::sleep() {

    Thread* _current = Thread::running();
    db<Semaphore>(TRC) << "[DEBUG] Putting running to sleep " << _current -> id() << "\n";
    unsigned int priority = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    Sleeping_Queue::Element sleeping_link = Sleeping_Queue::Element(_current, priority);
    _sleeping.insert(&sleeping_link);
    _current -> sleep();
}

void Semaphore::wakeup() {
    // Chama wakeup da thread que deve ser acordada
    _sleeping.remove() -> object() -> wakeup();
}

void Semaphore::wakeup_all() {
    db<Semaphore>(TRC) << "[DEBUG] Waking up all threads " << "\n";
    while (!_sleeping.empty()) {
        _sleeping.remove() -> object() -> wakeup();
    }
}

int Semaphore::finc(volatile int & number) {
    return CPU::finc(number);
}

int Semaphore::fdec(volatile int & number) {
    return CPU::fdec(number);
}

__END_API
