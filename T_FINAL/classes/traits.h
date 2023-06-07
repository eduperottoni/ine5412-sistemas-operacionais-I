#ifndef traits_game_h
#define traits_game_h

// Não alterar as 3 declarações abaixo

#define __BEGIN_GAME             namespace GAME {
#define __END_GAME               }
#define __USING_GAME            using namespace GAME;

__BEGIN_GAME

//Declaração das classes criadas no jogo devem ser colocadas aqui
class Debug;
class Sprite;

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

// Ativa ou desativa o debug para cada classe
template<>
struct Traits<Sprite>: public Traits<void>
{
    static const bool debugged = true;
};


__END_GAME

#endif