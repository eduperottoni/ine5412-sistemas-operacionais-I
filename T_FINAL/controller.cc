#include "classes/controller.h"
#include "classes/bullet.h"
#include "classes/game_config.h"
#include "classes/game.h"

__BEGIN_API

std::queue<Keyboard::Move> Controller::_action_queue;
std::queue<Keyboard::Move>* Controller::_player_queue;
std::queue<CollisionChecker::Collision*> Controller::_collision_queue;
GameConfig* Controller::_game_config;

Thread* Controller::_player_thread;
Thread* Controller::_collision_thread;
Thread* Controller::_window_thread;
std::list<Thread*> Controller::_enemy_threads;

std::list<Enemy*>* Controller:: _enemy_objects;
Player* Controller:: _player_object;
std::list<Bullet*>* Controller:: _player_bullet_list;
std::list<Bullet*>* Controller:: _enemies_bullet_list;

void Controller::reset() {
    db<Controller>(TRC) << "[CONTROLLER] RESETANDO OBJETOS" << "\n";
    _player_object -> set_health(_game_config -> get_player_health());
    _player_object -> set_kills(0);
    _player_object -> set_score(0);
    _player_object -> get_sprite() -> setPosition(300, 300);
    for (auto enemy : *_enemy_objects){
        enemy -> set_speed(_game_config->get_enemies_speed_lvl_1());
        enemy -> reset_position();
    }
    _resume_threads();
};


void Controller::_update_bullet_list(std::list<Bullet*>* bullet_list) {
    auto it = bullet_list->begin();
    while (it != bullet_list->end()) {
        if ((*it)->out_of_screen()) {
            it = bullet_list->erase(it);
        } else {
            (*it)->update(); 
        }
        ++it;
    }
}

void Controller::handle_bullet_bullet_collision(int id_player_bullet, int id_enemy_bullet){
    if (id_player_bullet >= 0 && id_player_bullet < _player_bullet_list->size()) {
        auto it = _player_bullet_list->begin();
        std::advance(it, id_player_bullet); // Avança para o índice desejado
        _player_bullet_list->erase(it); // Remove o elemento
    } else {
        std::cout << "Índice inválido!" << std::endl;
    }
    if (id_enemy_bullet >= 0 && id_enemy_bullet < _enemies_bullet_list->size()) {
        auto it = _enemies_bullet_list->begin();
        std::advance(it, id_enemy_bullet); // Avança para a posição desejada
        _enemies_bullet_list->erase(it);
    } else {
        db<Controller>(TRC) << "ERRO AO TRATAR bala inimiga" <<"\n";
    }
}

void Controller::handle_bullet_enemy_collision(int id_bullet, int id_enemy){
    if (id_bullet >= 0 && id_bullet < _player_bullet_list->size()) {
        auto it = _player_bullet_list->begin();
        std::advance(it, id_bullet); // Avança para o índice desejado
        _player_bullet_list->erase(it); // Remove o elemento
        _player_object->increment_score(100);
        _player_object->increment_kill();
    } else {
        std::cout << "Índice inválido!" << std::endl;
    }
    if (id_enemy >= 0 && id_enemy < _enemy_objects->size()) {
        auto it = _enemy_objects->begin();
        std::advance(it, id_enemy); // Avança para a posição desejada
        Enemy* element = *it; // Acessa o elemento
        element->set_can_render(false);
    } else {
        db<Controller>(TRC) << "ERRO AO TRATAR INIMIGO" <<"\n";
    }
}

void Controller::handle_bullet_player_collision(int id_player, int id_bullet) {
    if (id_bullet >= 0 && id_bullet < _enemies_bullet_list->size()) {
        auto it = _enemies_bullet_list->begin();
        std::advance(it, id_bullet); // Avança para o índice desejado
        delete *it;
        _enemies_bullet_list->erase(it);
        _player_object->decrement_health();
    } else {
        std::cout << "Índice inválido!" << std::endl;
    }
}

void Controller::handle_player_enemy_collision(int id_player, int id_enemy) {
    if (id_enemy >= 0 && id_enemy < _enemy_objects->size()) {
        auto it = _enemy_objects->begin();
        std::advance(it, id_enemy); // Avança para a posição desejada
        Enemy* element = *it; // Acessa o elemento
        element->set_can_render(false);
        _player_object -> decrement_health();
    }
}

void Controller::_resume_threads(){
    _player_thread->resume();
    for (auto enemy : _enemy_threads) {
        enemy -> resume();
    }
    _collision_thread -> resume();
}

void Controller::_suspend_threads(){
    _player_thread -> suspend();
    for (auto enemy : _enemy_threads) {
        enemy -> suspend();
    }
    _collision_thread -> suspend();
}

