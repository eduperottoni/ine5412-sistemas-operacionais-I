#include "classes/collision_checker.h"
#include "classes/bullet.h"

__BEGIN_API

sf::Sprite* CollisionChecker::_player_sprite;
list<sf::Sprite*>* CollisionChecker::_enemies_sprites;
list<Bullet*>* CollisionChecker::_enemies_bullets_list;
list<Bullet*>* CollisionChecker::_player_bullets_list;

bool CollisionChecker::check_collision(const sf::Sprite* sprite1, const sf::Sprite* sprite2){
    sf::FloatRect rect1 = sprite1 -> getGlobalBounds();
    sf::FloatRect rect2 = sprite2 -> getGlobalBounds();

    return rect1.intersects(rect2);
}

bool CollisionChecker::check_bullet_enemy_collision() {
    db<CollisionChecker>(INF) << "[CollisionChecker] ENTREI NO CHECK_BULLET_ENEMY_COLLISION!\n";
    if (_enemies_sprites != nullptr) {
        db<CollisionChecker>(INF) << "[CollisionChecker] NULL POINTER!\n";
    }
    for (auto enemy_sprite : *_enemies_sprites) {
        db<CollisionChecker>(INF) << "[CollisionChecker] FOR1!\n";
        for (auto bullet : *_player_bullets_list) {
            db<CollisionChecker>(INF) << "[CollisionChecker] FOR2!\n";
            if  (check_collision(bullet -> get_sprite(), enemy_sprite)){
                return true;
            }
        }
    }
    return false;
}

bool CollisionChecker::check_enemy_player_collision(){
    db<CollisionChecker>(INF) << "[CollisionChecker] ENTREI NO CHECK_ENEMY_PLAYER_COLLISION!\n";
    for (auto enemy_sprite : *_enemies_sprites) {
        if (check_collision(enemy_sprite, _player_sprite)) {
            db<CollisionChecker>(INF) << "[CollisionChecker] COLISAO PLAYER E NAVE INIMIGA!\n";
            return true;
        }
    }
    return false;
};

bool CollisionChecker::check_enemy_enemy_collision(){
    return false;
};

void CollisionChecker::run(){
    while (true) {
        db<CollisionChecker>(INF) << "[CollisionChecker] CollisionChecker dá oi!\n";
        if (check_bullet_enemy_collision()){
            db<CollisionChecker>(INF) << "[CollisionChecker] BULLET_ENEMY_COLLISION\n";
        }
        if (check_enemy_player_collision()){
            db<CollisionChecker>(INF) << "[CollisionChecker] ENEMY_PLAYER_COLLISION\n";
        }
        db<CollisionChecker>(INF) << "[CollisionChecker] AQUI\n";


        Thread::yield();
    }
}

__END_API