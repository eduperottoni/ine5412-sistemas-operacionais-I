#ifndef collision_checker_h
#define collision_checker_h

#include <SFML/Graphics.hpp>
#include <list>
#include "../src/lib/thread.h"


__BEGIN_API

using namespace std;
class CollisionChecker
{
private:
    sf::Sprite _player_sprite;
    list<sf::Sprite> _enemies_sprites;
    //Inserir também os sprites das balas
public:
    CollisionChecker(sf::Sprite player_sprite, list<sf::Sprite>);
    ~CollisionChecker();
    
    static void run();
};


__END_API


#endif