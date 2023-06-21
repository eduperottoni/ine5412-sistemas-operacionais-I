#include "classes/window.h"
#include "classes/player.h"
#include "classes/enemy.h"

__BEGIN_API

Window::Window()
{
    _sf_window.create(sf::VideoMode(900, 560), "Brick Game");
    //_sf_window = window;
    db<Window>(TRC) << "[Window] Construindo a janela e carregando as texturas \n";
    db<Window>(TRC) << "[Window] Criação da Thread da janela \n";
    // carregamento das texturas
    map<MovingSprite::Orientation, string> sprites;
    sprites[MovingSprite::Orientation::RIGHT] = "src/images/space_ships/space_ship1.png";
    sprites[MovingSprite::Orientation::LEFT] = "src/images/space_ships/space_ship2.png";
    sprites[MovingSprite::Orientation::UP] = "src/images/space_ships/space_ship3.png";
    sprites[MovingSprite::Orientation::DOWN] = "src/images/space_ships/space_ship4.png";

    _player = new Player(sprites);
    load_and_bind_textures();
}

sf::RenderWindow* Window::get_sf_window(){
    db<Window>(TRC) << "[Window] Entrei no getter do _sf_window! \n";
    return &_sf_window;
}


// Window::~Window() {
//     delete _player;
//     delete _enemy;
// }

void Window::draw_texture(unsigned int texture, int length, int height, float angle)
{
}

void Window::run()
{
    db<Window>(TRC) << "[Window] Renderizando a janela !\n";
    
    _sf_window.setFramerateLimit(10);
    db<Window>(TRC) << "[Window] FPS 10 !\n";
    //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
    //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
    _sf_window.setKeyRepeatEnabled(false);

    db<Window>(TRC) << "[Window] Preparação da chamada do jogador !\n";
    // Preparação da chamada da Thread jogador:
    // Chamada do escalonador para ceder o processamento para criação do jogador
    // _window->join();

    // Instanciação do jodador
    // _player = new Player();

    while (_sf_window.isOpen())
    {   db<Window>(TRC) << "[Window] Entrei no loop!\n";
        _sf_window.clear();
        _sf_window.draw(maze_sprite);
        
        sf::Sprite player_sprite = _player->get_current_sprite();
        player_sprite.setPosition(0,0);
        _sf_window.draw(player_sprite);
        
        // //TODO
        // // player.set_position()
        // enemy_ship_sprite.setPosition(245, 150);
        // _sf_window.draw(enemy_ship_sprite);

        // shot_sprite.setPosition(204, 400);
        // _sf_window.draw(shot_sprite);
        
        _sf_window.display();
        db<Window>(TRC) << "[Window] Chamada de yield!\n";
        Thread::yield();
    }
    
}

void Window::load_and_bind_textures()
{
    // for(int i = 0; i < )
    // Bind map textures
    if(!maze_tex.loadFromFile("sprites/maze/screen.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    }else{
        db<Window>(INF) << "[Window] Desenhando a Arena\n";
    }
    maze_sprite.setTexture(maze_tex);
    maze_sprite.scale(1.5, 1.5);
    
    // player.render()

    if(!shot_tex.loadFromFile("sprites/space_ships/shot.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o o arquivo\n";
    }else {
        db<Window>(INF) << "[Window] Desenhando o tiro\n";
    };
    shot_sprite.setTexture(shot_tex);
    shot_sprite.scale(-0.5, -0.5);

    if(!space_ship_up.loadFromFile("sprites/space_ships/space_ship1.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    }else {
        db<Window>(INF) << "[Window] Desenhando a nave\n";
    };
    space_ship_sprite.setTexture(space_ship_up);
    space_ship_sprite.scale(0.85, 0.85);

    if(!space_ship_left.loadFromFile("sprites/space_ships/space_ship2.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    }else {
        db<Window>(INF) << "[Window] Desenhando a nave\n";
    };
    space_ship_sprite.setTexture(space_ship_left);
    space_ship_sprite.scale(0.85, 0.85);

    if(!space_ship_down.loadFromFile("sprites/space_ships/space_ship3.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    }else {
        db<Window>(INF) << "[Window] Desenhando a nave\n";
    };
    space_ship_sprite.setTexture(space_ship_down);
    space_ship_sprite.scale(0.85, 0.85);

    if(!space_ship_right.loadFromFile("sprites/space_ships/space_ship4.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    }else {
        db<Window>(INF) << "[Window] Desenhando a nave\n";
    };
    space_ship_sprite.setTexture(space_ship_right);
    space_ship_sprite.scale(0.85, 0.85);

    if(!enemy_ship_up.loadFromFile("sprites/space_ships/enemy_space_ship1.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    } else {
        db<Window>(INF) << "[Window] Desenhando um inimigo\n";
    };
    enemy_ship_sprite.setTexture(enemy_ship_up);
    enemy_ship_sprite.scale(0.85,0.85);

    if(!enemy_ship_left.loadFromFile("sprites/space_ships/enemy_space_ship2.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    } else {
        db<Window>(INF) << "[Window] Desenhando um inimigo\n";
    };
    enemy_ship_sprite.setTexture(enemy_ship_left);
    enemy_ship_sprite.scale(0.85,0.85);

    if(!enemy_ship_right.loadFromFile("sprites/space_ships/enemy_space_ship3.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    } else {
        db<Window>(INF) << "[Window] Desenhando um inimigo\n";
    };
    enemy_ship_sprite.setTexture(enemy_ship_right);
    enemy_ship_sprite.scale(0.85,0.85);

        if(!enemy_ship_down.loadFromFile("sprites/space_ships/enemy_space_ship4.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    } else {
        db<Window>(INF) << "[Window] Desenhando um inimigo\n";
    };
    enemy_ship_sprite.setTexture(enemy_ship_down);
    enemy_ship_sprite.scale(0.85,0.85);

    if(!shot_tex.loadFromFile("sprites/space_ships/shot.png")){
        db<Window>(INF) << "[Window] Não foi possível obter o arquivo\n";
    } else {
        db<Window>(INF) << "[Window] Desenhando um tiro\n";
    };
    shot_sprite.setTexture(shot_tex);
    shot_sprite.scale(0.25,0.25);
}


__END_API