#include "main_class.h"

__BEGIN_API

 void Main::run(void * name){
    // Inicializando o Jogo
    Game * game = new Game();
    // Deletando a thread do jogo
    delete game;
 }

__END_API
