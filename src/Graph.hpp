#ifndef GRAPH_H
#define GRAPH_H
#include "Weighted_Graph_Algos.hpp"
#include "Unweighted_Graph_Algos.hpp"

template<typename T>
class Graph {
friend class App;
friend class Events_;
private:
    std::map<T, std::list<std::pair<T, uint32_t>>> adjList;
    std::map<T, std::list<std::pair<T, uint32_t>>> adjListConstant;
    std::map<T, std::pair<sf::Vector2f, bool>> tileCoords;
    std::map<T, std::list<std::pair<T, uint32_t>>> disconnectedNodes;
    std::map<T, sf::RectangleShape> obstructions;
    std::vector<sf::RectangleShape> objectTiles;
    std::vector<sf::RectangleShape> visitedNodes;
    std::pair<uint32_t, uint32_t> point_index;
    sf::Vector2f start_coord, end_coord;
    Weighted_Graph_Algos<T> WGA;
    Unweighted_Graph_Algos<T> UGA;
    uint32_t obsCount;
    bool stopVisiting;
    float objectSize;

public:
    void constructGraph(){
        int curr_row = 0;
        int prev_row = 0;
        int curr_col = 0;

        for (int i = 0; i < 400; ++i){
            if (i % 20 != 0){
                adjListConstant[i].push_back(std::make_pair(i - 1, 1));
                adjListConstant[i - 1].push_back(std::make_pair(i, 1));

                if (curr_row != 0){
                    adjListConstant[i].push_back(std::make_pair(prev_row + curr_col, 1));
                    adjListConstant[prev_row + curr_col].push_back(std::make_pair(i, 1));
                }
            }
            else {
                curr_col = 0;
                prev_row = curr_row;
                curr_row = i;
                if (curr_row != 0){
                    adjListConstant[i].push_back(std::make_pair(prev_row + curr_col, 1));
                    adjListConstant[prev_row + curr_col].push_back(std::make_pair(i, 1));
                }
            }
            curr_col++;
        }
    }

    void setTileCoords(){
        sf::Vector2f curr_position((542.0f/1080.0f) * sf::VideoMode::getDesktopMode().height, (161.0f/1080.0f) * sf::VideoMode::getDesktopMode().height);
        for (int i = 0; i < 400; ++i){
            if (i % 20 == 0 && i != 0){
                curr_position.x = (542.0f/1080.0f) * sf::VideoMode::getDesktopMode().height;
                curr_position.y = curr_position.y + objectSize;
                tileCoords[i].first = sf::Vector2f(curr_position.x, curr_position.y);
            }
            else {
                tileCoords[i].first = sf::Vector2f(curr_position.x, curr_position.y);
            }
            tileCoords[i].second = false;
            curr_position.x = curr_position.x + objectSize;
        }
    }

    void disconnectNode(T node){
        for (auto nbr : adjList[node]){
            disconnectedNodes[node].push_back(nbr);
        }
        for (auto neighbor : adjList[node]){
            adjList[neighbor.first].remove(std::make_pair(node, 1));
        }
        adjList[node].clear();

        tileCoords[node].second = true;
        sf::RectangleShape obs;
        obs.setSize(sf::Vector2f(objectSize, objectSize));
        obs.setPosition(sf::Vector2f(tileCoords[node].first.x, tileCoords[node].first.y));
        obs.setFillColor(sf::Color(12, 53, 71));
        obstructions[node] = obs;
        obsCount++;
    }

    void reconnectNode(T node){
        auto it = obstructions.find(node);
        if (it != obstructions.end())
            obstructions.erase(it);

        for (auto neighbor : disconnectedNodes[node]){
            adjList[neighbor.first].push_back(std::make_pair(node, 1));
            adjList[node].push_back(std::make_pair(neighbor.first,1));
        }

        tileCoords[node].second = false;
        auto it2 = disconnectedNodes.find(node);
        if (it2 != disconnectedNodes.end())
            disconnectedNodes.erase(it2);
        obsCount--;
    }

    Graph(){
        objectSize = (41.55/1080.0f) * sf::VideoMode::getDesktopMode().height;
        constructGraph();
        setTileCoords();
        adjList = adjListConstant;
        stopVisiting = false;
        point_index = std::make_pair(0, 399);
        start_coord.x = tileCoords[point_index.first].first.x;
        start_coord.y = tileCoords[point_index.first].first.y;
        end_coord.x = tileCoords[point_index.second].first.x;
        end_coord.y = tileCoords[point_index.second].first.y;
        obsCount = 0;
    }
};

#endif // GRAPH_H