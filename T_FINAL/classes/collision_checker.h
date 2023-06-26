#ifndef collision_checker_h
#define collision_checker_h

#include <SFML/Graphics.hpp>
#include <list>
#include <queue>
#include "../src/lib/thread.h"
#include "../classes/game_config.h"


__BEGIN_API

using namespace std;
class CollisionChecker
{
public:
    enum CollisionType{
        BULLET_ENEMY,
        ENEMY_ENEMY,
        PLAYER_ENEMY,
        BULLET_PLAYER,
        BULLET_BULLET
    };
    class Collision {
    public:
        Collision(CollisionType type, int id1, int id2){
            _collision_type = type; 
            _obj_id1 = id1;
            _obj_id2 = id2;
        };
        CollisionType _collision_type;
        int _obj_id1;
        int _obj_id2;
        ~Collision(){};
        // int get_id1(){
        //     return _obj_id1;
        // };
        // int get_id2(){
        //     return _obj_id2;
        // };
        // CollisionType get_collision_type(){
        //     return _collision_type;
        // };
    // private:
    };
    CollisionChecker(sf::Sprite* player_sprite, list<sf::Sprite*>* enemies_sprites_list, list<Bullet*>* player_bullets_list, list<Bullet*>* enemies_bullets_list, queue<CollisionChecker::Collision*>* collision_queue){
        _player_bullets_list = player_bullets_list;
        _enemies_bullets_list = enemies_bullets_list;
        _enemies_sprites = enemies_sprites_list;
        _player_sprite = player_sprite;
        _collision_queue = collision_queue;
    };

    ~CollisionChecker(){};
    
    static void run();

    static bool check_bullet_enemy_collision();
    static bool check_enemy_player_collision();
    // static bool check_enemy_enemy_collision();
    static bool check_bullet_bullet_collision();
    static bool check_bullet_player_collision();
    static bool check_collision(const sf::Sprite* sprite1, const sf::Sprite* sprite2);
private:
    static sf::Sprite* _player_sprite;
    static list<sf::Sprite*>* _enemies_sprites;
    //Inserir também os sprites das balas
    static list<Bullet*>* _enemies_bullets_list;
    static list<Bullet*>* _player_bullets_list;
    static queue<CollisionChecker::Collision*>* _collision_queue;

    // static Game::State* _game_state;
};


__END_API


#endif