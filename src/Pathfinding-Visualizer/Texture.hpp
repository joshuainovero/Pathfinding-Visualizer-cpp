#ifndef TEXTURE_H
#define TEXTURE_H
#include <SFML/Graphics.hpp>

class Texture_ {
private:

    sf::Texture visualize_texture;
    sf::Texture astar_cb_texture;
    sf::Texture dijkstra_cb_texture;
    sf::Texture bfs_cb_texture;
    sf::Texture dfs_cb_texture;
    sf::Texture rec_cb_texture;
    sf::Texture rand_cb_texture;
    sf::Texture check_texture;
    sf::Texture check2_texture;
    sf::Texture generate_texture;
    sf::Texture clear_texture;
    sf::Texture legend_texture;
    sf::Texture help_texture;

    sf::Sprite visualize_sprite;
    sf::Sprite astar_cb_sprite;
    sf::Sprite dijkstra_cb_sprite;
    sf::Sprite bfs_cb_sprite;
    sf::Sprite dfs_cb_sprite;
    sf::Sprite rec_cb_sprite;
    sf::Sprite rand_cb_sprite;
    sf::Sprite check_sprite;
    sf::Sprite check2_sprite;
    sf::Sprite generate_sprite;
    sf::Sprite clear_sprite;
    sf::Sprite legend_sprite;
    sf::Sprite help_sprite;

    sf::Text algo_choice_text;
    sf::Text astar_text;
    sf::Text dijkstra_text;
    sf::Text bfs_text;
    sf::Text dfs_text;
    sf::Text terrain_text;
    sf::Text recursive_maze_text;
    sf::Text random_terrain_text;
    sf::Font font;

    sf::RectangleShape thematic_break;
    


public:

    sf::Text algorithm_log_text;
    
    float visualize_ranges[4];
    float generate_ranges[4];
    float clear_ranges[4];
    float astar_ranges[4];
    float dijkstra_ranges[4];
    float bfs_ranges[4];
    float dfs_ranges[4];
    float rm_ranges[4];
    float rand_ranges[4];
    float help_ranges[4];

    template<typename T>
    void auto_scale(float n, T &obj);

    template<typename T>
    void set_position_center(float n, T &obj);

    template<typename T>
    void set_position_left(float n, T &obj);

    void set_ranges(float ranges_[4], sf::Sprite &sprite, bool center);

    void load_image(sf::Texture &texture, sf::Sprite &sprite, const char *file, float scale_n, float pos_y, bool center);

    void load_text(sf::Text &text, sf::Color color, const char *content, float size, bool center, uint32_t y);

    void position_checkbox(sf::Sprite &sprite, sf::Text &text, int pos_order);

    void position_check(int pos_order);

    void position_maze_buttons();

    void drawSprites(sf::RenderWindow* window);

    bool clickable_in_range(sf::RenderWindow* window, float ranges_[4], sf::Mouse mouse_pos);
    
    Texture_();
};


#endif // TEXTURE_H