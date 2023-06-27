#ifndef ENEMY_TRACKER_H
#define ENEMY_TRACKER_H

#include "../classes/enemy.h"
#include "../src/lib/traits.h"
#include "../src/lib/thread.h"
#include "../classes/window.h"
#include "../classes/bullet.h"
#include "sprite.h"
#include "spaceship.h"

#include <iostream>
#include <tuple>

__BEGIN_API


class EnemyTracker : virtual public Enemy {
public:
    EnemyTracker(float scale, int size, float speed, const std::map<Orientation, std::string>& paths, Orientation initial_orientation, Clock* clock, int x, int y, std::list<Bullet*>* bullet_list, sf::Sprite* player_sprite, int quadrante)
    : Sprite(scale, size, paths, initial_orientation, x, y), 
    MovingSprite(scale, size, speed, paths, initial_orientation, clock, x, y, quadrante),
    Spaceship(scale, size, speed, paths, initial_orientation, clock, x, y, bullet_list, quadrante),
    Enemy(scale, size, speed, paths, initial_orientation, clock, x, y, bullet_list, quadrante) {
        _player_sprite = player_sprite;
    };

    // Método para movimentar o personagem
    void run() override;

    // Método para o tiro do inimigo
    void shoot();
private:
    sf::Sprite* _player_sprite;
};

__END_API

#endif