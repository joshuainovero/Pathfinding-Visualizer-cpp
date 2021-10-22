#include "Texture.hpp"
#include <iostream>

void Texture_::load_image(sf::Texture &texture, sf::Sprite &sprite, const char *file, float scale_n, float pos_y, bool center){
    texture.loadFromFile(file);
    texture.setSmooth(true);
    sprite.setTexture(texture);

    if (center){
        sprite.setOrigin(sf::Vector2f((sprite.getPosition().x + sprite.getTexture()->getSize().x)/2.0f, (sprite.getPosition().y + sprite.getTexture()->getSize().y)/2.0f));
        auto_scale(scale_n, sprite);
        set_position_center(pos_y,sprite);
    }
    else {
        auto_scale(scale_n, sprite);
        set_position_left(pos_y, sprite);
    }
}

void Texture_::load_text(sf::Text &text, sf::Color color, const char *content, float size, bool center, uint32_t y){
    text.setFont(font);
    text.setString(content);
    text.setFillColor(color);
    text.setCharacterSize((size/768.0f) * sf::VideoMode::getDesktopMode().height);
    if (center){
        uint32_t origin_x = (text.getPosition().x + text.getLocalBounds().width)/2.0f;
        uint32_t origin_y = (text.getPosition().y + text.getLocalBounds().height)/2.0f;
        text.setOrigin(origin_x, origin_y);
        set_position_center(y, text);
    }
    else {
        set_position_left(y, text);
    }
}

void Texture_::set_ranges(float ranges_[4], sf::Sprite &sprite, bool center){
    float x1;
    float x2;
    float y1;
    float y2;
    if (center){
        x1 = sprite.getPosition().x - ((sprite.getTexture()->getSize().x * sprite.getScale().x)/2.0f);
        x2 = sprite.getPosition().x + ((sprite.getTexture()->getSize().x * sprite.getScale().x)/2.0f);
        y1 = sprite.getPosition().y - ((sprite.getTexture()->getSize().y * sprite.getScale().y)/2.0f);
        y2 = sprite.getPosition().y + ((sprite.getTexture()->getSize().y * sprite.getScale().y)/2.0f);
    }
    else {
        x1 = sprite.getPosition().x;
        x2 = x1 + (sprite.getTexture()->getSize().x * sprite.getScale().x);
        y1 = sprite.getPosition().y;
        y2 = y1 + (sprite.getTexture()->getSize().y * sprite.getScale().y);
    }
    ranges_[0] = x1;
    ranges_[1] = x2;
    ranges_[2] = y1;
    ranges_[3] = y2;
}

template<typename T>
void Texture_::set_position_center(float n, T &obj){
    float pos_x = (sf::VideoMode::getDesktopMode().height) + ((sf::VideoMode::getDesktopMode().width - sf::VideoMode::getDesktopMode().height)/2.0f);
    obj.setPosition(pos_x, (n/768.0f) * sf::VideoMode::getDesktopMode().height);
}   

template<typename T>
void Texture_::set_position_left(float n, T &obj){
    float pos_x = sf::VideoMode::getDesktopMode().height;
    obj.setPosition(pos_x, (n/768.0f) * sf::VideoMode::getDesktopMode().height);
}

template<typename T>
void Texture_::auto_scale(float n,T &obj){
    obj.setScale(sf::Vector2f((n/768.0f) * sf::VideoMode::getDesktopMode().height, (n/768.0f) * sf::VideoMode::getDesktopMode().height));
}

