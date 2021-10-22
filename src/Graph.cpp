#include "Graph.hpp"
#include <iostream>

void Graph::construct_graph(){
    for (size_t i = 0; i < total_rows; ++i){
        for (size_t k = 0; k < total_rows; ++k)
            board[i].push_back(new Node(i, k, tile_gap, total_rows));
    }
}

Graph::Graph(uint32_t rows, uint32_t width){
    total_rows = rows;
    board_width = width;
    tile_gap = (float)board_width / (float)total_rows;
    current_algo = PF_Algorithms::Astar;
    current_maze_algo = Maze_Algorithms::RM;
    construct_graph();
    
    start_node = nullptr;
    end_node = nullptr;

    board[7][22]->set_start();
    start_node = board[7][22];

    board[37][22]->set_target();
    end_node = board[37][22];

    vertLine.setFillColor(sf::Color::Black);
    horLine.setFillColor(sf::Color::Black);
    vertLine.setSize(sf::Vector2f(1,width));
    horLine.setSize(sf::Vector2f(width,1));
    green_tile.setSize(sf::Vector2f(tile_gap, tile_gap));
    green_tile.setFillColor(START_COLOR);
    red_tile.setSize(sf::Vector2f(tile_gap, tile_gap));
    red_tile.setFillColor(TARGET_COLOR);
}

sf::Vector2i Graph::rowcol_pos_click(sf::Vector2i pos){
    uint32_t y = pos.x;
    uint32_t x = pos.y;
    uint32_t row = y / tile_gap;
    uint32_t col = x / tile_gap;
    return sf::Vector2i(row, col);
}

void Graph::draw_grid(sf::RenderWindow *window){
    float row_pos_y;
    float col_pos_x;

    for (size_t i = 0; i <= total_rows; ++i){
        row_pos_y = i * tile_gap;
        horLine.setPosition(0, row_pos_y);
        window->draw(horLine);
        for (size_t j = 0; j <= total_rows; ++j){
            col_pos_x = j * tile_gap;
            vertLine.setPosition(col_pos_x, 0);
            window->draw(vertLine);
        }
    }
}

void Graph::draw_tiles(sf::RenderWindow *window, bool visualize_visiting){
    for (auto row : board){
        for (auto node : row){
            if (!visualize_visiting)
                node->draw_node(window);
            else {
                if (node->color != sf::Color(VISITED_COLOR))
                    node->draw_node(window);
            }
        }
    }
}