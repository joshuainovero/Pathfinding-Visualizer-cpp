#ifndef RANDOM_TERRAIN_H
#define RANDOM_TERRAIN_H

#include "Algorithm.hpp"

class RandomTerrain : public Algorithm_{
public:

    RandomTerrain(std::vector<Node*>* tiles_, uint32_t total_rows_);

    virtual ~RandomTerrain() override;

    virtual void run(Node* start = nullptr, Node* end = nullptr) override;

private:

    static constexpr float ratio_overall = 0.7530864198f;

};

#endif // RANDOM_TERRAIN_H