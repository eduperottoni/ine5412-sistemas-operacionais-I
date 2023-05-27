#include "semaphore.h"

__BEGIN_API

Semaphore::Semaphore(int v){
    _counter = v;
}

Semaphore::~Semaphore(){
    // acorda todas as threads na deleção do Semáforo
    wakeup_all();
}

void Semaphore::p() {
    db<Semaphore>(TRC) << "Semaphore counter on P() = " << _counter << "\n";
    if (fdec(_counter) < 0){
        sleep();
    }
    
    // if (_counter > 0) {
    //     fdec(_counter);
    // } else {
    //     sleep();
    // }
}

void Semaphore::v() {
    if(finc(_counter) < 1){
        wakeup();
    }
    
    // if (_sleeping.empty()) {
    //     finc(_counter);
    // } else {
    //     wakeup();
    // }
    db<Semaphore>(TRC) << "Semaphore counter on V() = " << _counter << "\n";
}

void Semaphore::sleep() {
    Thread* _current = Thread::running();
    unsigned int priority = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    Sleeping_Queue::Element sleeping_link = Sleeping_Queue::Element(_current, priority);
    _sleeping.insert(&sleeping_link);
    _current -> sleep();
}

void Semaphore::wakeup() {
    // Trocar o estado da Thread
    _sleeping.remove() -> object() -> wakeup();
}

void Semaphore::wakeup_all() {
    while (!_sleeping.empty()) {
        wakeup();
    }
}

int Semaphore::finc(volatile int & number) {
    return CPU::finc(number);
}

int Semaphore::fdec(volatile int & number) {
    return CPU::fdec(number);
}

__END_API
