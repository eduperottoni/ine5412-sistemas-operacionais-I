#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <SFML/Graphics.hpp>
#include <string>
#include <tuple>

using namespace std;
class GameConfig {
public:
    static GameConfig& get_instance();

    void set_video_mode(unsigned int width, unsigned int height);
    sf::VideoMode get_video_mode() const;

    void set_window_title(const std::string& title);
    string get_window_title() const;

    void set_frame_limit(unsigned int limit);
    unsigned int get_frame_limit() const;

    void set_key_repeat_enabled(bool enabled);
    bool is_key_repeat_enabled() const;

    void set_texture_path(const std::string& path);
    string get_texture_path() const;

    // void set_usable_screen(const unsigned int x, const unsigned int y);
    // unsigned int get_usable_screen_x();
    // unsigned int get_usable_screen_y();

private:
    GameConfig(){};
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    sf::VideoMode _video_mode;
    string _window_title;
    unsigned int _frame_limit;
    bool _key_repeat_enabled;
    string _texture_path;
    float _enemies_speed;
    float _player_speed;
    // tuple<int, int> _usable_screen;
};

#endif  // GAME_CONFIG_H