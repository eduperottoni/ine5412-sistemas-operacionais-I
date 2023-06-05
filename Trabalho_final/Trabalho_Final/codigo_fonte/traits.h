#ifndef traits_h
#define traits_h

// Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

class CPU; //declaração das classes criadas nos trabalhos devem ser colocadas aqui
class Thread;
class Debug;
class System;
class Lists;
class Semaphore;
class Game;

//declaração da classe Traits
template<typename T>
struct Traits {};

template<>
struct Traits<CPU>: public Traits<void>
{
    //Adicionar aqui a declaração do tamanho da Pilha
    static const unsigned int STACK_SIZE = 8 * 1024; // 1Kb
    static const bool debugged = true;
};

// Gerencia os 4 níveis gerais de debug
template<>
struct Traits<Debug>: public Traits<void>
{
    static const bool error = false;
    static const bool warning = false;
    static const bool info = true;
    static const bool trace = true;
};

// Ativa ou desativa o debug para cada classe

template<>
struct Traits<System> : public Traits<void>
{
    static const bool debugged = false;
};

template<>
struct Traits<Thread> : public Traits<void>
{
    static const bool debugged = false;
};


template<>
struct Traits<Lists> : public Traits<void>
{
    static const bool debugged = false;
};

template<>
struct Traits<Semaphore> : public Traits<void>
{
    static const bool debugged = false;
};

template<>
struct Traits<Game> : public Traits<void>
{
    static const bool debugged = false;
};


__END_API

#endif