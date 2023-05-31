#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    // Saves the current context
    getcontext(&_context);
}

void CPU::Context::load()
{
    // Loads the context for the caller (that will take on the execution)
    setcontext(&_context);
}

CPU::Context::~Context()
{
    // Deletes stack to liberate the memory
    if (_stack) delete _stack;
}

int CPU::switch_context(Context *from, Context *to)
{
    // Switches context
    return swapcontext(&from->_context, &to->_context);
}

int CPU::finc(volatile int &number){
    // Returns the number intital value and saves incremented value in number
    int inc_value = 1;
    asm("lock xadd %0, %2" : "=a" (inc_value) : "a" (inc_value), "m" (number));

    return inc_value;
}

int CPU::fdec(volatile int &number){
    // Return the number's initial value and saves decremented value in number
    int dec_value = -1;
    asm("lock xadd %0, %2" : "=a" (dec_value) : "a" (dec_value), "m" (number));
    
    return dec_value;
}

__END_API
