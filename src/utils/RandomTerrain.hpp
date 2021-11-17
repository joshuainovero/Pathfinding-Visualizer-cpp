#ifndef RANDOM_TERRAIN_H
#define RANDOM_TERRAIN_H

#include "Algorithm.hpp"

class RandomTerrain : public Algorithm_{
public:

    RandomTerrain(std::vector<Node*>* tiles_, uint32_t total_rows_);

    virtual ~RandomTerrain() override;

    virtual void run(Node* start = nullptr, Node* end = nullptr) override;

};

#endif // RANDOM_TERRAIN_H