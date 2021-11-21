#ifndef RECURSIVE_MAZE_H
#define RECURSIVE_MAZE_H
#include <unordered_map>
#include "Algorithm.hpp"

class RecursiveMaze : public Algorithm_{
public:

    RecursiveMaze(std::vector<Node*>* tiles_, uint32_t total_rows_);

    virtual ~RecursiveMaze() override;

    virtual void run(Node* start = nullptr, Node* end = nullptr) override;
    
private:

    void maze_recursion(Node* current);

};

#endif // RECURSIVE_MAZE_H