#ifndef game_h
#define game_h


#include "cpu.h"
#include "thread.h"
#include "semaphore.h"
#include "traits.h"
#include "window.h"

using namespace std;

__BEGIN_API

/*
    Arena de batalha:
        W: wall
        a: arena
        

    window[45][30] = 
    {
        {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W}
    }
*/

class Game
{
protected:
    typedef CPU::Context Context;

public:
    // Inicializiando as threads
    Game();

    // Deletando game
    ~Game();

    // Elementos do mapa
    // typedef enum elements {W,a,E,P};

    //
    // inline static window[30][45] = 
    // {
    //     {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
    //     {W,a,a,E,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,E,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,P,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,a,a,E,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,E,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
    //     {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W}
    // };

    // Objeto de Janela
    static Window *_window;

    // Método de inicialização do jogo
    static void init();

    private:
        Context * volatile game_context;
        // // Eixos x e y da tela
        // int sizex;
        // int sizey;

};


Game::Game(){
    // Inicialização da Thread de jogo, criação do contexto
    game_context = new CPU::Context();
}

__END_API

#endif