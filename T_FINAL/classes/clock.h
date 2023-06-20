#ifndef clock_h
#define clock_h

#include <SFML/Graphics.hpp>
#include <list>
#include "../src/lib/thread.h"

__BEGIN_API

class Clock
{
public:
    // Resets the clock
    static float reset();
    // Sets the delta time
    static void set_delta_time();
    // Sets the delta time
    static float get_delta_time();
private:
    static sf::Clock _clock;
    static float _delta_time;
    // Gets the elapsed time
    static float get_elapsed_time();
};


__END_API


#endif