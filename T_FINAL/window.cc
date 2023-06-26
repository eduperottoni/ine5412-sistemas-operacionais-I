#include "classes/window.h"
#include "classes/player.h"

__BEGIN_API

StaticSprite* Window::_screen;
StaticSprite* Window::_ready;
StaticSprite* Window::_score;
std::list<Bullet*>* Window::_player_bullet_list;
std::list<Bullet*>* Window::_enemies_bullet_list;

Window::Window(sf::Sprite* sprite, std::list<sf::Sprite*> enemies_sprites_list, std::list<Bullet*>* player_bullet_list, std::list<Bullet*>* enemies_bullet_list, Clock* clock)
{
    _sf_window.create(sf::VideoMode(1086, 746), "Brick Game");
    //_sf_window = window;
    db<Window>(TRC) << "[Window] Construindo a janela e carregando as texturas \n";
    db<Window>(TRC) << "[Window] Criação da Thread da janela \n";
    // carregamento das texturas
    _player_sprite = sprite;
    for (auto enemy_sprite : enemies_sprites_list){
        _enemies_sprites_list.push_back(enemy_sprite);
    }
    _player_bullet_list = player_bullet_list;
    _enemies_bullet_list = enemies_bullet_list;
    // _enemies_sprites_list = enemies_sprites_list;
    _clock = clock;
    load_and_bind_textures();
}

sf::RenderWindow* Window::get_sf_window(){
    db<Window>(TRC) << "[Window] Entrei no getter do _sf_window! \n";
    return &_sf_window;
}

Window::~Window() {
    // delete _player;
}

void Window::draw_texture(unsigned int texture, int length, int height, float angle)
{
}

