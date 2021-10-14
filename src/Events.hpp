#ifndef EVENTS_H
#define EVENTS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Textures.hpp"
#include "Graph.hpp"

enum Algorithms_ {Astar, Dijkstra, BFS, DFS};
class Events_{
public:
    Texture_ texture_;
    Graph<int> graph;
    uint32_t visualizeRanges[4];
    uint32_t reloadRanges[4];
    uint32_t clearRanges[4];
    uint32_t AstarRanges[4];
    uint32_t dijkstraRanges[4];
    uint32_t bfsRanges[4];
    uint32_t dfsRanges[4];
    sf::Mouse mousePos;
    Algorithms_ algos;
    std::vector<sf::Vector2f> choicePositions;
    sf::Clock dtClock;
    size_t objectCount;
    size_t visitedCount;
    float dt, totalTime, totalTime2;

    bool visualizeInRange();
    bool reloadInRange();
    bool clearInRange();
    bool AstarInRange();
    bool dijkstraInRange();
    bool bfsInRange();
    bool dfsInRange();

    bool visualizeInProgress;
    bool visualizeFinished;
    bool displayPath;

    //Mouse Down
    bool md_visualize;
    bool md_checkBox;
    bool md_tile;
    bool md_reload;
    bool md_clear;

    //Hand triggers
    bool visualize_handTrigger;
    bool check_handTrigger;
    bool reload_handTrigger;
    bool clear_handTrigger;

    bool startInDrag, targetInDrag;

    Events_(sf::Vector2f &&windowSize);
    void clickEvents(sf::RenderWindow *window);
    void drawColoredTiles(sf::RenderWindow *window);
};

#endif