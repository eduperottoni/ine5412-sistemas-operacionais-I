#ifndef traits_h
#define traits_h

// Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

//Declaração das classes criadas no jogo devem ser colocadas aqui
class Debug;
class Sprite;
class CPU;
class Thread;
class System;
class Lists;
class Game;
class Semaphore;
class Window;
class Player;
class Keyboard;
class Controller;
class CollisionChecker;
class MovingSprite;
class Enemy;

//declaração da classe Traits
template<typename T>
struct Traits {};

// Gerencia os 4 níveis gerais de debug
template<>
struct Traits<Debug>: public Traits<void>
{
    static const bool error = false;
    static const bool warning = false;
    static const bool info = true;
    static const bool trace = true;
};

template<>
struct Traits<CPU>: public Traits<void>
{
    //Adicionar aqui a declaração do tamanho da Pilha
    static const unsigned int STACK_SIZE = 1000 * 1024; // 1Kb
    static const bool debugged = true;
};

// Ativa ou desativa o debug para cada classe
template<>
struct Traits<Sprite>: public Traits<void>
{
    static const bool debugged = true;
};

template<>
struct Traits<System>: public Traits<void>
{
    static const bool debugged = false;
};

template<>
struct Traits<Lists>: public Traits<void>
{
    static const bool debugged = false;
};

template<>
struct Traits<Thread>: public Traits<void>
{
    static const bool debugged = false;
};


template<>
struct Traits<Semaphore>: public Traits<void>
{
    static const bool debugged = false;
};

template<>
struct Traits<Window>: public Traits<void>
{
    static const bool debugged = true;
};

template<>
struct Traits<Player>: public Traits<void>
{
    static const bool debugged = true;
};

template<>
struct Traits<Game>: public Traits<void>
{
    static const bool debugged = true;
};

template<>
struct Traits<Keyboard>: public Traits<void>
{
    static const bool debugged = false;
};

template<>
struct Traits<Controller>: public Traits<void>
{
    static const bool debugged = true;
};

template<>
struct Traits<CollisionChecker>: public Traits<void>
{
    static const bool debugged = true;
};

template<>
struct Traits<MovingSprite>: public Traits<void>
{
    static const bool debugged = true;
};

template<>
struct Traits<Enemy>: public Traits<void>
{
    static const bool debugged = true;
};
__END_API

#endif