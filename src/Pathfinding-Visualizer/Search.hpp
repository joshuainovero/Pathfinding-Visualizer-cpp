#ifndef SEARCH_H
#define SEARCH_H
#include "Algorithm.hpp"
#include <unordered_map>
#include <vector>
#include <utility>
#include <set>

class Search_ : public Algorithm_{
public:

    Search_(std::vector<Node*> *tiles_, uint32_t total_rows_, Node* start, Node* end);

    virtual ~Search_() override;

    virtual void reset_attributes() = 0;

    virtual void run(Node* start = nullptr, Node* end = nullptr) = 0;

protected:

    Node* start_node;
    Node* end_node;

    std::unordered_map<Node*, Node*> previous_node;

    void reconstruct_path(Node* current);

};

#endif // SEARCH_H