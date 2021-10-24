#ifndef APP_H
#define APP_H
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "Texture.hpp"
#include "Graph.hpp"

class App {
private:
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    sf::Clock *clock_timer;
    sf::Mouse mousePos;
    std::vector<Node*> visited_nodes;
    std::vector<Node*> path_nodes;
    std::vector<Node*> maze_path[45];
    std::vector<Node*> maze_path2[45];
    Texture_ textures;
    Graph graph;
    uint32_t visited_count, path_count, maze_count;
    
    float dt;
    float total_time;
    bool visualize_visiting;
    bool visualize_path;
    bool finished_visualizing;
    bool visualize_maze;
    bool mouse_down;

    void render();
    void updateSFMLEvents();
    void update();
    bool app_in_focus(sf::RenderWindow *app);

public:
    void run();

    App();
    ~App();
};

#endif