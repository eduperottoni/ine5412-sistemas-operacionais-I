#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <SFML/Graphics.hpp>
#include <string>

class GameConfig {
public:
    static GameConfig& get_instance();

    void set_video_mode(unsigned int width, unsigned int height);
    sf::VideoMode get_video_mode() const;

    void set_window_title(const std::string& title);
    std::string get_window_title() const;

    void set_frame_limit(unsigned int limit);
    unsigned int get_frame_limit() const;

    void set_key_repeat_enabled(bool enabled);
    bool is_key_repeat_enabled() const;

    void set_texture_path(const std::string& path);
    std::string get_texture_path() const;

private:
    GameConfig(){};
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    sf::VideoMode _video_mode;
    std::string _window_title;
    unsigned int _frame_limit;
    bool _key_repeat_enabled;
    std::string _texture_path;
};

#endif  // GAME_CONFIG_H