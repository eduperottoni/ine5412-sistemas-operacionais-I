#include "classes/controller.h"
#include "classes/bullet.h"

__BEGIN_API

std::queue<Keyboard::Move> Controller::_action_queue;
Controller::State Controller::_game_state;
std::queue<Keyboard::Move>* Controller::_player_queue;
// std::list<Bullet>* Controller::_bullet_list;

void Controller::run() {
    while (true) {
        // _bullet_list->remove_if([](Bullet* bullet) {
        //     if(bullet->out_of_screen()){
        //         db<Controller>(TRC) << "[CONTROLLER] REMOVENDO BULLET DA LISTA" << "\n";
        //         return true;
        //     };
        //     return false;
        // });
        auto it = _bullet_list->begin();
        while (it != _bullet_list->end()) {
            if ((*it)->out_of_screen()) {
                db<Controller>(TRC) << "[CONTROLLER] ENTREI NO LOOP" << "\n";
                delete *it;
                it = _bullet_list->erase(it);
            } else {
                ++it;
            }
        }
        // for (auto bullet : *_bullet_list){
        //     db<Controller>(TRC) << "[CONTROLLER] ENTREI NO LOOP" << "\n";
        //     if (!bullet -> out_of_screen()) {
        //         db<Controller>(TRC) << "[CONTROLLER] TENTAR ATUALIZAR" << "\n";
        //         bullet -> update();
        //         db<Controller>(TRC) << "[CONTROLLER] ATUALIZEI" << "\n";
        //     } else {
        //         // _bullet_list -> remove_if([&bullet](Bullet* ptr) { return ptr == bullet; });
        //         db<Controller>(TRC) << "[CONTROLLER] REMOVENDO BULLET DA LISTA" << "\n";
        //         _bullet_list->erase(std::remove(_bullet_list->begin(), _bullet_list->end(), bullet), _bullet_list->end());
        //         // delete bullet;
        //         db<Controller>(TRC) << "[CONTROLLER] REMOVI BULLET DA LISTA" << "\n";
        //     }
        // }
        // auto it = _bullet_list->begin();
        // while (it != _bullet_list->end()) {
        //     if ((*it)->out_of_screen()) {
        //         delete *it;
        //         it = _bullet_list->erase(it);
        //     } else {
        //         ++it;
        //     }
        // }
        if (!_action_queue.empty()) {
            Keyboard::Move move = _action_queue.front();
            _action_queue.pop();
            db<Controller>(TRC) << "[CONTROLLER] NOT EMPTY" << move << "\n";
            // MOVIMENTO DO JOGADOR
            if (move == Keyboard::Move::DOWN || move == Keyboard::Move::LEFT || move == Keyboard::Move::RIGHT || move == Keyboard::Move::UP || move == Keyboard::Move::SHOOT) {
                if (_game_state == RUNNING) _player_queue -> push(move);
            } else {
                // MOVIMENTO DE CONTROLE DO JOGO
                switch (move) {
                case Keyboard::Move::EXIT:
                    db<Controller>(TRC) << "[CONTROLLER] EXIT \n";
                    break;
                case Keyboard::Move::P:
                    db<Controller>(TRC) << "[CONTROLLER] PAUSE PRESSIONADO \n";
                    if (_game_state == RUNNING) {
                        db<Controller>(TRC) << "[CONTROLLER] PAUSE \n";
                        // SUPEND EM TODAS, EXCETO WINDOW E KEYBOARD
                        for (auto thread : _enemy_threads) thread -> suspend();
                        _player_thread -> suspend();
                        _game_state = PAUSED;
                    } else if (_game_state == PAUSED) {
                        for (auto thread : _enemy_threads) thread -> resume();
                        _player_thread -> resume();
                        _game_state = RUNNING;
                        db<Controller>(TRC) << "[CONTROLLER] UNPAUSE \n";
                    }
                    break;
                default:
                break;
                }
            }
        } else {
            db<Controller>(TRC) << "[CONTROLLER] EMPTY\n";
            db<Controller>(TRC) << "[CONTROLLER] GAME ESTATE " << _game_state << "\n";
        }
        Thread::yield();
    }
}


Controller::~Controller() {
}

std::queue<Keyboard::Move>* Controller::get_action_queue(){
    db<Controller>(TRC) << "[CONTROLLER] Entrei no getter do _action_queue! \n";
    return &_action_queue;
}

__END_API
