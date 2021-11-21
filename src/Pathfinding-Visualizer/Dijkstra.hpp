#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "Search.hpp"

class Dijkstra_ : public Search_{
public:

    Dijkstra_(std::vector<Node*>* tiles_, uint32_t total_rows_, Node* start, Node* end);

    virtual ~Dijkstra_() override;

    virtual void run(Node* start = nullptr, Node* end = nullptr) override;

    virtual void reset_attributes() override;

private:
    std::set<std::pair<uint32_t, Node*>> priority_queue;

    std::unordered_map<Node*, uint32_t>  g_score;        

};

#endif //DIJKSTRA_H