#include "classes/controller.h"
#include "classes/bullet.h"
#include "classes/game_config.h"
#include "classes/game.h"

__BEGIN_API

std::queue<Keyboard::Move> Controller::_action_queue;
std::queue<Keyboard::Move>* Controller::_player_queue;
std::queue<CollisionChecker::Collision*> Controller::_collision_queue;

Thread* Controller::_player_thread;
std::list<Thread*> Controller::_enemy_threads;

std::list<Enemy*>* Controller:: _enemy_objects;
Player* Controller:: _player_object;
std::list<Bullet*>* Controller:: _player_bullet_list;
std::list<Bullet*>* Controller:: _enemies_bullet_list;
// std::list<Bullet>* Controller::_bullet_list;

void Controller::_update_bullet_list(std::list<Bullet*>* bullet_list) {
    auto it = bullet_list->begin();
    while (it != bullet_list->end()) {
        if ((*it)->out_of_screen()) {
            delete *it;
            db<Controller>(TRC) << "[CONTROLLER] DELETEI BALA" << "\n";
            it = bullet_list->erase(it);
        } else {
            (*it)->update();
            ++it;
        }
    }
}

void Controller::handle_bullet_bullet_collision(int id_player_bullet, int id_enemy_bullet){
    db<Controller>(TRC) << "COLISÃO ENTRE BALA DO JOGADOR E BALA DO INIMIGO" <<"\n";
    if (id_player_bullet >= 0 && id_player_bullet < _player_bullet_list->size()) {
        auto it = _player_bullet_list->begin();
        std::advance(it, id_player_bullet); // Avança para o índice desejado
        delete *it;
        _player_bullet_list->erase(it); // Remove o elemento
        db<Controller>(TRC) << "[CONTROLLER] ELEMENTO REMOVIDO" <<"\n";
    } else {
        std::cout << "Índice inválido!" << std::endl;
    }
    if (id_enemy_bullet >= 0 && id_enemy_bullet < _enemies_bullet_list->size()) {
        auto it = _enemies_bullet_list->begin();
        std::advance(it, id_enemy_bullet); // Avança para a posição desejada
        delete *it;
        _enemies_bullet_list->erase(it);
    } else {
        db<Controller>(TRC) << "ERRO AO TRATAR bala inimiga" <<"\n";
    }
}

void Controller::handle_bullet_enemy_collision(int id_bullet, int id_enemy){
    db<Controller>(TRC) << "COLISÃO ENTRE BALA DO JOGADOR E INIMIGO" <<"\n";
    if (id_bullet >= 0 && id_bullet < _player_bullet_list->size()) {
        auto it = _player_bullet_list->begin();
        std::advance(it, id_bullet); // Avança para o índice desejado
        delete *it;
        _player_bullet_list->erase(it); // Remove o elemento
        _player_object->increment_score(100);
        _player_object->increment_kill();
        db<Controller>(TRC) << "[CONTROLLER] ELEMENTO REMOVIDO" <<"\n";
    } else {
        std::cout << "Índice inválido!" << std::endl;
    }
    if (id_enemy >= 0 && id_enemy < _enemy_objects->size()) {
        auto it = _enemy_objects->begin();
        std::advance(it, id_enemy); // Avança para a posição desejada
        Enemy* element = *it; // Acessa o elemento
        element->set_can_render(false);
        db<Controller>(TRC) << "CAN RENDER DO INIMIGO SETADO COMO FALSE" <<"\n";
    } else {
        db<Controller>(TRC) << "ERRO AO TRATAR INIMIGO" <<"\n";
    }
}

void Controller::handle_bullet_player_collision(int id_player, int id_bullet) {
    db<Controller>(TRC) << "COLISÃO ENTRE BALA DO INIMIGO E JOGADOR" <<"\n";
    if (id_bullet >= 0 && id_bullet < _enemies_bullet_list->size()) {
        auto it = _enemies_bullet_list->begin();
        std::advance(it, id_bullet); // Avança para o índice desejado
        delete *it;
        _enemies_bullet_list->erase(it);
        _player_object->decrement_health();
        db<Controller>(TRC) << "PERDEU VIDA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SOCORRO" <<"\n";
    } else {
        std::cout << "Índice inválido!" << std::endl;
    }
}

