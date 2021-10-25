#ifndef GRAPH_H
#define GRAHP_H
#include "Node.hpp"
#include "Algorithms.hpp"
#include <vector>

enum PF_Algorithms {Astar, Dijkstra, BFS, DFS};
enum Maze_Algorithms {RM, RAND_T};

class Graph {
public:
    std::vector<Node*> *board;  
    sf::RectangleShape horLine, vertLine;
    sf::RectangleShape green_tile, red_tile;
    Algorithms_ algorithms;
    PF_Algorithms current_algo;
    Maze_Algorithms current_maze_algo;
    Node* start_node;
    Node* end_node;
    uint32_t board_width;
    uint32_t total_rows;
    float tile_gap;

    void draw_grid(sf::RenderWindow *window);
    void draw_tiles(sf::RenderWindow *window, bool visualize_visiting);
    void construct_graph(uint32_t rows, uint32_t width);
    sf::Vector2i rowcol_pos_click(sf::Vector2i pos);
    Graph(uint32_t rows, uint32_t width);
};

#endif // GRAPH_H