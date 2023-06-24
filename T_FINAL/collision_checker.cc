#include "classes/collision_checker.h"

__BEGIN_API

sf::Sprite* CollisionChecker::_player_sprite;
list<sf::Sprite*> CollisionChecker::_enemies_sprites;
// Game::State* CollisionChecker::_game_state;

CollisionChecker::CollisionChecker(sf::Sprite* player_sprite, list<sf::Sprite*> enemies_sprites_list){
    // _player_sprite = player_sprite;
    // for (auto sprite : enemies_sprites_list) _enemies_sprites.push_back(sprite);
    // _game_state = state;
}

bool check_collision(const sf::Sprite& sprite1, const sf::Sprite& sprite2){
    sf::FloatRect rect1 = sprite1.getGlobalBounds();
    sf::FloatRect rect2 = sprite2.getGlobalBounds();

    return rect1.intersects(rect2);
}

void CollisionChecker::run(){
    while (true){
        db<CollisionChecker>(INF) << "[CollisionChecker] CollisionChecker dá oi!\n";

        // for (auto enemy_sprite : _enemies_sprites){
        //     if (check_collision(enemy_sprite, _player_sprite)){
        //         db<CollisionChecker>(INF) << "[CollisionChecker] COLISÃO ENTRE O JOGADOR E UM INIMIGO\n";
        //     }
        // }





        Thread::yield();
    }
}

__END_API