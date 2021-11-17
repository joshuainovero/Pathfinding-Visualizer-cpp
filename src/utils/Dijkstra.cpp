#include "Dijkstra.hpp"

Dijkstra_::Dijkstra_(std::vector<Node*>* tiles_, uint32_t total_rows_, Node* start, Node* end)
    : Search_(tiles_, total_rows_, start, end){}

Dijkstra_::~Dijkstra_() {}

void Dijkstra_::run(Node* start, Node* end){
    start_node = start;
    end_node = end;

    updateTileNeighbors();
    
    bool found_end = false;
    for (size_t i = 0; i < total_rows; ++i){
        for (size_t k = 0; k < total_rows; ++k){
            g_score[tiles[i][k]] = INT_MAX;
        }
    }

    g_score[start_node] = 0;
    priority_queue.insert(std::make_pair(g_score[start_node], start_node));

    while(!priority_queue.empty()){
        Node* current_node = (priority_queue.begin())->second;
        if (current_node == end_node)
            found_end = true;

        if (!found_end)
            visited_nodes.push_back(current_node);

        uint32_t current_dist = (priority_queue.begin())->first;
        priority_queue.erase(priority_queue.begin());

        for (auto neighbor : current_node->neighbors){
            if (current_dist + 1 < g_score[neighbor]){
                auto find_node = priority_queue.find(std::make_pair(g_score[neighbor], neighbor));
                if (find_node != priority_queue.end())
                    priority_queue.erase(find_node);

                g_score[neighbor] = current_dist + 1;
                priority_queue.insert(std::make_pair(g_score[neighbor], neighbor));
                previous_node[neighbor] = current_node;
            }
        }
    }
    if (!found_end)
        visited_nodes.clear();
    else
        reconstruct_path(end_node);
}

void Dijkstra_::reset_attributes(){
    previous_node.clear();
    priority_queue.clear();
    g_score.clear();
    path_nodes.clear();
    visited_nodes.clear(); 
}