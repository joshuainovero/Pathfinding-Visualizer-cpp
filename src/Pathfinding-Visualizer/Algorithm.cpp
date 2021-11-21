#include "Algorithm.hpp"

Algorithm_::Algorithm_(std::vector<Node*>* tiles_, uint32_t total_rows_) : 
    tiles (tiles_), total_rows(total_rows_){}

Algorithm_::~Algorithm_(){}

void Algorithm_::updateTileNeighbors(){
    for (size_t i = 0; i < total_rows; ++i){
        for (auto node : tiles[i])
            node->update_neighbors(tiles);
    }
}

std::vector<Node*> Algorithm_::getPathNodes() { return path_nodes; }

std::vector<Node*> Algorithm_::getVisitedNodes() { return visited_nodes; }