#include "classes/controller.h"
#include "classes/bullet.h"

__BEGIN_API

std::queue<Keyboard::Move> Controller::_action_queue;
Controller::State Controller::_game_state;
std::queue<Keyboard::Move>* Controller::_player_queue;

Thread* Controller::_player_thread;
std::list<Thread*> Controller::_enemy_threads;

std::list<Enemy*>* Controller:: _enemy_objects;
Player* Controller:: _player_object;
std::list<Bullet*>* Controller:: _bullet_list;
// std::list<Bullet>* Controller::_bullet_list;

void Controller::run() {
    while (true) {
        if (_game_state == RUNNING) {
            auto it = _bullet_list->begin();
            while (it != _bullet_list->end()) {
                if ((*it)->out_of_screen()) {
                    //db<Controller>(TRC) << "[CONTROLLER] ENTREI NO LOOP" << "\n";
                    delete *it;
                    it = _bullet_list->erase(it);
                } else {
                    (*it)->update();
                    ++it;
                }
            }
        }
        sf::FloatRect player_bounds = _player_object->get_sprite()->getGlobalBounds();
        auto enemy = _enemy_objects->begin();
        while (enemy != _enemy_objects->end()) {
            sf::FloatRect enemy_bounds = (*enemy)->get_sprite()->getGlobalBounds();
            if(player_bounds.intersects(enemy_bounds)) {
                db<Controller>(TRC) << "[CONTROLLER] COLLIDING!!!";
                //db<Controller>(TRC) << "[CONTROLLER] ENTREI NO LOOP" << "\n";
                enemy = _enemy_objects->erase(enemy);
            } else {
                ++enemy;
            }
        }
        if (!_action_queue.empty()) {
            Keyboard::Move move = _action_queue.front();
            _action_queue.pop();
            //db<Controller>(TRC) << "[CONTROLLER] NOT EMPTY" << move << "\n";
            // MOVIMENTO DO JOGADOR
            if (move == Keyboard::Move::DOWN || move == Keyboard::Move::LEFT || move == Keyboard::Move::RIGHT || move == Keyboard::Move::UP || move == Keyboard::Move::SHOOT) {
                if (_game_state == RUNNING) _player_queue -> push(move);
            } else {
                // MOVIMENTO DE CONTROLE DO JOGO
                switch (move) {
                case Keyboard::Move::EXIT:
                    //db<Controller>(TRC) << "[CONTROLLER] EXIT \n";
                    break;
                case Keyboard::Move::P:
                    //db<Controller>(TRC) << "[CONTROLLER] PAUSE PRESSIONADO \n";
                    if (_game_state == RUNNING) {
                        //db<Controller>(TRC) << "[CONTROLLER] PAUSE \n";
                        // SUPEND EM TODAS, EXCETO WINDOW E KEYBOARD
                    for (auto thread : _enemy_threads) thread -> suspend();
                        _player_thread -> suspend();
                        _game_state = PAUSED;
                    } else if (_game_state == PAUSED) {
                        for (auto thread : _enemy_threads) thread -> resume();
                        _player_thread -> resume();
                        _game_state = RUNNING;
                        //db<Controller>(TRC) << "[CONTROLLER] UNPAUSE \n";
                    }
                    break;
                default:
                break;
                }
            }
        } else {
            //db<Controller>(TRC) << "[CONTROLLER] EMPTY\n";
            //db<Controller>(TRC) << "[CONTROLLER] GAME ESTATE " << _game_state << "\n";
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

__END_API