void Texture_::position_checkbox(sf::Sprite &sprite, sf::Text &text, int pos_order){
    uint32_t checkbox_x, text_x;
    if (pos_order == 0 || pos_order == 2 || pos_order == 4) {
        checkbox_x = (85.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
        text_x = checkbox_x + ((10.0f/768.0f) * sf::VideoMode::getDesktopMode().height);
        sprite.setPosition(sprite.getPosition().x + checkbox_x, sprite.getPosition().y);
        text.setPosition((text.getPosition().x + text_x) + (sprite.getTexture()->getSize().x * sprite.getScale().x), text.getPosition().y);
    }
    else if (pos_order == 1 || pos_order == 3 || pos_order == 5){
        checkbox_x = ((85.0f/768.0f) * sf::VideoMode::getDesktopMode().height) + ((235.0f/768.0f) * sf::VideoMode::getDesktopMode().height);
        text_x = checkbox_x + ((10.0f/768.0f) * sf::VideoMode::getDesktopMode().height);
        sprite.setPosition(sprite.getPosition().x + checkbox_x, sprite.getPosition().y);
        text.setPosition((text.getPosition().x + text_x) + (sprite.getTexture()->getSize().x * sprite.getScale().x), text.getPosition().y);
    }
}

void Texture_::position_check(int pos_order){
    if (pos_order == 0)
        check_sprite.setPosition((astar_cb_sprite.getPosition().x) - ((3.0f/768.0f) * sf::VideoMode::getDesktopMode().height), astar_cb_sprite.getPosition().y - ((12.0f/768.0f) * sf::VideoMode::getDesktopMode().height));
    if (pos_order == 1)
        check_sprite.setPosition((dijkstra_cb_sprite.getPosition().x) - ((3.0f/768.0f) * sf::VideoMode::getDesktopMode().height), dijkstra_cb_sprite.getPosition().y - ((12.0f/768.0f) * sf::VideoMode::getDesktopMode().height));
    if (pos_order == 2)
        check_sprite.setPosition((bfs_cb_sprite.getPosition().x) - ((3.0f/768.0f) * sf::VideoMode::getDesktopMode().height), bfs_cb_sprite.getPosition().y - ((12.0f/768.0f) * sf::VideoMode::getDesktopMode().height));
    if (pos_order == 3)
        check_sprite.setPosition((dfs_cb_sprite.getPosition().x) - ((3.0f/768.0f) * sf::VideoMode::getDesktopMode().height), dfs_cb_sprite.getPosition().y - ((12.0f/768.0f) * sf::VideoMode::getDesktopMode().height));
    if (pos_order == 4){
        check2_sprite.setPosition((rec_cb_sprite.getPosition().x) - ((3.0f/768.0f) * sf::VideoMode::getDesktopMode().height), rec_cb_sprite.getPosition().y - ((12.0f/768.0f) * sf::VideoMode::getDesktopMode().height));
    }
    if (pos_order == 5){
        check2_sprite.setPosition((rand_cb_sprite.getPosition().x) - ((3.0f/768.0f) * sf::VideoMode::getDesktopMode().height), rand_cb_sprite.getPosition().y - ((12.0f/768.0f) * sf::VideoMode::getDesktopMode().height));
    }
}

bool Texture_::clickable_in_range(float ranges_[4], sf::Mouse mouse_pos){
    sf::Vector2f pos(mouse_pos.getPosition().x, mouse_pos.getPosition().y);
    return ((pos.x >= ranges_[0] && pos.x <= ranges_[1]) && (pos.y >= ranges_[2] && pos.y <= ranges_[3]));
}

void Texture_::position_maze_buttons(){
    float x_movement = (110.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    generate_sprite.setPosition(generate_sprite.getPosition().x - x_movement, generate_sprite.getPosition().y);
    clear_sprite.setPosition(clear_sprite.getPosition().x + x_movement, clear_sprite.getPosition().y);
}

Texture_::Texture_(){
    font.loadFromFile("Font/OpenSans-Light.ttf");

    load_image(visualize_texture, visualize_sprite, "Assets/visualize.png", 0.40f, 60, true);
    load_image(astar_cb_texture, astar_cb_sprite, "Assets/checkbox.png", 0.10f, 196, false);
    load_image(dijkstra_cb_texture, dijkstra_cb_sprite, "Assets/checkbox.png", 0.10f, 196, false);
    load_image(bfs_cb_texture, bfs_cb_sprite, "Assets/checkbox.png", 0.10f, 260, false);
    load_image(dfs_cb_texture, dfs_cb_sprite, "Assets/checkbox.png", 0.10f, 260, false);
    load_image(rec_cb_texture, rec_cb_sprite, "Assets/checkbox.png", 0.10f, 366, false);
    load_image(rand_cb_texture, rand_cb_sprite, "Assets/checkbox.png", 0.10f, 366, false);
    load_image(check_texture, check_sprite, "Assets/check.png", 0.34f, 196, false);
    load_image(check2_texture, check2_sprite, "Assets/check.png", 0.34f, 196, false);
    load_image(legend_texture, legend_sprite, "Assets/legend.png", 0.55f, 620, true);
    load_image(generate_texture, generate_sprite, "Assets/generate.png", 0.19f, 430, true);
    load_image(clear_texture, clear_sprite, "Assets/clearboard.png", 0.19f, 430, true);
    load_image(help_texture, help_sprite, "Assets/help.png", 0.23f, 13, false);

    load_text(algo_choice_text, sf::Color::Black, "Pick an Algorithm:", 26.0f, true, 150);
    load_text(astar_text, sf::Color::Black, "A* Search", 18.0f, false, 196);
    load_text(dijkstra_text, sf::Color::Black, "Dijkstra's Algorithm", 18.0f, false, 196);
    load_text(bfs_text, sf::Color::Black, "Breadth-First Search", 18.0f, false, 260);
    load_text(dfs_text, sf::Color::Black, "Depth-First Search", 18.0f, false, 260);
    load_text(terrain_text, sf::Color::Black, "Terrain: ", 26.0f, true, 320);
    load_text(recursive_maze_text, sf::Color::Black, "Recursive Maze", 18.0f, false, 366);
    load_text(random_terrain_text, sf::Color::Black, "Random Terrain", 18.0f, false, 366);
    load_text(algorithm_log_text, sf::Color::Black, "", 14.0f, false, 0);

    position_checkbox(astar_cb_sprite, astar_text, 0);
    position_checkbox(dijkstra_cb_sprite, dijkstra_text, 1);
    position_checkbox(bfs_cb_sprite, bfs_text, 2);
    position_checkbox(dfs_cb_sprite, dfs_text, 3);
    position_checkbox(rec_cb_sprite, recursive_maze_text, 4);
    position_checkbox(rand_cb_sprite, random_terrain_text, 5);
    
    position_check(0);
    position_check(4);
    position_maze_buttons();

    set_ranges(visualize_ranges, visualize_sprite, true);
    set_ranges(generate_ranges, generate_sprite, true);
    set_ranges(clear_ranges, clear_sprite, true);
    set_ranges(astar_ranges, astar_cb_sprite, false);
    set_ranges(dijkstra_ranges, dijkstra_cb_sprite, false);
    set_ranges(bfs_ranges, bfs_cb_sprite, false);
    set_ranges(dfs_ranges, dfs_cb_sprite, false);
    set_ranges(rm_ranges, rec_cb_sprite, false);
    set_ranges(rand_ranges, rand_cb_sprite, false);

    /* Manual Calculations */

    float y_pos_line = (485.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    float line_weight = (1.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    float line_dec = (110.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    float center_panel = ((sf::VideoMode::getDesktopMode().height) + (sf::VideoMode::getDesktopMode().width - sf::VideoMode::getDesktopMode().height)/2.0f);
    thematic_break.setSize(sf::Vector2f((sf::VideoMode::getDesktopMode().width - sf::VideoMode::getDesktopMode().height) - line_dec, line_weight));
    thematic_break.setOrigin(sf::Vector2f(thematic_break.getSize().x/2.0f, thematic_break.getSize().y/2.0f));
    thematic_break.setFillColor(sf::Color::Black);

    algorithm_log_text.setPosition(algorithm_log_text.getPosition().x + ((20.0f/768.0f) * sf::VideoMode::getDesktopMode().height), algorithm_log_text.getPosition().y + ((10.0f/768.0f) * sf::VideoMode::getDesktopMode().height));

    thematic_break.setPosition(center_panel, y_pos_line);

    float excess_panel = sf::VideoMode::getDesktopMode().width - sf::VideoMode::getDesktopMode().height;
    help_sprite.setPosition((help_sprite.getPosition().x + excess_panel) - ((67.0f/768.0f) * sf::VideoMode::getDesktopMode().height), help_sprite.getPosition().y);
    set_ranges(help_ranges, help_sprite, false);
}