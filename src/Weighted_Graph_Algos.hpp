#ifndef WEIGHTED_GRAPH_ALGOS_H
#define WEIGHTED_GRAPH_ALGOS_H
#include "Base_Algo.hpp"

template<typename T>
class Weighted_Graph_Algos : public Base_Algo<T>{
public:
    double calc_heuristic(T src, T end, std::map<T, std::pair<sf::Vector2f, bool>> &tileCoords_){
        sf::Vector2f srcLoc(tileCoords_[src].first);
        sf::Vector2f endLoc(tileCoords_[end].first);
        return std::abs(srcLoc.x - endLoc.x) + std::abs(srcLoc.y - endLoc.y);
    }

    void A_star_search(T start, T end, std::map<T, std::list<std::pair<T, uint32_t>>> &adjList,
    std::map<T, std::pair<sf::Vector2f, bool>> &tileCoords_, float &objectSize_, 
    std::vector<sf::RectangleShape> &visited_nodes, bool &stopVisiting, 
    std::vector<sf::RectangleShape> &objectTiles){
        std::set<std::pair<double, T>> priority_queue;
        std::map<T, uint32_t> dist;
        std::map<T, T> parent_;
        std::vector<T> path_;

        for (auto n : adjList)
            dist[n.first] = INT_MAX;

        dist[start] = 0;
        priority_queue.insert(std::make_pair(dist[start], start));

        while (!priority_queue.empty()){
            std::pair<uint32_t, T> current_visited = *(priority_queue.begin());
            T node = current_visited.second;
            Base_Algo<T>::visitNodesUI(node, end, visited_nodes, stopVisiting, tileCoords_, objectSize_);
            
            if (node == end)
                break;
            
            priority_queue.erase(priority_queue.begin());
            for (auto neighbor : adjList[node]){
                double g_cost = dist[node] + neighbor.second;
                if (g_cost < dist[neighbor.first] || dist.find(neighbor.first) == dist.end()){
                    dist[neighbor.first] = g_cost;
                    double f_cost = dist[neighbor.first] + calc_heuristic(neighbor.first,end, tileCoords_);
                    priority_queue.insert(std::make_pair(f_cost, neighbor.first));
                    parent_[neighbor.first] = node;
                }
            }
        }
        path_ = Base_Algo<T>::reconstructPath(start, end, parent_);
        Base_Algo<T>::setPathTiles(path_, objectTiles, tileCoords_, objectSize_);
        
    }

    void dijkstra_algorithm(T start, T end, std::map<T, std::list<std::pair<T, uint32_t>>> &adjList,
    std::map<T, std::pair<sf::Vector2f, bool>> &tileCoords_, float &objectSize_, 
    std::vector<sf::RectangleShape> &visited_nodes, bool &stopVisiting, 
    std::vector<sf::RectangleShape> &objectTiles){
        std::set<std::pair<uint32_t, T>> priority_queue;
        std::unordered_map<T, uint32_t> dist;
        std::map<T, T> parent_;
        std::vector<T> path_;

        for (auto n : adjList)
            dist[n.first] = INT_MAX;

        dist[start] = 0;
        priority_queue.insert(std::make_pair(dist[start], start));

        while (!priority_queue.empty()){
            std::pair<uint32_t, T> current_visited = *(priority_queue.begin());
            T current_node = current_visited.second;
            Base_Algo<T>::visitNodesUI(current_node, end, visited_nodes, stopVisiting, tileCoords_, objectSize_);
            uint32_t nodeDist = current_visited.first;
            priority_queue.erase(priority_queue.begin());

            for (auto neighbor : adjList[current_node]){
                if (nodeDist + neighbor.second < dist[neighbor.first]){
                    T dest = neighbor.first;
                    auto findNode = priority_queue.find(std::make_pair(dist[dest], dest));
                    if (findNode != priority_queue.end())
                        priority_queue.erase(findNode);
                    dist[dest] = nodeDist + neighbor.second;
                    priority_queue.insert(std::make_pair(dist[dest], dest));
                    parent_[dest] = current_node;
                }
            }
        }

        path_ = Base_Algo<T>::reconstructPath(start, end, parent_);
        Base_Algo<T>::setPathTiles(path_, objectTiles, tileCoords_, objectSize_);
        
    }

};

#endif // WEIGHTED_GRAPH_ALGOS_H