void Controller::run() {
    while (true) {
        if (*_game_config->get_game_state() == GameConfig::State::RUNNING) {
            db<Controller>(TRC) << "[CONTROLLER]vazia?" << !_collision_queue.empty() <<"\n";
            db<Controller>(TRC) << "[CONTROLLER]TAMANHO DA LISTA DE COLISÕES:" << _collision_queue.size() <<"\n";
            while (!_collision_queue.empty()) {
                CollisionChecker::Collision* collision = _collision_queue.front();
                _collision_queue.pop();
                db<Controller>(TRC) << "[CONTROLLER]TAMANHO DA LISTA DE COLISÕES:" << _collision_queue.size() <<"\n";
                db<Controller>(TRC) << "[CONTROLLER]id 1:" << collision->_obj_id1 <<"\n";
                db<Controller>(TRC) << "[CONTROLLER]id 2:" << collision->_obj_id2 <<"\n";
                db<Controller>(TRC) << "[CONTROLLER]CollisionType:" << collision->_collision_type <<"\n";
                if (collision->_collision_type == CollisionChecker::BULLET_ENEMY){
                    handle_bullet_enemy_collision(collision->_obj_id1, collision->_obj_id2);   
                } else if (collision->_collision_type == CollisionChecker::PLAYER_ENEMY){
                    db<Controller>(TRC) << "COLISÃO ENTRE PLAYER E INIMIGO" <<"\n";
                    // 
                } else if (collision->_collision_type == CollisionChecker::ENEMY_ENEMY){
                    db<Controller>(TRC) << "COLISÃO ENTRE INIMIGO E INIMIGO" <<"\n";
                } else if (collision->_collision_type == CollisionChecker::BULLET_PLAYER){
                    handle_bullet_player_collision(collision->_obj_id1, collision->_obj_id2);
                    db<Controller>(TRC) << "COLISÃO ENTRE BALA E JOGADOR" <<"\n";
                } else if (collision->_collision_type == CollisionChecker::BULLET_BULLET){
                    handle_bullet_bullet_collision(collision->_obj_id1, collision->_obj_id2);
                    db<Controller>(TRC) << "COLISÃO ENTRE BALA E BALA" << "\n";
                    // 
                }
                delete collision;
            }
            _update_bullet_list(_enemies_bullet_list);
            _update_bullet_list(_player_bullet_list);
        } else{
            db<Controller>(TRC) << "FALSEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE " << *_game_config->get_game_state() <<  "\n";
            db<Controller>(TRC) << "FALSEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE " << GameConfig::State::RUNNING <<  "\n";
        }
        // sf::FloatRect player_bounds = _player_object->get_sprite()->getGlobalBounds();
        // auto enemy = _enemy_objects->begin();
        // while (enemy != _enemy_objects->end()) {
        //     sf::FloatRect enemy_bounds = (*enemy)->get_sprite()->getGlobalBounds();
        //     if(player_bounds.intersects(enemy_bounds)) {
        //         db<Controller>(TRC) << "[CONTROLLER] COLLIDING!!!";
        //         //db<Controller>(TRC) << "[CONTROLLER] ENTREI NO LOOP" << "\n";
        //         // enemy = _enemy_objects->erase(enemy);
        //     } else {
        //         ++enemy;
        //     }
        // }
        // sf::FloatRect player_bounds = _player_object->get_sprite()->getGlobalBounds();
        // auto enemy = _enemy_objects->begin();
        // while (enemy != _enemy_objects->end()) {
        //     sf::FloatRect enemy_bounds = (*enemy)->get_sprite()->getGlobalBounds();
        //     if(player_bounds.intersects(enemy_bounds)) {
        //         db<Controller>(TRC) << "[CONTROLLER] COLLIDING!!!";
        //         //db<Controller>(TRC) << "[CONTROLLER] ENTREI NO LOOP" << "\n";
        //         enemy = _enemy_objects->erase(enemy);
        //     } else {
        //         ++enemy;
        //     }
        // }

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

        if (!_action_queue.empty()) {
            Keyboard::Move move = _action_queue.front();
            _action_queue.pop();
            //db<Controller>(TRC) << "[CONTROLLER] NOT EMPTY" << move << "\n";
            // MOVIMENTO DO JOGADOR
            if (move == Keyboard::Move::DOWN || move == Keyboard::Move::LEFT || move == Keyboard::Move::RIGHT || move == Keyboard::Move::UP || move == Keyboard::Move::SHOOT) {
                if (*_game_config->get_game_state() == GameConfig::State::RUNNING) _player_queue -> push(move);
            } else {
                // MOVIMENTO DE CONTROLE DO JOGO
                switch (move) {
                case Keyboard::Move::EXIT:
                    
                    //db<Controller>(TRC) << "[CONTROLLER] EXIT \n";
                    break;
                case Keyboard::Move::P:
                    //db<Controller>(TRC) << "[CONTROLLER] PAUSE PRESSIONADO \n";
                    if (*_game_config->get_game_state() == GameConfig::State::RUNNING) {
                        //db<Controller>(TRC) << "[CONTROLLER] PAUSE \n";
                        // SUPEND EM TODAS, EXCETO WINDOW E KEYBOARD
                    for (auto thread : _enemy_threads) thread -> suspend();
                        _player_thread -> suspend();
                        //*_game_config->get_game_state() == GameConfig::State::RUNNING
                        _game_config->set_game_state(GameConfig::State::PAUSED);
                        //*_current_state = PAUSED;
                    } else if (*_game_config->get_game_state() == GameConfig::State::PAUSED) {
                        for (auto thread : _enemy_threads) thread -> resume();
                        _player_thread -> resume();
                        //*_current_state = RUNNING;
                        _game_config->set_game_state(GameConfig::State::RUNNING);
                        //db<Controller>(TRC) << "[CONTROLLER] UNPAUSE \n";
                    }
                    break;
                default:
                break;
                }
            }
        } else {
            //db<Controller>(TRC) << "[CONTROLLER] EMPTY\n";
            //db<Controller>(TRC) << "[CONTROLLER] GAME ESTATE " << *_current_state << "\n";
        }
        Thread::yield();
    }
}


Controller::~Controller() {
}

std::queue<Keyboard::Move>* Controller::get_action_queue(){
    //db<Controller>(TRC) << "[CONTROLLER] Entrei no getter do _action_queue! \n";
    return &_action_queue;
}

std::queue<CollisionChecker::Collision*>* Controller::get_collision_queue(){
    // if (_collision_queue == nullptr) db<Controller>(TRC) << "[CONTROLLER] NULO CARALHO" << "\n";
    return &_collision_queue;
}

__END_API
