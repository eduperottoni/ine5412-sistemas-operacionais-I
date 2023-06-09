#include "classes/game_config.h"

GameConfig& GameConfig::get_instance() {
    static GameConfig instance;
    return instance;
}

void GameConfig::set_video_size(const std::tuple<int, int>& new_video_size) {
    _video_size = new_video_size;
}

std::tuple<int, int> GameConfig::get_video_size() const{
    return _video_size;
}

void GameConfig::set_window_title(const std::string& title) {
    _window_title = title;
}

std::string GameConfig::get_window_title() const {
    return _window_title;
}

void GameConfig::set_frame_limit(int limit) {
    _frame_limit = limit;
}
int GameConfig::get_frame_limit() const {
    return _frame_limit;
}

void GameConfig::set_kills_to_lvl_2(int limit) {
    _kills_to_lvl_2 = limit;
}
int GameConfig::get_kills_to_lvl_2() const {
    return _kills_to_lvl_2;
}

void GameConfig::set_kills_to_lvl_3(int limit) {
    _kills_to_lvl_3 = limit;
}
int GameConfig::get_kills_to_lvl_3() const {
    return _kills_to_lvl_3;
}

void GameConfig::set_number_of_enemies(int number) {
    _number_of_enemies = number;
}
int GameConfig::get_number_of_enemies() const {
    return _number_of_enemies;
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

void GameConfig::set_sprites_scale(const float& scale){
    _sprites_scale = scale;
}

float GameConfig::get_sprites_scale() const{
    return _sprites_scale;
}

void GameConfig::set_enemies_speed_lvl_1(const float& enemies_speed){
    _enemies_speed_lvl_1 = enemies_speed;
}


void GameConfig::set_enemies_speed_lvl_2(const float& enemies_speed){
    _enemies_speed_lvl_2 = enemies_speed;
}


void GameConfig::set_enemies_speed_lvl_3(const float& enemies_speed){
    _enemies_speed_lvl_3 = enemies_speed;
}

float GameConfig::get_enemies_speed_lvl_1() const{
    return _enemies_speed_lvl_1;
}

float GameConfig::get_enemies_speed_lvl_2() const{
    return _enemies_speed_lvl_2;
}


float GameConfig::get_enemies_speed_lvl_3() const{
    return _enemies_speed_lvl_3;
}


void GameConfig::set_player_speed(const float& player_speed){
    _player_speed = player_speed;
}

float GameConfig::get_player_speed() const{
    return _player_speed;
}

void GameConfig::set_player_health(int player_health){
    _player_health = player_health;
}
int GameConfig::get_player_health() const{
    return _player_health;
}

void GameConfig::set_screen_sprite_scale(const float& screen_sprite_scale){
    _screen_sprite_scale = screen_sprite_scale;
}
float GameConfig::get_screen_sprite_scale() const{
    return _screen_sprite_scale;
}

void GameConfig::set_start_panel(const std::tuple<float, float>& start_panel){
    _start_panel = start_panel;
}
std::tuple<float, float> GameConfig::get_start_panel() const{
    return _start_panel;
}

void GameConfig::set_font_size(const float& font_size){
    _font_size = font_size;
}
float GameConfig::get_font_size() const{
    return _font_size;
}


void GameConfig::set_game_state(State state){
    _game_state = state;
}

GameConfig::State* GameConfig::get_game_state() {
    return &_game_state;
}

// void GameConfig::GameConfig::set_usable_screen(const unsigned int x, const unsigned int y){
//     get<0>(_usable_screen) = x;
//     get<1>(_usable_screen) = y;
// }

// unsigned int GameConfig::get_usable_screen_x(){
//     return get<0>(_usable_screen);
// }
// unsigned int GameConfig::get_usable_screen_y(){
//     return get<0>(_usable_screen);
// }