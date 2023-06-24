#ifndef collision_checker_h
#define collision_checker_h

#include <SFML/Graphics.hpp>
#include <list>
#include "../src/lib/thread.h"


__BEGIN_API

using namespace std;
class CollisionChecker
{
public:
    CollisionChecker(sf::Sprite* player_sprite, list<sf::Sprite*> enemies_sprites_list);

    ~CollisionChecker();
    
    void run();
private:
    static sf::Sprite* _player_sprite;
    static list<sf::Sprite*> _enemies_sprites;
    //Inserir também os sprites das balas

    // static Game::State* _game_state;
};


__END_API


#endif