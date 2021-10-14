#ifndef UNWEIGHTED_GRAPH_ALGOS_H
#define UNWEIGHTED_GRAPH_ALGOS_H
#include "Base_Algo.hpp"

template<typename T>
class Unweighted_Graph_Algos : public Base_Algo<T> {
public:
    void bfs_algorithm(T start, T end, std::map<T, std::list<std::pair<T, uint32_t>>> &adjList,
    std::map<T, std::pair<sf::Vector2f, bool>> &tileCoords_, float &objectSize_, 
    std::vector<sf::RectangleShape> &visited_nodes, bool &stopVisiting, 
    std::vector<sf::RectangleShape> &objectTiles){
        std::map<T, bool> visited;
        std::vector<T> path_;
        std::queue<T> q;
        q.push(start);
        visited[start] = true;

        std::map<T, T> parent_;

        while (!q.empty()){
            T node = q.front();
            Base_Algo<T>::visitNodesUI(node, end, visited_nodes, stopVisiting, tileCoords_, objectSize_);
            q.pop();
            auto neighbors = adjList[node];
            for (auto neighbor : neighbors){
                if (!visited[neighbor.first]){
                    q.push(neighbor.first);
                    visited[neighbor.first] = true;
                    parent_[neighbor.first] = node;
                }
            }
        }

        path_ = Base_Algo<T>::reconstructPath(start, end, parent_);
        Base_Algo<T>::setPathTiles(path_, objectTiles, tileCoords_, objectSize_);

    }

    void dfs_helper(T src, T end, std::map<T, std::list<std::pair<T, uint32_t>>> &adjList,
    std::map<T, std::pair<sf::Vector2f, bool>> &tileCoords_, float &objectSize_, 
    std::vector<sf::RectangleShape> &visited_nodes, bool &stopVisiting, 
    std::vector<sf::RectangleShape> &objectTiles, std::map<T, bool> &visited,
    std::map<T, T> &parent_){
        visited[src] = true;

        for (auto nbr : adjList[src]){
            if (!visited[nbr.first]){
                Base_Algo<T>::visitNodesUI(nbr.first, end, visited_nodes, stopVisiting, tileCoords_, objectSize_);
                parent_[nbr.first] = src;
                dfs_helper(nbr.first, end, adjList, tileCoords_, objectSize_, visited_nodes, stopVisiting, objectTiles, visited, parent_);
            }

        }
    }

    void dfs_algorithm(T start, T end, std::map<T, std::list<std::pair<T, uint32_t>>> &adjList,
    std::map<T, std::pair<sf::Vector2f, bool>> &tileCoords_, float &objectSize_, 
    std::vector<sf::RectangleShape> &visited_nodes, bool &stopVisiting, 
    std::vector<sf::RectangleShape> &objectTiles){
        std::map<T, T> parent;
        std::map<T, bool> visited;
        std::vector<T> path_;
        dfs_helper(start, end, adjList, tileCoords_, objectSize_, visited_nodes, stopVisiting, objectTiles, visited, parent);

        path_ = Base_Algo<T>::reconstructPath(start, end, parent);
        Base_Algo<T>::setPathTiles(path_, objectTiles, tileCoords_, objectSize_);
    }

};

#endif