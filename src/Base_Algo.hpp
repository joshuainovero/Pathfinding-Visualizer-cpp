#ifndef BASE_ALGO_H
#define BASE_ALGO_H
#include <SFML/Graphics.hpp>
#include <list>
#include <utility>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <cmath>

template<typename T>
class Base_Algo{
protected:
    std::vector<T> reconstructPath(T start_, T end_, std::map<T, T> &_parent){
        std::vector<T> tempPath;
        for (T at = end_; at != start_; at = _parent[at])
            tempPath.push_back(at);
        tempPath.push_back(start_);
        std::reverse(tempPath.begin(), tempPath.end());
        return tempPath;
    }

    void visitNodesUI(T node, T end, std::vector<sf::RectangleShape> &visited_nodes, bool &stopVisiting_,
    std::map<T, std::pair<sf::Vector2f, bool>> &tileCoords_, const float &objectSize_){
        if (!stopVisiting_){
            sf::RectangleShape visitedObject;
            visitedObject.setSize(sf::Vector2f(objectSize_, objectSize_));
            visitedObject.setPosition(sf::Vector2f(tileCoords_[node].first.x, tileCoords_[node].first.y));
            visitedObject.setFillColor(sf::Color(68,204,228));
            visited_nodes.push_back(visitedObject);
            if (node == end)
                stopVisiting_ = true;
        }
    }

    void setPathTiles(const std::vector<T> &_path, std::vector<sf::RectangleShape> &objectTiles_, 
    std::map<T, std::pair<sf::Vector2f, bool>> &tileCoords_, const float &objectSize_){
        for (size_t i = 0; i < _path.size(); ++i){
            sf::RectangleShape pathObject;
            pathObject.setSize(sf::Vector2f(objectSize_, objectSize_));
            pathObject.setPosition(sf::Vector2f(tileCoords_[_path[i]].first.x, tileCoords_[_path[i]].first.y));
            pathObject.setFillColor(sf::Color(255, 254, 106));
            objectTiles_.push_back(pathObject);
        }
    }


};

#endif