#include "DFS.hpp"

DFS_::DFS_(std::vector<Node*>* tiles_, uint32_t total_rows_, Node* start, Node* end)
    : Search_(tiles_, total_rows_, start, end){}

DFS_::~DFS_() {}

void DFS_::run(Node* start, Node* end){
    start_node = start;
    end_node = end;
    updateTileNeighbors();

    std::unordered_map<Node*, bool> visited;
    bool found_end = false;
    DFS_recursion(visited, start_node, found_end);
    if (!found_end)
        visited_nodes.clear();
    else
        reconstruct_path(end_node);
}

void DFS_::DFS_recursion(std::unordered_map<Node*, bool>& visited, Node* current, bool& found_end){
    visited[current] = true;
    if (current == end_node)
        found_end = true;
    if (!found_end)
        visited_nodes.push_back(current);
    for (auto neighbor : current->neighbors){
        if (!visited[neighbor]){
            previous_node[neighbor] = current;
            DFS_recursion(visited, neighbor, found_end);
        }
    }
}

void DFS_::reset_attributes(){
    previous_node.clear();
    path_nodes.clear();
    visited_nodes.clear();
}