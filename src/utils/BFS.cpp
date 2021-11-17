#include "BFS.hpp"

BFS_::BFS_(std::vector<Node*>* tiles_, uint32_t total_rows_, Node* start, Node* end)
    : Search_(tiles_, total_rows_, start, end){}

BFS_::~BFS_() {}

void BFS_::run(Node* start, Node* end){
    start_node = start;
    end_node = end;

    updateTileNeighbors();

    _queue.push(start_node);
    visited[start_node] = true;

    bool found_end = false;
    while (!_queue.empty()){
        Node* current_node = _queue.front();
        if (current_node == end_node)
            found_end = true;

        if (!found_end)
            visited_nodes.push_back(current_node);

        _queue.pop();
        for (auto neighbor : current_node->neighbors){
            if (!visited[neighbor]){
                _queue.push(neighbor);
                visited[neighbor] = true;
                previous_node[neighbor] = current_node;
            }
        }
    }
    if (!found_end)
        visited_nodes.clear();
    else
        reconstruct_path(end_node);
}

void BFS_::reset_attributes(){
    previous_node.clear();
    std::queue<Node*> empty;
    std::swap(_queue, empty);
    visited.clear();
    path_nodes.clear();
    visited_nodes.clear();
}