#ifndef NODE_H
#define NODE_H
#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <vector>

#define PATH_COLOR 255, 254, 106
#define OBSTRUCTION_COLOR 12, 53, 71
#define VISITED_COLOR 68, 204, 228
#define OPEN_COLOR sf::Color::Cyan
#define START_COLOR sf::Color::Green
#define TARGET_COLOR sf::Color::Red
#define BLANK_COLOR sf::Color::White

class Node {
public:
    std::vector<Node*> neighbors;
    sf::RectangleShape tile_shape;
    sf::Color color;
    uint32_t row, col;
    uint32_t total_rows;
    float x, y;
    float width;
    bool visited_maze;

    void draw_node(sf::RenderWindow *window);
    Node(uint32_t row, uint32_t col, float width, uint32_t total_rows);


    /* Tile state */
    void update_neighbors(std::vector<Node*> *board);
    void set_start();
    void set_target();
    void set_obstruction();
    void set_visited();
    void set_open();
    void set_path();
    void reset();
    bool is_obstruction();
    sf::Vector2i get_coord();
};

#endif // NODE_H