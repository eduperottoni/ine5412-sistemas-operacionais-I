#include "classes/clock.h"

__BEGIN_API

sf::Clock Clock::_clock;
float Clock::_delta_time;

double Clock::get_current_time(){
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
    long long timestamp = std::chrono::time_point_cast<std::chrono::seconds>(current_time).time_since_epoch().count();
    double timestamp_double = static_cast<double>(timestamp);
    return timestamp_double;
}

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