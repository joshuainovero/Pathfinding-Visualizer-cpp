#include "App.hpp"
#include <iostream>

App::App(uint32_t total_rows) : graph(total_rows, sf::VideoMode::getDesktopMode().height), textures(){
    window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Pathfinding Visualizer", sf::Style::Close | sf::Style::Fullscreen);
    window->setFramerateLimit(120);
    dt = 0.0f;
    total_time = 0.0f;
    visualize_visiting = false;
    visualize_path = false;
    finished_visualizing = false;
    visualize_maze = false;
    app_in_focus = true;
    visited_count = 0;
    path_count = 0;
    maze_count = 0;
    clock_timer = nullptr;

    maze_path = new std::vector<Node*>[total_rows];

    row_sizes[0] = 15;
    row_sizes[1] = 25;
    row_sizes[2] = 35;
    row_sizes[3] = 45;
    mouse_scroll_value = 3;
}


void App::updateSFMLEvents(){
    while (window->pollEvent(sfEvent)){
        switch(sfEvent.type){
            case sf::Event::Closed:
                window->close();
            break;
            case sf::Event::TextEntered:
                if (sfEvent.text.unicode == int('c') || sfEvent.text.unicode == int('C')){
                    if (!visualize_maze && !visualize_path && !visualize_visiting){
                        for (size_t i = 0; i < graph.total_rows; ++i){
                            for (auto node : graph.board[i]){
                                node->visited_maze = false;
                                if (node != graph.start_node && node != graph.end_node){
                                    node->reset();
                                }
                            }
                        }
                    }
                }
                else if (sfEvent.text.unicode == 27)
                    window->close();
            
            break;
            case sf::Event::MouseWheelMoved:
                if(!visualize_maze && !visualize_path && !visualize_visiting){
                    temp_mouse_value = mouse_scroll_value;
                    if (sfEvent.mouseWheel.delta > 0){
                        if (mouse_scroll_value < 3)
                            mouse_scroll_value++;
                    }
                    else {
                        if (mouse_scroll_value > 0)
                            mouse_scroll_value--;
                    }
                    if (mouse_scroll_value != temp_mouse_value){
                        for (size_t i = 0; i < graph.total_rows; ++i){
                            for (Node *node : graph.board[i]) {
                                delete node;
                            }
                            graph.board[i].clear();
                        }
                        delete [] graph.board;
                        graph.construct_graph(row_sizes[mouse_scroll_value], sf::VideoMode::getDesktopMode().height);

                    }
                }
            break;
            
            case sf::Event::LostFocus: app_in_focus = false; break;
            case sf::Event::GainedFocus: app_in_focus = true; break;
            default:break;
        }
    }
}

