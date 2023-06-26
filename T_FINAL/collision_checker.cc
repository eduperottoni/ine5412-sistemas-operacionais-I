#include "classes/collision_checker.h"
#include "classes/bullet.h"

__BEGIN_API

sf::Sprite* CollisionChecker::_player_sprite;
list<sf::Sprite*>* CollisionChecker::_enemies_sprites;
list<Bullet*>* CollisionChecker::_enemies_bullets_list;
list<Bullet*>* CollisionChecker::_player_bullets_list;
queue<CollisionChecker::Collision*>* CollisionChecker::_collision_queue;

bool CollisionChecker::check_collision(const sf::Sprite* sprite1, const sf::Sprite* sprite2){
    sf::FloatRect rect1 = sprite1 -> getGlobalBounds();
    sf::FloatRect rect2 = sprite2 -> getGlobalBounds();

    return rect1.intersects(rect2);
}

bool CollisionChecker::check_bullet_enemy_collision() {
    bool collision = false;
    db<CollisionChecker>(INF) << "[CollisionChecker] ENTREI NO CHECK_BULLET_ENEMY_COLLISION!\n";
    unsigned int counter_enemy = 0;
    for (auto enemy_sprite : *_enemies_sprites) {
        unsigned int counter_bullet = 0;
        for (auto bullet : *_player_bullets_list) {
            if  (check_collision(bullet -> get_sprite(), enemy_sprite)){
                _collision_queue->push(new Collision(CollisionType::BULLET_ENEMY, counter_bullet, counter_enemy));
                collision = true;
                break;
            }
            counter_bullet++;
        }
        counter_enemy++;
    }
    return collision;
}

bool CollisionChecker::check_bullet_bullet_collision() {
    bool collision = false;
    db<CollisionChecker>(INF) << "[CollisionChecker] ENTREI NO CHECK_BULLET_BULLET_COLLISION!\n";
    unsigned int counter_enemy_bullet = 0;
    for (auto enemy_bullet : *_enemies_bullets_list) {
        unsigned int counter_player_bullet = 0;
        for (auto player_bullet : *_player_bullets_list) {
            if  (check_collision(player_bullet -> get_sprite(), enemy_bullet -> get_sprite())){
                db<CollisionChecker>(INF) << "[CollisionChecker] COLISÃO BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n";
                db<CollisionChecker>(INF) << "[CollisionChecker] COLISÃO BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n";
                _collision_queue->push(new Collision(CollisionType::BULLET_BULLET, counter_player_bullet, counter_enemy_bullet));
                collision = true;
                break;
            }
            counter_player_bullet++;
        }
        counter_enemy_bullet++;
    }
    return collision;
}

bool CollisionChecker::check_enemy_player_collision(){
    db<CollisionChecker>(INF) << "[CollisionChecker] ENTREI NO CHECK_ENEMY_PLAYER_COLLISION!\n";
    unsigned int counter_enemy = 0;
    for (auto enemy_sprite : *_enemies_sprites) {
        if (check_collision(enemy_sprite, _player_sprite)) {
            db<CollisionChecker>(INF) << "[CollisionChecker] COLISAO PLAYER E NAVE INIMIGA!\n";
            Collision* colisao = new Collision(CollisionType::PLAYER_ENEMY, -1, counter_enemy);
            db<CollisionChecker>(INF) << "[CollisionChecker] COLISAO CRIADA!\n";
            if (_collision_queue == nullptr) {
                db<CollisionChecker>(INF) << "[CollisionChecker] NULL POINTER!\n";
            }
            _collision_queue->push(colisao);
            
            db<CollisionChecker>(INF) << "[CollisionChecker] PUSH NA COLLISION QUEUE!\n";
            return true;
        }
        counter_enemy++;
    }
    return false;
};

// bool CollisionChecker::check_enemy_enemy_collision(){
//     return false;
// };

void CollisionChecker::run(){
    while (true) {
        db<CollisionChecker>(INF) << "[CollisionChecker] CollisionChecker dá oi!\n";
        if (check_bullet_enemy_collision()){
            db<CollisionChecker>(INF) << "[CollisionChecker] BULLET_ENEMY_COLLISION\n";
        }
        if (check_enemy_player_collision()){
            db<CollisionChecker>(INF) << "[CollisionChecker] ENEMY_PLAYER_COLLISION\n";
        }
        if (check_bullet_bullet_collision()){
            db<CollisionChecker>(INF) << "[CollisionChecker] BULLET_BULLET_COLLISION\n";
        }
        db<CollisionChecker>(INF) << "[CollisionChecker] AQUI\n";


        Thread::yield();
    }
}

__END_API