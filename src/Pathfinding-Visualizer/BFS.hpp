#ifndef BFS_H
#define BFS_H
#include <queue>
#include "Search.hpp"

class BFS_ : public Search_{
public:

    BFS_(std::vector<Node*>* tiles_, uint32_t total_rows_, Node* start, Node* end);

    virtual ~BFS_() override;

    virtual void run(Node* start = nullptr, Node* end = nullptr) override;

    virtual void reset_attributes() override;

private:

    std::unordered_map<Node*, bool> visited;

    std::queue<Node*> _queue;     

};


#endif // BFS_H