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

    void set_frame_limit(int limit);
    int get_frame_limit() const;

    void set_kills_to_lvl_2(int limit);
    int get_kills_to_lvl_2() const;

    void set_kills_to_lvl_3(int limit);
    int get_kills_to_lvl_3() const;

    void set_key_repeat_enabled(bool enabled);
    bool is_key_repeat_enabled() const;

    void set_texture_path(const std::string& path);
    string get_texture_path() const;

    void set_video_size(const std::tuple<int, int>& new_video_size);
    std::tuple<int, int> get_video_size() const;

    void set_sprites_scale(const float& scale);
    float get_sprites_scale() const;

    void set_enemies_speed_lvl_1(const float& enemies_speed);
    float get_enemies_speed_lvl_1() const;

    void set_enemies_speed_lvl_2(const float& enemies_speed);
    float get_enemies_speed_lvl_2() const;

    void set_enemies_speed_lvl_3(const float& enemies_speed);
    float get_enemies_speed_lvl_3() const;

    void set_player_speed(const float& player_speed);
    float get_player_speed() const;

    void set_screen_sprite_scale(const float& screen_sprite_scale);
    float get_screen_sprite_scale() const;

    void set_start_panel(const std::tuple<float, float>& start_panel);
    std::tuple<float, float> get_start_panel() const;

    void set_font_size(const float& font_size);
    float get_font_size() const;

    void set_player_health(int player_health);
    int get_player_health() const;

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
    unsigned int _kills_to_lvl_2;
    unsigned int _kills_to_lvl_3;
    bool _key_repeat_enabled;
    string _texture_path;
    std::tuple<int, int> _video_size;
    float _sprites_scale;
    int _enemies_speed_lvl_1;
    int _enemies_speed_lvl_2;
    int _enemies_speed_lvl_3;
    float _player_speed;
    int _player_health;
    float _screen_sprite_scale;
    std::tuple<float, float> _start_panel;
    float _font_size;
};

#endif  // GAME_CONFIG_H