#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <unordered_map>
#include <set>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include "Node.hpp"

class Algorithms_ {
public:
    /* Pathfinding ALgorithms */
    double calc_heuristic(sf::Vector2i p1, sf::Vector2i p2);
    void reconstruct_path(std::unordered_map<Node*, Node*> previous_vertex, Node *current, Node* start_node, 
    std::vector<Node*> &path_nodes);
    void a_star(std::vector<Node*> *board, Node* start_node, Node* end_node, uint32_t total_rows,
    std::vector<Node*> &visited_nodes, std::vector<Node*> &path_nodes);
    void dijkstra(std::vector<Node*> *board, Node* start_node, Node* end_node, uint32_t total_rows,
    std::vector<Node*> &visited_nodes, std::vector<Node*> &path_nodes);
    void bfs(std::vector<Node*> *board, Node* start_node, Node* end_node, uint32_t total_rows,
    std::vector<Node*> &visited_nodes, std::vector<Node*> &path_nodes);
    void dfs_recursion(Node *current, Node* end_node, std::unordered_map<Node*, bool> &visited,
    std::unordered_map<Node*, Node*> &previous_node, std::vector<Node*> &visited_nodes, bool &found_end);
    void dfs(std::vector<Node*> *board, Node* start_node, Node* end_node, uint32_t total_rows,
    std::vector<Node*> &visited_nodes, std::vector<Node*> &path_nodes);

    /*Maze Algorithms*/
    void maze_recursion(Node* current, std::vector<Node*> *board);
    void generate_maze(std::vector<Node*> *board);
    void random_terrain(std::vector<Node*> *board, Node* start_node, Node* end_node, uint32_t total_rows);
};

#endif // ALGORITHMS_H