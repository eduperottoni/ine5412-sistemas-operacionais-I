#include "classes/game_config.h"

GameConfig& GameConfig::get_instance() {
    static GameConfig instance;
    return instance;
}

void GameConfig::set_video_mode(unsigned int width, unsigned int height) {
    _video_mode.width = width;
    _video_mode.height = height;
}

sf::VideoMode GameConfig::get_video_mode() const {
    return _video_mode;
}

void GameConfig::set_window_title(const std::string& title) {
    _window_title = title;
}

std::string GameConfig::get_window_title() const {
    return _window_title;
}

void GameConfig::set_frame_limit(unsigned int limit) {
    _frame_limit = limit;
}

unsigned int GameConfig::get_frame_limit() const {
    return _frame_limit;
}

void GameConfig::set_key_repeat_enabled(bool enabled) {
    _key_repeat_enabled = enabled;
}

bool GameConfig::is_key_repeat_enabled() const {
    return _key_repeat_enabled;
}

void GameConfig::set_texture_path(const std::string& path) {
    _texture_path = path;
}

std::string GameConfig::get_texture_path() const {
    return _texture_path;
}


// void GameConfig::set_usable_screen(const unsigned int x, const unsigned int y){
//     get<0>(_usable_screen) = x;
//     get<1>(_usable_screen) = y;
// }

// unsigned int GameConfig::get_usable_screen_x(){
//     return get<0>(_usable_screen);
// }
// unsigned int GameConfig::get_usable_screen_y(){
//     return get<0>(_usable_screen);
// }