void App::update(){
    dt = dtClock.restart().asSeconds();
    updateSFMLEvents();
    if (app_in_focus){
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2u rowcol = graph.rowcol_pos_click(mousePos.getPosition(*window));
            if (finished_visualizing){
                if (!mouse_down){
                    for (size_t i = 0; i < graph.total_rows; ++i){
                        for (auto node : graph.board[i]){
                            if (node->color == sf::Color(PATH_COLOR) || node->color == sf::Color(VISITED_COLOR)
                            || node->color == sf::Color(OPEN_COLOR)){
                                node->reset();
                            }
                        }
                    }
                    textures.algorithm_log_text.setString("");
                    finished_visualizing = false;
                    mouse_down = true;
                }
            }
            else if (rowcol.x < graph.total_rows){
                Node* clicked_node = graph.board[rowcol.x][rowcol.y];
                if (!(graph.start_node) && clicked_node != graph.end_node){
                    graph.start_node = clicked_node;
                    graph.start_node->set_start();
                }
                else if (!(graph.end_node) && clicked_node != graph.start_node){
                    graph.end_node = clicked_node;
                    graph.end_node->set_target();
                }
                else if (clicked_node != graph.end_node && clicked_node != graph.start_node){
                    clicked_node->set_obstruction();
                }
            }

            else if (textures.clickable_in_range(textures.visualize_ranges, mousePos)){
                if (graph.start_node != nullptr  && graph.end_node != nullptr){
                    if (!visualize_visiting && !visualize_path){
                        if (!mouse_down){
                            for (size_t i = 0; i < graph.total_rows; ++i){
                                for (auto node : graph.board[i]){
                                    node->update_neighbors(graph.board);
                                }
                            }
                            clock_timer = new sf::Clock();
                            switch (graph.current_algo){
                                case PF_Algorithms::Astar:
                                    
                                    graph.algorithms.a_star(graph.board, graph.start_node, graph.end_node, graph.total_rows, visited_nodes, path_nodes);
                                break;
                                case PF_Algorithms::Dijkstra:
                                    graph.algorithms.dijkstra(graph.board, graph.start_node, graph.end_node, graph.total_rows, visited_nodes, path_nodes);
                                break;
                                case PF_Algorithms::BFS:
                                    graph.algorithms.bfs(graph.board, graph.start_node, graph.end_node, graph.total_rows, visited_nodes, path_nodes);     
                                break;
                                case PF_Algorithms::DFS:
                                    graph.algorithms.dfs(graph.board, graph.start_node, graph.end_node, graph.total_rows, visited_nodes, path_nodes);      
                                break;
                                default:break;
                            }
                            std::string log_msg;
                            if (!path_nodes.empty()){
                                log_msg = "Time taken: " + std::to_string(clock_timer->getElapsedTime().asMilliseconds()) +" ms\nVisited nodes: " + std::to_string(visited_nodes.size() - 1) + "\nPath length: " + std::to_string(path_nodes.size() + 1);
                                textures.algorithm_log_text.setFillColor(sf::Color::Black);
                            }
                            else {
                                log_msg = "No path!";
                                textures.algorithm_log_text.setFillColor(sf::Color::Red);
                                finished_visualizing = true;
                            }
                            textures.algorithm_log_text.setString(log_msg);
                            delete clock_timer;
                            clock_timer = nullptr;
                            if (!visited_nodes.empty())
                                visualize_visiting = true;
                            mouse_down = true;
                        }
                    }
                }
            }
            else if (textures.clickable_in_range(textures.generate_ranges, mousePos)){
                if (graph.start_node != nullptr  && graph.end_node != nullptr){
                    if (!visualize_visiting && !visualize_path && !visualize_maze){
                        if (!mouse_down){
                            for (size_t i = 0; i < graph.total_rows; ++i){
                                for (auto node : graph.board[i]){
                                    node->visited_maze = false;
                                    if (node != graph.start_node && node != graph.end_node){
                                        node->reset();
                                    } 
                                }
                            }
                            for (size_t i = 0; i < graph.total_rows; ++i){
                                for (auto node : graph.board[i]){
                                   node->update_neighbors(graph.board);  
                                }
                            }
                            switch (graph.current_maze_algo){
                                case Maze_Algorithms::RM:

                                    graph.algorithms.generate_maze(graph.board);

                                    for (size_t i = 0; i < graph.total_rows; ++i){
                                        for (size_t k = 0; k < graph.total_rows; ++k){
                                            if (graph.board[i][k]->visited_maze == false){
                                                maze_path[i].push_back(graph.board[i][k]);
                                            }
                                        }
                                    }
                                        
                                    graph.start_node->reset();
                                    graph.end_node->reset();
                                    graph.start_node = graph.board[0][0];
                                    graph.end_node = graph.board[graph.total_rows - 1][graph.total_rows - 1];
                                    graph.start_node->set_start();
                                    graph.end_node->set_target();
                                    visualize_maze = true;
                                break;
                                case Maze_Algorithms::RAND_T:
                                    graph.algorithms.random_terrain(graph.board, graph.start_node, graph.end_node, graph.total_rows);
                                break;
                                default:break;
                            }
                            mouse_down = true;
                        }
                    }
                }
            }
            else if (textures.clickable_in_range(textures.clear_ranges, mousePos)){
                if (graph.start_node != nullptr  && graph.end_node != nullptr){
                    if (!visualize_visiting && !visualize_path && !visualize_maze){
                        for (size_t i = 0; i < graph.total_rows; ++i){
                            for (auto node : graph.board[i]){
                                node->visited_maze = false;
                                if (node != graph.start_node && node != graph.end_node){
                                    node->reset();
                                }
                            }
                        }
                    }
                }
            }
            else if (textures.clickable_in_range(textures.astar_ranges, mousePos)){
                if (!mouse_down){
                    graph.current_algo = PF_Algorithms::Astar;
                    textures.position_check(0);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(textures.dijkstra_ranges, mousePos)){
                if (!mouse_down){
                    graph.current_algo = PF_Algorithms::Dijkstra;
                    textures.position_check(1);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(textures.bfs_ranges, mousePos)){
                if (!mouse_down){
                    graph.current_algo = PF_Algorithms::BFS;
                    textures.position_check(2);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(textures.dfs_ranges, mousePos)){
                if (!mouse_down){
                    graph.current_algo = PF_Algorithms::DFS;
                    textures.position_check(3);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(textures.rm_ranges, mousePos)){
                if (!mouse_down){
                    graph.current_maze_algo = Maze_Algorithms::RM;
                    textures.position_check(4);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(textures.rand_ranges, mousePos)){
                if (!mouse_down){
                    graph.current_maze_algo = Maze_Algorithms::RAND_T;
                    textures.position_check(5);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(textures.help_ranges, mousePos)){
                if (!mouse_down){
                    mouse_down = true;
                }
            }
            
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            sf::Vector2u rowcol = graph.rowcol_pos_click(mousePos.getPosition(*window));
            if (rowcol.x < graph.total_rows){
                if (!mouse_down){
                    Node* clicked_node = graph.board[rowcol.x][rowcol.y];
                    if (clicked_node == graph.start_node && graph.end_node != nullptr){
                        clicked_node->reset();
                        graph.start_node = nullptr;
                    }
                    else if (clicked_node == graph.end_node && graph.start_node != nullptr){
                        clicked_node->reset();
                        graph.end_node = nullptr;
                    }
                    else if (clicked_node != graph.start_node && clicked_node != graph.end_node) {
                        clicked_node->reset();
                    }
                }
            }

        }
        else
            mouse_down = false;
    }

}

void App::render(){
    window->clear(sf::Color::White);
    graph.draw_tiles(window, visualize_visiting);

    if (visualize_visiting){
        total_time += dt;
        if (total_time >= 0.013f){
            total_time -= 0.013f;
            if (visited_count != visited_nodes.size())
                visited_count++;
        }
        for (size_t i = 0; i < visited_count; ++i){
            for (auto open_neighbor : visited_nodes[i]->neighbors){
                if (open_neighbor != graph.start_node && open_neighbor != graph.end_node)
                    open_neighbor->set_open();
            }
            if (visited_nodes[i]->color != sf::Color(VISITED_COLOR)){
                if (visited_nodes[i] != graph.start_node && visited_nodes[i] != graph.end_node)
                    visited_nodes[i]->set_visited();
            }
            visited_nodes[i]->draw_node(window);
            

            if (i == visited_nodes.size() - 1){
                visualize_visiting = false;
                visualize_path = true;
                total_time = 0.0f;
                for (size_t i = 0; i < visited_nodes.size(); ++i){
                    if (visited_nodes[i] != graph.start_node && visited_nodes[i] != graph.end_node)
                        visited_nodes[i]->set_visited();
                }
                visited_nodes.clear();
                visited_count = 0;
            }
        }
    
    }

    if (visualize_path){
        total_time += dt;
        if (total_time >= 0.013f){
            total_time -= 0.013f;
            if (path_count != path_nodes.size())
                path_count++;
        }
        for (size_t i = 0; i < path_count; ++i){
            path_nodes[i]->set_path();
            path_nodes[i]->draw_node(window);
            if (i == path_nodes.size() - 1){
                visualize_path = false;
                finished_visualizing = true;
                total_time = 0.0f;
                path_nodes.clear();
                path_count = 0;
            }
        }
    }

    if (visualize_maze){
        total_time += dt;
        if (total_time >= 0.001f){
            total_time -= 0.001f;
            if (maze_count != graph.total_rows)
                maze_count++;

            for (size_t i = 0; i < maze_count; ++i){
                for (size_t k = 0; k < maze_path[i].size(); ++k){
                    if (maze_path[i][k]->color != sf::Color(OBSTRUCTION_COLOR))
                        maze_path[i][k]->set_obstruction();
                }
                if (i == graph.total_rows - 1){
                    visualize_maze = false;
                    total_time = 0;
                    maze_count = 0;
                    for (size_t i = 0; i < graph.total_rows; ++i){
                            maze_path[i].clear();
                    }
                  
                }
            }
        }
    }
    graph.draw_grid(window);

    window->draw(textures.visualize_sprite);
    window->draw(textures.algo_choice_text);
    window->draw(textures.astar_cb_sprite);
    window->draw(textures.astar_text);
    window->draw(textures.dijkstra_cb_sprite);
    window->draw(textures.dijkstra_text);
    window->draw(textures.bfs_cb_sprite);
    window->draw(textures.rec_cb_sprite);
    window->draw(textures.rand_cb_sprite);
    window->draw(textures.bfs_text);
    window->draw(textures.dfs_cb_sprite);
    window->draw(textures.dfs_text);
    window->draw(textures.recursive_maze_text);
    window->draw(textures.random_terrain_text);
    window->draw(textures.check_sprite);
    window->draw(textures.check2_sprite);
    window->draw(textures.terrain_text);
    window->draw(textures.generate_sprite);
    window->draw(textures.clear_sprite);
    window->draw(textures.thematic_break);
    window->draw(textures.legend_sprite);
    window->draw(textures.algorithm_log_text);
    window->draw(textures.help_sprite);

    if (graph.start_node == nullptr){
        graph.green_tile.setPosition(mousePos.getPosition(*window).x, mousePos.getPosition(*window).y);
        window->draw(graph.green_tile);
    }
    else if (graph.end_node == nullptr){
        graph.red_tile.setPosition(mousePos.getPosition(*window).x, mousePos.getPosition(*window).y);
        window->draw(graph.red_tile);
    }
    window->display();
}

void App::run(){
    while (window->isOpen()){
        update();
        render();
    }
}

App::~App(){
    for (size_t i = 0; i < graph.total_rows; ++i){
        for (auto *node : graph.board[i]){
            delete node;
        }
        for (auto *node2 : maze_path[i]){
            delete node2;
        }
    }
    delete [] graph.board;
    delete [] maze_path;
    delete window;
}