#ifndef ASTAR_H
#define ASTAR_H
#include "Search.hpp"

class Astar_ : public Search_{
public:

    Astar_(std::vector<Node*>* tiles_, uint32_t total_rows_, Node* start, Node* end);

    virtual ~Astar_() override;

    virtual void run(Node* start = nullptr, Node* end = nullptr) override;

    virtual void reset_attributes() override;

private:

    std::set<std::pair<std::pair<double, uint32_t>, Node*>> priority_queue;

    std::unordered_map<Node*, uint32_t> g_score;
    std::unordered_map<Node*, double> f_score;

    double calc_heuristic(sf::Vector2i p1, sf::Vector2i p2);
};


#endif // STAR_H