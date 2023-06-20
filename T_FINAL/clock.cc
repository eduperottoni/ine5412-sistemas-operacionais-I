#include "classes/clock.h"

__BEGIN_API

sf::Clock Clock::_clock;
float Clock::_delta_time;

float Clock::reset()
{
    return _clock.restart().asSeconds();
}

float Clock::get_elapsed_time()
{
    return _clock.getElapsedTime().asSeconds();
}

float Clock::get_delta_time()
{
    return _delta_time;
}

void Clock::set_delta_time()
{
    _delta_time = reset();
}

__END_API