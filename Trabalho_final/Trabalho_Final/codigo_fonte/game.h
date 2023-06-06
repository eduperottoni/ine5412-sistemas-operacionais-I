#ifndef game_h
#define game_h


#include "cpu.h"
#include "thread.h"
#include "semaphore.h"
#include "traits.h"
#include "window.h"
#include <SFML/Graphics.hpp>

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
public:
    // Inicializiando as threads
    Game();

    // Deletando game
    ~Game();

    // Elementos do mapa
    // W: wall
    // a: arena
    // E: enemy
    // P: player
    // S: score
    // L: Life
    // Lv: Level
    typedef enum {W,a,E,P,S,L,Lv} tile;

    // Método de inicialização do jogo
    static void init();

    protected:
    // Matriz de elementos da arena
    inline static tile window[31][45] = 
    {
        {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
        {W,a,a,E,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,E,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,S,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,L,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,P,a,a,a,a,a,a,a,a,a,a,a,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
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
        {W,a,a,E,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,E,a,a,W,a,a,a,a,a,a,a,a,a,a,a,a,W},
        {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W}
    };

    // Chamada de Context
    typedef CPU::Context Context;

    private:
        Context * volatile game_context;
        // Objeto de Janela
        Window * _window;

};

__END_API

#endif