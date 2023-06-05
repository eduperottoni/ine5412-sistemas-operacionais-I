#include "game.h"


__BEGIN_API

// Inicialização do jogo realiza a pintura da tela do jogo
void Game::init()
{
    // Chamando o método run() a instancia da Janela
    _window->run();

};

// Deletando o contexto do jogo
Game::~Game(){
    delete game_context;
}


__END_API