void Controller::run() {
    while (true) {
        if (*_game_config->get_game_state() == GameConfig::State::FINISHING){
            clear();
            break;
        }
        else if (*_game_config->get_game_state() == GameConfig::State::OVER) {
            while (*_game_config->get_game_state() == GameConfig::State::OVER) {
                if (!_action_queue.empty()) {
                    Keyboard::Move move = _action_queue.front();
                    _action_queue.pop();
                    if (move == Keyboard::RESET) {
                        reset();
                        _game_config -> set_game_state(GameConfig::State::RUNNING);
                    } else if (move == Keyboard::QUIT) {
                        _resume_threads();
                        _game_config -> set_game_state(GameConfig::State::FINISHING);
                    }
                }
                Thread::yield();
            }
            if (*_game_config->get_game_state() == GameConfig::State::FINISHING) {
                break;
            }
        } else if (*_game_config->get_game_state() == GameConfig::State::RUNNING) {
            if (_player_object->get_health() <= 0) {
                _game_config->set_game_state(GameConfig::State::OVER);
                _suspend_threads();
                clear();
                continue;
            }
            while (!_collision_queue.empty()) {
                CollisionChecker::Collision* collision = _collision_queue.front();
                _collision_queue.pop();
                if (collision->_collision_type == CollisionChecker::BULLET_ENEMY){
                    handle_bullet_enemy_collision(collision->_obj_id1, collision->_obj_id2);   
                } else if (collision->_collision_type == CollisionChecker::PLAYER_ENEMY){
                    handle_player_enemy_collision(collision->_obj_id1, collision->_obj_id2);
                } else if (collision->_collision_type == CollisionChecker::BULLET_PLAYER){
                    handle_bullet_player_collision(collision->_obj_id1, collision->_obj_id2);
                } else if (collision->_collision_type == CollisionChecker::BULLET_BULLET){
                    handle_bullet_bullet_collision(collision->_obj_id1, collision->_obj_id2);
                }
                delete collision;
            }
            _update_bullet_list(_enemies_bullet_list);
            _update_bullet_list(_player_bullet_list);
            _update_level();
        }
        if (!_action_queue.empty()) {
            Keyboard::Move move = _action_queue.front();
            _action_queue.pop();
            // MOVIMENTO DO JOGADOR
            if (move == Keyboard::Move::DOWN || move == Keyboard::Move::LEFT || move == Keyboard::Move::RIGHT || move == Keyboard::Move::UP || move == Keyboard::Move::SHOOT) {
                if (*_game_config->get_game_state() == GameConfig::State::RUNNING) _player_queue -> push(move);
            } else {
                // MOVIMENTO DE CONTROLE DO JOGO
                switch (move) {
                case Keyboard::Move::P:
                    if (*_game_config -> get_game_state() == GameConfig::State::RUNNING) {
                        for (auto thread : _enemy_threads) thread -> suspend();
                        _player_thread -> suspend();
                        _game_config -> set_game_state(GameConfig::State::PAUSED);
                    } else if (*_game_config -> get_game_state() == GameConfig::State::PAUSED) {
                        for (auto thread : _enemy_threads) thread -> resume();
                        _player_thread -> resume();
                        _game_config -> set_game_state(GameConfig::State::RUNNING);
                    }
                    break;
                case Keyboard::Move::QUIT:
                    _game_config -> set_game_state(GameConfig::State::FINISHING);
                default:
                break;
                }
            }
        }  
        Thread::yield();
    }
}

void Controller::_update_level() {
    if (_player_object->get_kills() == _game_config->get_kills_to_lvl_2()) {
        for (auto enemy : *_enemy_objects) {
            enemy->set_speed(_game_config->get_enemies_speed_lvl_2());
            Game::set_level(Game::Level::LEVEL_2);
        }
    }
    if (_player_object->get_kills() == _game_config->get_kills_to_lvl_3()) {
        for (auto enemy : *_enemy_objects) {
            enemy->set_speed(_game_config->get_enemies_speed_lvl_3());
            Game::set_level(Game::Level::LEVEL_3);
        }
    }
}


Controller::~Controller() {
}

std::queue<Keyboard::Move>* Controller::get_action_queue() {
    return &_action_queue;
}

std::queue<CollisionChecker::Collision*>* Controller::get_collision_queue() {
    return &_collision_queue;
}

void Controller::clear() {
    while (!_enemies_bullet_list->empty()) {
        Bullet* bullet = _enemies_bullet_list->front();
        _enemies_bullet_list->pop_front();
        delete bullet;
    }
    while (!_player_bullet_list->empty()) {
        Bullet* bullet = _player_bullet_list->front();
        _player_bullet_list->pop_front();
        delete bullet;
    }

    while (!_collision_queue.empty()) {
        CollisionChecker::Collision* collision = _collision_queue.front();
        _collision_queue.pop();
        delete collision;
    }
    while (!_action_queue.empty()) {
        _action_queue.pop();
    }
}

__END_API
