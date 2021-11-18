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
#include <utility>

enum Enum_Search {ASTAR, DIJKSTRA, BFS, DFS};
enum Maze_Algorithms {RM, RAND_T};

class Graph {
public:

    static constexpr float ratio_row = 0.1555555556f;

    Graph(uint32_t rows, uint32_t width);

    void construct_graph(uint32_t rows, uint32_t width);

    void clear_graph();

    void draw_grid(sf::RenderWindow *window);

    void draw_tiles(sf::RenderWindow *window, bool visualize_visiting);
    
    void assign_start(Node* v__);

    void remove_start();

    void remove_end();

    void assign_end(Node* v__);

    void assign_curr_search_algo(Enum_Search v__);

    void assign_curr_terr_algo(Maze_Algorithms v__);

    void draw_ST_tiles(sf::RenderWindow* window, sf::Mouse& mousePos);

    std::vector<Node*>* get_board() const;

    uint32_t get_total_rows() const;

    std::pair<Node*, Node*> STNodes() const;

    Search_* g_curr_search_algo() const;

    Algorithm_* g_curr_terr_algo() const;

    Maze_Algorithms g_curr_maze_algo() const;

    std::vector<Search_*> g_search_algos() const;

    std::vector<Algorithm_*> g_terrain_algos() const;

    sf::Vector2u rowcol_pos_click(sf::Vector2i pos);

private:

    std::vector<Node*> *board;  

    std::vector<Algorithm_*> terrain_algorithms;
    std::vector<Search_*>    search_algorithms;

    Maze_Algorithms current_maze_algo;
    Algorithm_*     current_terrain_algo;
    Search_*        current_search_algo;

    Node* start_node;
    Node* end_node;

    uint32_t board_width;
    uint32_t total_rows;
    float    tile_gap;

    sf::RectangleShape horLine, vertLine;
    sf::RectangleShape green_tile, red_tile;

};

#endif // GRAPH_H