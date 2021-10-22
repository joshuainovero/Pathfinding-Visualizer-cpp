#include "Algorithms.hpp"
#include <iostream>

double Algorithms_::calc_heuristic(sf::Vector2i p1, sf::Vector2i p2){
    return (std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y));
}

void Algorithms_::reconstruct_path(std::unordered_map<Node*, Node*> previous_vertex, Node *current, Node* start_node,
std::vector<Node*> &path_nodes){
    while (current != start_node){
        path_nodes.push_back(current);
        current = previous_vertex[current];
    }
    std::reverse(path_nodes.begin(), path_nodes.end());
    path_nodes.pop_back();

}

void Algorithms_::a_star(std::vector<Node*> board[45], Node* start_node, Node* end_node, uint32_t total_rows,
    std::vector<Node*> &visited_nodes, std::vector<Node*> &path_nodes){
    uint32_t precedence = 0;
    std::set<std::pair<std::pair<double, uint32_t>, Node*>> priority_queue;
    priority_queue.insert(std::make_pair(std::make_pair(0, precedence), start_node));
    std::unordered_map<Node*, Node*> previous_vertex;
    std::unordered_map<Node*, uint32_t> g_score;
    std::unordered_map<Node*, double> f_score;
    for (size_t i = 0; i < total_rows; ++i){
        for (size_t k = 0; k < total_rows; ++k){
            g_score[board[i][k]] = INT_MAX;
        }
    }
    g_score[start_node] = 0;

    for (size_t i = 0; i < total_rows; ++i){
        for (size_t k = 0; k < total_rows; ++k){
            f_score[board[i][k]] = INT_MAX;
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
            reconstruct_path(previous_vertex, current, start_node, path_nodes);
            return;
        }

        for (auto neighbor : current->neighbors){
            uint32_t temp_g_score = g_score[current] + 1;

            if (temp_g_score < g_score[neighbor]){
                previous_vertex[neighbor] = current;
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

void Algorithms_::dijkstra(std::vector<Node*> board[45], Node* start_node, Node* end_node, uint32_t total_rows,
std::vector<Node*> &visited_nodes, std::vector<Node*> &path_nodes){
    std::set<std::pair<uint32_t, Node*>> priority_queue;
    std::unordered_map<Node*, uint32_t> g_score;
    std::unordered_map<Node*, Node*> previous_node;
    bool found_end = false;
    for (size_t i = 0; i < total_rows; ++i){
        for (size_t k = 0; k < total_rows; ++k){
            g_score[board[i][k]] = INT_MAX;
        }
    }

    g_score[start_node] = 0;
    priority_queue.insert(std::make_pair(g_score[start_node], start_node));

    while(!priority_queue.empty()){
        Node* current_node = (priority_queue.begin())->second;
        if (current_node == end_node)
            found_end = true;

        if (!found_end)
            visited_nodes.push_back(current_node);

        uint32_t current_dist = (priority_queue.begin())->first;
        priority_queue.erase(priority_queue.begin());

        for (auto neighbor : current_node->neighbors){
            if (current_dist + 1 < g_score[neighbor]){
                auto find_node = priority_queue.find(std::make_pair(g_score[neighbor], neighbor));
                if (find_node != priority_queue.end())
                    priority_queue.erase(find_node);

                g_score[neighbor] = current_dist + 1;
                priority_queue.insert(std::make_pair(g_score[neighbor], neighbor));
                previous_node[neighbor] = current_node;
            }
        }
    }
    if (!found_end)
        visited_nodes.clear();
    else
        reconstruct_path(previous_node, end_node, start_node, path_nodes);
}

void Algorithms_::bfs(std::vector<Node*> board[45], Node* start_node, Node* end_node, uint32_t total_rows,
std::vector<Node*> &visited_nodes, std::vector<Node*> &path_nodes){
    std::unordered_map<Node*, bool> visited;
    std::queue<Node*> q;
    q.push(start_node);
    visited[start_node] = true;
    std::unordered_map<Node*, Node*> previous_node;
    bool found_end = false;

    while (!q.empty()){
        Node* current_node = q.front();
        if (current_node == end_node)
            found_end = true;

        if (!found_end)
            visited_nodes.push_back(current_node);

        q.pop();
        for (auto neighbor : current_node->neighbors){
            if (!visited[neighbor]){
                q.push(neighbor);
                visited[neighbor] = true;
                previous_node[neighbor] = current_node;
            }
        }
    }
    if (!found_end)
        visited_nodes.clear();
    else
        reconstruct_path(previous_node, end_node, start_node, path_nodes);
}

void Algorithms_::dfs_recursion(Node *current, Node* end_node, std::unordered_map<Node*, bool> &visited,
std::unordered_map<Node*, Node*> &previous_node, std::vector<Node*> &visited_nodes, bool &found_end){
    visited[current] = true;
    if (current == end_node)
        found_end = true;
    if (!found_end)
        visited_nodes.push_back(current);
    for (auto neighbor : current->neighbors){
        if (!visited[neighbor]){
            previous_node[neighbor] = current;
            dfs_recursion(neighbor, end_node, visited, previous_node, visited_nodes, found_end);
        }
    }
}

void Algorithms_::dfs(std::vector<Node*> board[45], Node* start_node, Node* end_node, uint32_t total_rows,
std::vector<Node*> &visited_nodes, std::vector<Node*> &path_nodes){
    std::unordered_map<Node*, Node*> previous_node;
    std::unordered_map<Node*, bool> visited;
    bool found_end = false;
    dfs_recursion(start_node, end_node, visited, previous_node, visited_nodes, found_end);
    
    if (!found_end)
        visited_nodes.clear();
    else
        reconstruct_path(previous_node, end_node, start_node, path_nodes);
}

void Algorithms_::maze_recursion(Node* current, std::vector<Node*> board[45]){
    current->visited_maze = true;
    std::vector<Node*> randomized_neighbors = current->neighbors;
    std::random_shuffle(randomized_neighbors.begin(), randomized_neighbors.end());
    for (auto neighbor : randomized_neighbors){
        Node* next_neighbor = nullptr;

        if (neighbor->row > current->row){
            if (!(board[neighbor->row + 1][neighbor->col])->visited_maze){
                next_neighbor = board[neighbor->row + 1][neighbor->col];
            }
        }
        else if (neighbor->row < current->row){
            if (!neighbor->row == 0){
                if (!(board[neighbor->row - 1][neighbor->col])->visited_maze){
                    next_neighbor = board[neighbor->row - 1][neighbor->col];
                }
            }          
        }
        else if (neighbor->col > current->col){
            if (!(board[neighbor->row][neighbor->col + 1])->visited_maze){
                next_neighbor = board[neighbor->row][neighbor->col + 1];
            }            
        }
        else if (neighbor->col < current->col){
            if (!(board[neighbor->row][neighbor->col - 1])->visited_maze){
                next_neighbor = board[neighbor->row][neighbor->col - 1];
            }             
        }
        if (next_neighbor != nullptr){
            neighbor->visited_maze = true;
            maze_recursion(next_neighbor, board);
        }

    }

    
}

void Algorithms_::generate_maze(std::vector<Node*> board[45]){
    std::srand(time(0));
    std::unordered_map<Node*, bool> visited;
    Node* current = board[0][0];
    maze_recursion(current, board);
}

void Algorithms_::random_terrain(std::vector<Node*> board[45], Node* start_node, Node* end_node, uint32_t total_rows){
    uint32_t counter = 0;
    while (counter != 500){
        sf::Vector2i random_pos (rand() % total_rows, rand() % total_rows);     
        if (board[random_pos.x][random_pos.y] != start_node && board[random_pos.x][random_pos.y] != end_node){
            board[random_pos.x][random_pos.y]->set_obstruction();
            counter++;
        }
    }
}