#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    //adicionar implementação
}

void CPU::Context::load()
{
    //adicionar implementação
}

template<typename ... Tn>
CPU::Context::Context(void (* func)(Tn ...), Tn ... an){
    // adicionar implementação
}

CPU::Context::~Context()
{
    //adicionar implementação
}

int CPU::switch_context(Context *from, Context *to)
{
     //implementação do método
}

__END_API
