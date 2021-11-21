#include "Astar.hpp"

Astar_::Astar_(std::vector<Node*>* tiles_, uint32_t total_rows_, Node* start, Node* end)
    : Search_(tiles_, total_rows_, start, end){}

Astar_::~Astar_(){}

double Astar_::calc_heuristic(sf::Vector2i p1, sf::Vector2i p2){
    return (std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y));
}

void Astar_::run(Node* start, Node* end){
    start_node = start;
    end_node = end;
    
    updateTileNeighbors();
    uint32_t precedence = 0;
    priority_queue.insert(std::make_pair(std::make_pair(0, precedence), start_node));
    for (size_t i = 0; i < total_rows; ++i){
        for (size_t k = 0; k < total_rows; ++k){
            g_score[tiles[i][k]] = INT_MAX;
        }
    }
    g_score[start_node] = 0;

    for (size_t i = 0; i < total_rows; ++i){
        for (size_t k = 0; k < total_rows; ++k){
            f_score[tiles[i][k]] = INT_MAX;
        }
    }
    f_score[start_node] = calc_heuristic(start_node->get_coord(), end_node->get_coord());

    std::vector<Node*> priority_queue_tracker = {start_node};

    while (!priority_queue.empty()){
        auto current_queue = *(priority_queue.begin());
        Node *current = current_queue.second;
        
        visited_nodes.push_back(current);

        auto it1 = std::find(priority_queue_tracker.begin(), priority_queue_tracker.end(), current);
        priority_queue.erase(priority_queue.begin());
        if (it1 != priority_queue_tracker.end())
            priority_queue_tracker.erase(it1);

        if (current == end_node){
            reconstruct_path(current);
            return;
        }

        for (auto neighbor : current->neighbors){
            uint32_t temp_g_score = g_score[current] + 1;

            if (temp_g_score < g_score[neighbor]){
                previous_node[neighbor] = current;
                g_score[neighbor] = temp_g_score;
                f_score[neighbor] = temp_g_score + calc_heuristic(neighbor->get_coord(), end_node->get_coord());
                
                if (std::find(priority_queue_tracker.begin(), priority_queue_tracker.end(), neighbor) == priority_queue_tracker.end()){
                    precedence += 1;
                    priority_queue.insert(std::make_pair(std::make_pair(f_score[neighbor], precedence), neighbor));
                    priority_queue_tracker.push_back(neighbor);
                    
                }
            }
        }
    }
    visited_nodes.clear();

}

void Astar_::reset_attributes(){
    previous_node.clear();
    priority_queue.clear();
    g_score.clear();
    f_score.clear();
    path_nodes.clear();
    visited_nodes.clear();
}