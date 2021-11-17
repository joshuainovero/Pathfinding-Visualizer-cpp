#ifndef GRAPH_H
#define GRAHP_H
#include "Node.hpp"
#include "Astar.hpp"
#include "Dijkstra.hpp"
#include "BFS.hpp"
#include "DFS.hpp"
#include "RecursiveMaze.hpp"
#include "RandomTerrain.hpp"
#include <vector>

enum Maze_Algorithms {RM, RAND_T};

class Graph {
public:
    std::vector<Node*> *board;  
    sf::RectangleShape horLine, vertLine;
    sf::RectangleShape green_tile, red_tile;
    Search_ *a_star, *dijkstra, *BFS, *DFS;
    Algorithm_ *recursive_maze, *random_terrain;
    Search_* current_search_algo;
    Algorithm_* current_terrain_algo;
    Maze_Algorithms current_maze_algo;
    Node* start_node;
    Node* end_node;
    uint32_t board_width;
    uint32_t total_rows;
    float tile_gap;

    void draw_grid(sf::RenderWindow *window);
    void draw_tiles(sf::RenderWindow *window, bool visualize_visiting);
    void construct_graph(uint32_t rows, uint32_t width);
    sf::Vector2u rowcol_pos_click(sf::Vector2i pos);
    Graph(uint32_t rows, uint32_t width);
};

#endif // GRAPH_H