void Window::run()
{
    db<Window>(TRC) << "[Window] Renderizando a janela !\n";
    
    // FIXME ESSE VALOR DEVE VIR DE UMA CLASSE DE CONFIGURAÇÃO
    _sf_window.setFramerateLimit(10);
    db<Window>(TRC) << "[Window] oiii !\n";
    //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
    //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
    // FIXME ESSE VALOR DEVE VIR DE UMA CLASSE DE CONFIGURAÇÃO
    _sf_window.setKeyRepeatEnabled(_game_config.is_key_repeat_enabled());

    

    db<Window>(TRC) << "[Window] Preparação da chamada do jogador !\n";
    // Preparação da chamada da Thread jogador:
    // Chamada do escalonador para ceder o processamento para criação do jogador
    // _window->join();

    // Instanciação do jodador
    // _player = new Player();

    // db<Window>(TRC) << "[Window] Jogador construido !\n";

    while (_sf_window.isOpen())
    {   

        // AQUI:

        // 1. Fazer a janela ler fila de eventos dela no game (criar fila de eventos para ela a ser atualizada pelo keyboard)
        // 1.1. Caso o evento for de pause, ficar em um loop mostrando a tela de pause
        //      Nesse caso, a thread vai ficar parada, não liberando o processador para as demais
        //      O que está certo, visto que nada pode acontecer quando o jogo estiver pausado.
        // 1.1.1. Dentro desse loop, quando ler o unpause, sai desse loop.

        _clock->set_delta_time();
        db<Window>(TRC) << "[Window] Entrei no loop!\n";
        _sf_window.clear();
        // _sf_window.draw(maze_sprite);
        
        
        // sf::Event event;
        // while (window.pollEvent(event))
        // {
        //     switch (event.type) {
        //     case sf::Event::Closed:
        //         window.close();
        //         break;
            
        //     // key pressed
        //     case sf::Event::KeyPressed:
        //         // // Player será movido para cima ou para baixo
        //         // _player->move();
        //         // // PLayer será movido para a esquerda ou para a direita
        //         // _player->rotate();
                
        //         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        //             // Encapsulamento de funções, não funcional
        //             // _player->move("Left");
        //             db<Window>(TRC) <<"[Window] Tecla a esquerda \n";
        //             space_ship_sprite.setTexture(space_ship_left);
        //             space_ship_sprite.setPosition(space_ship_sprite.getPosition().x - 10, space_ship_sprite.getPosition().y);
                
        //         } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        //             // _player->move("Right");
        //             db<Window>(TRC) <<"[Window] Tecla a direita \n";
        //             space_ship_sprite.setTexture(space_ship_right);    
        //             space_ship_sprite.setPosition(space_ship_sprite.getPosition().x + 10, space_ship_sprite.getPosition().y);
                
        //         } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        //             // _player->rotate("Down");
        //             db<Window>(TRC) <<"[Window] Tecla para baixo \n";
        //             space_ship_sprite.setTexture(space_ship_down);
        //             space_ship_sprite.setPosition(space_ship_sprite.getPosition().x, space_ship_sprite.getPosition().y + 10);
                
        //         } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        //             // _player->rotate("Up");
        //             db<Window>(TRC) <<"[Window] Tecla para cima \n";
        //             space_ship_sprite.setTexture(space_ship_up);
        //             space_ship_sprite.setPosition(space_ship_sprite.getPosition().x, space_ship_sprite.getPosition().y - 10);

        //         } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        //             db<Window>(TRC) <<"[Window] Tiro orientado \n";
        //             // Chamar o Tiro aqui
        //             shot_sprite.setTexture(shot_tex);
        //             shot_sprite.setPosition(space_ship_sprite.getPosition().x + 10, space_ship_sprite.getPosition().y + 10);
        //             // Chamada de método para direcionar o tiro
                
        //         } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        //             db<Window>(TRC) <<"[Window] Jogo pausado !\n";
        //             // Chamada de Pause
        //             // Botando todas as Threads na fila de suspensos
                    
        //         }
        //         else
        //             std::cout << "Keyboard pressed = " << event.key.code << std::endl;
        //         break;

        //         default:
        //             break;
            
        //     }
        // }

        
        _sf_window.draw(*_screen -> get_sprite());
        _sf_window.draw(*_ready -> get_sprite());
        _sf_window.draw(*_score -> get_sprite());
        _sf_window.draw(*_player_sprite);
        _sf_window.draw(_text);
        // _sf_window.display();
        // _sf_window.draw(*_enemies_sprites_list.front());
        
        cout << "TAMANHO DA LISTA:" << _player_bullet_list->size() << "\n";
        cout << "TAMANHO DA LISTA:" << _enemies_bullet_list->size() << "\n";
        for (auto enemy_sprite : _enemies_sprites_list){
            // std::cout << "Type: " << typeid(*enemy_sprite).name() << std::endl;
            // cout << "POSIÇÃO DO INIMIGO EM X:" << enemy_sprite->getPosition().x << "\n";
            // cout << "POSIÇÃO DO INIMIGO EM Y:" << enemy_sprite->getPosition().y << "\n";
            _sf_window.draw(*enemy_sprite);
        }

        for (auto bullet : *_player_bullet_list){
            // bullet->update();
            // db<Window>(TRC) << "[Window] DESENHANDO BULLET!\n";
            _sf_window.draw(*bullet->get_sprite());
            // db<Window>(TRC) << "[Window] DESENHEI BULLET!\n";
        }
        for (auto bullet : *_enemies_bullet_list){
            _sf_window.draw(*bullet->get_sprite());
        }
        _sf_window.display();

        // enemy_ship_sprite.setPosition(245, 150);
        // _sf_window.draw(enemy_ship_sprite);

        // shot_sprite.setPosition(204, 400);
        // _sf_window.draw(shot_sprite);
        
        // _sf_window.display();
        Thread::yield();
    }
    
}

