#include "classes/window.h"
#include "classes/player.h"
#include "classes/game.h"

__BEGIN_API

StaticSprite* Window::_screen;
StaticSprite* Window::_ready;
StaticSprite* Window::_score;
std::list<Bullet*>* Window::_player_bullet_list;
std::list<Bullet*>* Window::_enemies_bullet_list;

Window::Window(Player* player, std::list<sf::Sprite*> enemies_sprites_list, std::list<Bullet*>* player_bullet_list, std::list<Bullet*>* enemies_bullet_list, Clock* clock)
{
    db<Window>(TRC) << "[Window] Construindo a Window\n";

    int width = std::get<0>(_game_config.get_video_size());
    int height = std::get<1>(_game_config.get_video_size());
    _sf_window.create(sf::VideoMode(width, height), _game_config.get_window_title());

    _player_obj = player;
    for (auto enemy_sprite : enemies_sprites_list){
        _enemies_sprites_list.push_back(enemy_sprite);
    }
    _player_bullet_list = player_bullet_list;
    _enemies_bullet_list = enemies_bullet_list;
    _clock = clock;
    load_and_bind_textures();
}

sf::RenderWindow* Window::get_sf_window(){
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
    GameConfig* game_config = &GameConfig::get_instance();
    db<Window>(TRC) << "[Window] Renderizando a janela !\n";
    
    _sf_window.setFramerateLimit(_game_config.get_frame_limit());
    //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
    //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
    _sf_window.setKeyRepeatEnabled(_game_config.is_key_repeat_enabled());

    while (*game_config -> get_game_state() != GameConfig::State::FINISHING) {
        db<Window>(TRC) << "[Window] ENTREI NA WINDOW\n";



        // AQUI:

        // 1. Fazer a janela ler fila de eventos dela no game (criar fila de eventos para ela a ser atualizada pelo keyboard)
        // 1.1. Caso o evento for de pause, ficar em um loop mostrando a tela de pause
        //      Nesse caso, a thread vai ficar parada, não liberando o processador para as demais
        //      O que está certo, visto que nada pode acontecer quando o jogo estiver pausado.
        // 1.1.1. Dentro desse loop, quando ler o unpause, sai desse loop.

        _clock->set_delta_time();
        db<Window>(TRC) << "[Window] Entrei no loop!\n";
        _sf_window.clear();
        
        _sf_window.draw(*_screen -> get_sprite());
        // _sf_window.draw(*_ready -> get_sprite());
        _sf_window.draw(*_score -> get_sprite());
        _sf_window.draw(*_player_obj -> get_sprite());
        _text_score_value.setString(std::to_string(_player_obj -> get_score()));
        _sf_window.draw(_text_score_value);
        _sf_window.draw(_text_level);
        _text_level_value.setString(std::to_string(Game::get_level() + 1));
        cout << "TAMANHO DA LISTA:" << std::to_string(Game::get_level()) << "\n";
        _sf_window.draw(_text_level_value);
        _text_health_value.setString(std::to_string(_player_obj -> get_health()));
        _sf_window.draw(_text_health_value);
        _sf_window.draw(_text_health);
        // _sf_window.display();
        // _sf_window.draw(*_enemies_sprites_list.front());
        
        cout << "TAMANHO DA LISTA:" << _player_bullet_list->size() << "\n";
        cout << "TAMANHO DA LISTA:" << _enemies_bullet_list->size() << "\n";
        for (auto enemy_sprite : _enemies_sprites_list){
            // std::cout << "Type: " << typeid(*enemy_sprite).name() << std::endl;
            _sf_window.draw(*enemy_sprite);
        }

        for (auto bullet : *_player_bullet_list){
            _sf_window.draw(*bullet->get_sprite());
        }
        for (auto bullet : *_enemies_bullet_list){
            _sf_window.draw(*bullet->get_sprite());
        }
        _sf_window.display();
        
        // _sf_window.display();
        db<Window>(TRC) << "[Window] fim do loop da window\n";
        Thread::yield();
    }
    db<Window>(TRC) << "[Window] SAINDO DA WINDOW RUN\n";
}

void Window::load_and_bind_textures()
{
    float x_start = std::get<0>(_game_config.get_start_panel());
    float y_start = std::get<1>(_game_config.get_start_panel());

    map<Sprite::Orientation, string> path;
    path[Sprite::Orientation::STATIC] = "src/images/screen/screen.png";
    _screen = new StaticSprite(_game_config.get_screen_sprite_scale(), 0, path, Sprite::Orientation::STATIC, 0, 0);

    map<Sprite::Orientation, string> score_path;
    score_path[Sprite::Orientation::STATIC] = "src/images/ui/score_tex.png";
    _score = new StaticSprite(3, 0, score_path, Sprite::Orientation::STATIC, x_start, y_start);

    map<Sprite::Orientation, string> ready_path;
    ready_path[Sprite::Orientation::STATIC] = "src/images/ui/ready.png";
    _ready = new StaticSprite(3, 0, ready_path, Sprite::Orientation::STATIC, x_start, y_start+200);

    if (!_font.loadFromFile("src/fonts/Retro-Gaming.ttf"))
    {
        // Tratar erro caso a fonte não seja carregada corretamente
        db<Window>(ERR) << "[Window] Não foi possível carregar a fonte!\n";
    }

    // CONFIGURING THE SCORE TEXT ON SCREEN
    _text_score_value.setFont(_font);
    _text_score_value.setCharacterSize(_game_config.get_font_size());
    _text_score_value.setFillColor(sf::Color::White);
    _text_score_value.setPosition(x_start, y_start + 50);

    // CONFIGURING THE LEVEL TEXT ON SCREEN
    _text_level.setPosition(x_start, y_start + 200);
    _text_level.setFont(_font);
    _text_level.setString("LEVEL");
    _text_level.setFillColor(sf::Color::Blue);
    _text_level.setCharacterSize(_game_config.get_font_size() - 20);
    _text_level_value.setFont(_font);
    _text_level_value.setPosition(x_start, y_start + 250);
    _text_level_value.setFillColor(sf::Color::Yellow);
    _text_level_value.setCharacterSize(_game_config.get_font_size());
    
    // CONFIGURING HEALTH ON SCREEN
    _text_health.setPosition(x_start, y_start + 350);
    _text_health.setFont(_font);
    _text_health.setString("HEALTH");
    _text_health.setFillColor(sf::Color::Blue);
    _text_health.setCharacterSize(_game_config.get_font_size() - 20);
    _text_health_value.setFont(_font);
    _text_health_value.setPosition(x_start, y_start + 400);
    _text_health_value.setFillColor(sf::Color::Yellow);
    _text_health_value.setCharacterSize(_game_config.get_font_size());
    
}


__END_API