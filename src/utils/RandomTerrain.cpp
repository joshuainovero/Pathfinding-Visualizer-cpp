#include "RandomTerrain.hpp"

RandomTerrain::RandomTerrain(std::vector<Node*>* tiles_, uint32_t total_rows_)
    : Algorithm_(tiles_, total_rows_){}

RandomTerrain::~RandomTerrain() {}

void RandomTerrain::run(Node* start, Node* end){
    uint32_t counter = 0;
    const float ratio_overall = 0.7530864198f;
    uint32_t total_walls = std::floor((float)std::pow(total_rows, 2) - ((float)std::pow(total_rows, 2) * ratio_overall));
    while (counter != total_walls){
        sf::Vector2i random_pos (rand() % total_rows, rand() % total_rows);     
        if (tiles[random_pos.x][random_pos.y] != start && tiles[random_pos.x][random_pos.y] != end){
            tiles[random_pos.x][random_pos.y]->set_obstruction();
            counter++;
        }
    }
}
