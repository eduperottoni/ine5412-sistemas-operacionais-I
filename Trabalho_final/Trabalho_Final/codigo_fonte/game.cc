#include "game.h"
#include <SFML/Graphics.hpp>


__BEGIN_API

Game _game;

Game::Game(){
    game_context = new CPU::Context();
    // Chamada de init para desenhar a tela
    db<Game>(INF) << "[Debug] Game::init() chamado\n";
    _game.init();
}

// Inicialização do jogo realiza a pintura da tela do jogo
void Game::init()
{
    // Chamando o método run() da instancia de window
    _game._window->run();
}

// Deletando o contexto do jogo
Game::~Game(){
    delete game_context;
}



__END_API