void Window::load_and_bind_textures()
{
    // int NUMBER_OF_ENEMIES = 4;
    float SCALE = 0.75;
    float ENEMIES_SPEED = 100.f;
    float SCREEN_SCALE = 2.f;
    float TEXT_X = 850;
    float TEXT_Y = 100;
    map<Sprite::Orientation, string> path;
    path[Sprite::Orientation::STATIC] = "src/images/screen/screen.png";
    _screen = new StaticSprite(SCREEN_SCALE, 0, path, Sprite::Orientation::STATIC, 0, 0);

    map<Sprite::Orientation, string> score_path;
    score_path[Sprite::Orientation::STATIC] = "src/images/ui/score_tex.png";
    _score = new StaticSprite(3, 0, score_path, Sprite::Orientation::STATIC, 850, 50);

    map<Sprite::Orientation, string> ready_path;
    ready_path[Sprite::Orientation::STATIC] = "src/images/ui/ready.png";
    _ready = new StaticSprite(3, 0, ready_path, Sprite::Orientation::STATIC, 850, 200);

    
    if (!_font.loadFromFile("src/fonts/Orbitron-VariableFont_wght.ttf"))
    {
        // Tratar erro caso a fonte não seja carregada corretamente
        db<Window>(ERR) << "[Window] Não foi possível carregar a fonte!\n";
    }

    _text.setFont(_font);
    _text.setString("0");
    _text.setCharacterSize(50);
    _text.setFillColor(sf::Color::White);
    _text.setPosition(TEXT_X, TEXT_Y);
    

    // for(int i = 0; i < )
    // Bind map textures
    // if(!maze_tex.loadFromFile("sprites/maze/screen.png")){
    //     db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    // }else{
    //     db<Window>(INF) << "[Window] Desenhando a Arena\n";
    // }
    // maze_sprite.setTexture(maze_tex);
    // maze_sprite.scale(1.5, 1.5);
    
    // // player.render()

    // if(!shot_tex.loadFromFile("sprites/space_ships/shot.png")){
    //     db<Window>(INF) << "[Window] Não foi possível obter o o arquivo\n";
    // }else {
    //     db<Window>(INF) << "[Window] Desenhando o tiro\n";
    // };
    // shot_sprite.setTexture(shot_tex);
    // shot_sprite.scale(-0.5, -0.5);

    // // if(!space_ship_up.loadFromFile("sprites/space_ships/space_ship1.png")){
    // //     db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    // // }else {
    // //     db<Window>(INF) << "[Window] Desenhando a nave\n";
    // // };
    // // space_ship_sprite.setTexture(space_ship_up);
    // // space_ship_sprite.scale(0.85, 0.85);

    // // if(!space_ship_left.loadFromFile("sprites/space_ships/space_ship2.png")){
    // //     db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    // // }else {
    // //     db<Window>(INF) << "[Window] Desenhando a nave\n";
    // // };
    // // space_ship_sprite.setTexture(space_ship_left);
    // // space_ship_sprite.scale(0.85, 0.85);

    // // if(!space_ship_down.loadFromFile("sprites/space_ships/space_ship3.png")){
    // //     db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    // // }else {
    // //     db<Window>(INF) << "[Window] Desenhando a nave\n";
    // // };
    // // space_ship_sprite.setTexture(space_ship_down);
    // // space_ship_sprite.scale(0.85, 0.85);

    // // if(!space_ship_right.loadFromFile("sprites/space_ships/enemy)space_ship.png")){
    // //     db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    // // }else {
    // //     db<Window>(INF) << "[Window] Desenhando a nave\n";
    // // };
    // // space_ship_sprite.setTexture(space_ship_right);
    // // space_ship_sprite.scale(0.85, 0.85);

    // if(!enemy_ship_tex.loadFromFile("sprites/space_ships/enemy_space_ship_up.png")){
    //     db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    // } else {
    //     db<Window>(INF) << "[Window] Desenhando um inimigo\n";
    // };
    // enemy_ship_sprite.setTexture(enemy_ship_tex);
    // enemy_ship_sprite.scale(0.85,0.85);

    // if(!shot_tex.loadFromFile("sprites/space_ships/shot.png")){
    //     db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    // } else {
    //     db<Window>(INF) << "[Window] Desenhando um tiro\n";
    // };
    // shot_sprite.setTexture(enemy_ship_tex);
    // shot_sprite.scale(0.25,0.25);
}


__END_API