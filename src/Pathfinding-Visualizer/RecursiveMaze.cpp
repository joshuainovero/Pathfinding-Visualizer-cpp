#include "RecursiveMaze.hpp"

RecursiveMaze::RecursiveMaze(std::vector<Node*>* tiles_, uint32_t total_rows_)
    : Algorithm_(tiles_, total_rows_){}

RecursiveMaze::~RecursiveMaze() {}

void RecursiveMaze::run(Node* start, Node* end){
    updateTileNeighbors();
    std::unordered_map<Node*, bool> visited;
    Node* current = tiles[0][0];
    maze_recursion(current);
}

void RecursiveMaze::maze_recursion(Node* current){
    current->visited_maze = true;
    std::vector<Node*> randomized_neighbors = current->neighbors;
    std::random_shuffle(randomized_neighbors.begin(), randomized_neighbors.end());
    for (auto neighbor : randomized_neighbors){
        Node* next_neighbor = nullptr;

        if (neighbor->row > current->row){
            if (!(tiles[neighbor->row + 1][neighbor->col])->visited_maze){
                next_neighbor = tiles[neighbor->row + 1][neighbor->col];
            }
        }
        else if (neighbor->row < current->row){
            if (!neighbor->row == 0){
                if (!(tiles[neighbor->row - 1][neighbor->col])->visited_maze){
                    next_neighbor = tiles[neighbor->row - 1][neighbor->col];
                }
            }          
        }
        else if (neighbor->col > current->col){
            if (!(tiles[neighbor->row][neighbor->col + 1])->visited_maze){
                next_neighbor = tiles[neighbor->row][neighbor->col + 1];
            }            
        }
        else if (neighbor->col < current->col){
            if (!(tiles[neighbor->row][neighbor->col - 1])->visited_maze){
                next_neighbor = tiles[neighbor->row][neighbor->col - 1];
            }             
        }
        if (next_neighbor != nullptr){
            neighbor->visited_maze = true;
            maze_recursion(next_neighbor);
        }
    }
}