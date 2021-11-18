#include "App.hpp"
#include <iostream>

App::App(uint32_t total_rows) : graph(total_rows, sf::VideoMode::getDesktopMode().height), textures(){
    window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Pathfinding Visualizer", sf::Style::Close);
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
                        for (size_t i = 0; i < graph.get_total_rows(); ++i){
                            for (auto node : graph.get_board()[i]){
                                node->visited_maze = false;
                                if (node != graph.STNodes().first && node != graph.STNodes().second){
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
                        graph.clear_graph();
                        delete [] maze_path;
                        maze_path = new std::vector<Node*>[row_sizes[mouse_scroll_value]];
                        graph.construct_graph(row_sizes[mouse_scroll_value], sf::VideoMode::getDesktopMode().height);
                        textures.position_check(0);
                        textures.position_check(4);
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
                    for (size_t i = 0; i < graph.get_total_rows(); ++i){
                        for (auto node : graph.get_board()[i]){
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
            else if (!(rowcol.x >= graph.get_total_rows()) && !(rowcol.y >= graph.get_total_rows())){
                Node* clicked_node = graph.get_board()[rowcol.x][rowcol.y];
                if (!(graph.STNodes().first) && clicked_node != graph.STNodes().second){
                    graph.assign_start(clicked_node);
                }
                else if (!(graph.STNodes().second) && clicked_node != graph.STNodes().first){
                    graph.assign_end(clicked_node);
                }
                else if (clicked_node != graph.STNodes().second && clicked_node != graph.STNodes().first){
                    clicked_node->set_obstruction();
                }
            }

            else if (textures.clickable_in_range(window, textures.visualize_ranges, mousePos)){
                if (graph.STNodes().first != nullptr  && graph.STNodes().second != nullptr){
                    if (!visualize_visiting && !visualize_path){
                        if (!mouse_down){

                            clock_timer = new sf::Clock();

                            graph.g_curr_search_algo()->run(graph.STNodes().first, graph.STNodes().second);
                            visited_nodes = graph.g_curr_search_algo()->getVisitedNodes();
                            path_nodes = graph.g_curr_search_algo()->getPathNodes();
                            graph.g_curr_search_algo()->reset_attributes();

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
            else if (textures.clickable_in_range(window, textures.generate_ranges, mousePos)){
                if (graph.STNodes().first != nullptr  && graph.STNodes().second != nullptr){
                    if (!visualize_visiting && !visualize_path && !visualize_maze){
                        if (!mouse_down){
                            for (size_t i = 0; i < graph.get_total_rows(); ++i){
                                for (auto node : graph.get_board()[i]){
                                    node->visited_maze = false;
                                    if (node != graph.STNodes().first && node != graph.STNodes().second){
                                        node->reset();
                                    } 
                                }
                            }
                            switch (graph.g_curr_maze_algo()){
                                case Maze_Algorithms::RM:
                                    graph.g_curr_terr_algo()->run(graph.STNodes().first);
                                    
                                    for (size_t i = 0; i < graph.get_total_rows(); ++i){
                                        for (size_t k = 0; k < graph.get_total_rows(); ++k){
                                            if (graph.get_board()[i][k]->visited_maze == false){
                                                maze_path[i].push_back(graph.get_board()[i][k]);
                                            }
                                        }
                                    }
                                        
                                    graph.STNodes().first->reset();
                                    graph.STNodes().second->reset();

                                    if (mouse_scroll_value == 3){
                                        graph.assign_start(graph.get_board()[(size_t)std::round(graph.get_total_rows() * Graph::ratio_row) - 1][graph.get_total_rows()/2]);
                                        graph.assign_end(graph.get_board()[graph.get_total_rows() - (size_t)std::round(graph.get_total_rows() * Graph::ratio_row)][graph.get_total_rows()/2]);
                                    }
                                    else if (mouse_scroll_value == 2){
                                        graph.assign_start(graph.get_board()[(size_t)std::round(graph.get_total_rows() * Graph::ratio_row) - 1][(graph.get_total_rows()/2) - 1]);
                                        graph.assign_end(graph.get_board()[graph.get_total_rows() - (size_t)std::round(graph.get_total_rows() * Graph::ratio_row)][(graph.get_total_rows()/2) - 1]);                                      
                                    }
                                    else if (mouse_scroll_value == 0){
                                        graph.assign_start(graph.get_board()[(size_t)std::round(graph.get_total_rows() * Graph::ratio_row)][(graph.get_total_rows()/2) - 1]);
                                        graph.assign_end(graph.get_board()[graph.get_total_rows() - (size_t)std::round(graph.get_total_rows() * Graph::ratio_row) - 1][(graph.get_total_rows()/2) - 1]);                                       
                                    }

                                    graph.STNodes().first->set_start();
                                    graph.STNodes().second->set_target();
                                    visualize_maze = true;
                                break;
                                case Maze_Algorithms::RAND_T:
                                    graph.g_curr_terr_algo()->run(graph.STNodes().first, graph.STNodes().second);
                                break;
                                default:break;
                            }
                            mouse_down = true;
                        }
                    }
                }
            }
            else if (textures.clickable_in_range(window, textures.clear_ranges, mousePos)){
                if (graph.STNodes().first != nullptr  && graph.STNodes().second != nullptr){
                    if (!visualize_visiting && !visualize_path && !visualize_maze){
                        for (size_t i = 0; i < graph.get_total_rows(); ++i){
                            for (auto node : graph.get_board()[i]){
                                node->visited_maze = false;
                                if (node != graph.STNodes().first && node != graph.STNodes().second){
                                    node->reset();
                                }
                            }
                        }
                    }
                }
            }
            else if (textures.clickable_in_range(window, textures.astar_ranges, mousePos)){
                if (!mouse_down){
                    graph.assign_curr_search_algo(Enum_Search::ASTAR);
                    textures.position_check(0);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(window, textures.dijkstra_ranges, mousePos)){
                if (!mouse_down){
                    graph.assign_curr_search_algo(Enum_Search::DIJKSTRA);
                    textures.position_check(1);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(window, textures.bfs_ranges, mousePos)){
                if (!mouse_down){
                    graph.assign_curr_search_algo(Enum_Search::BFS);
                    textures.position_check(2);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(window, textures.dfs_ranges, mousePos)){
                if (!mouse_down){
                    graph.assign_curr_search_algo(Enum_Search::DFS);
                    textures.position_check(3);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(window, textures.rm_ranges, mousePos)){
                if (!mouse_down){
                    graph.assign_curr_terr_algo(Maze_Algorithms::RM);
                    textures.position_check(4);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(window, textures.rand_ranges, mousePos)){
                if (!mouse_down){
                    graph.assign_curr_terr_algo(Maze_Algorithms::RAND_T);
                    textures.position_check(5);
                    mouse_down = true;
                }
            }
            else if (textures.clickable_in_range(window, textures.help_ranges, mousePos)){
                if (!mouse_down){
                    mouse_down = true;
                }
            }
            
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            std::cout << "Clicking right" << std::endl;
            sf::Vector2u rowcol = graph.rowcol_pos_click(mousePos.getPosition(*window));
            std::cout << rowcol.x << " " << rowcol.y << std::endl;
            if (rowcol.x < graph.get_total_rows()){
                if (!mouse_down){
                    Node* clicked_node = graph.get_board()[rowcol.x][rowcol.y];
                    if (clicked_node == graph.STNodes().first && graph.STNodes().second != nullptr){
                        clicked_node->reset();
                        graph.remove_start();
                    }
                    else if (clicked_node == graph.STNodes().second && graph.STNodes().first != nullptr){
                        clicked_node->reset();
                        graph.remove_end();
                    }
                    else if (clicked_node != graph.STNodes().first && clicked_node != graph.STNodes().second) {
                        clicked_node->reset();
                    }
                }
                            std::cout << "Clicking second" << std::endl;
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
                if (open_neighbor != graph.STNodes().first && open_neighbor != graph.STNodes().second)
                    open_neighbor->set_open();
            }
            if (visited_nodes[i]->color != sf::Color(VISITED_COLOR)){
                if (visited_nodes[i] != graph.STNodes().first && visited_nodes[i] != graph.STNodes().second)
                    visited_nodes[i]->set_visited();
            }
            visited_nodes[i]->draw_node(window);
            

            if (i == visited_nodes.size() - 1){
                visualize_visiting = false;
                visualize_path = true;
                total_time = 0.0f;
                for (size_t i = 0; i < visited_nodes.size(); ++i){
                    if (visited_nodes[i] != graph.STNodes().first && visited_nodes[i] != graph.STNodes().second)
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
            if (maze_count != graph.get_total_rows())
                maze_count++;

            for (size_t i = 0; i < maze_count; ++i){
                for (size_t k = 0; k < maze_path[i].size(); ++k){
                    if (maze_path[i][k]->color != sf::Color(OBSTRUCTION_COLOR))
                        maze_path[i][k]->set_obstruction();
                }
                if (i == graph.get_total_rows() - 1){
                    visualize_maze = false;
                    total_time = 0;
                    maze_count = 0;
                    for (size_t i = 0; i < graph.get_total_rows(); ++i){
                            maze_path[i].clear();
                    }
                  
                }
            }
        }
    }
    graph.draw_grid(window);

    textures.drawSprites(window);

    graph.draw_ST_tiles(window, mousePos);

    window->display();
}

void App::run(){
    while (window->isOpen()){
        update();
        render();
    }
}

App::~App(){
    graph.clear_graph();
    delete [] maze_path;

    delete window;
}