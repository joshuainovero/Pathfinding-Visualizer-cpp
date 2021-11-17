#include "Search.hpp"

Search_::Search_(std::vector<Node*>* tiles_, uint32_t total_rows_, Node* start, Node* end)
    : Algorithm_(tiles_, total_rows_){

        start_node = start;

        end_node = end;

    }

Search_::~Search_() {}

void Search_::reconstruct_path(Node* current){
    while (current != start_node){
        path_nodes.push_back(current);
        current = previous_node[current];
    }
    std::reverse(path_nodes.begin(), path_nodes.end());
    path_nodes.pop_back();
}