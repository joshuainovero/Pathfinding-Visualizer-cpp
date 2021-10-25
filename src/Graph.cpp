#include "Graph.hpp"
#include <iostream>

void Graph::construct_graph(uint32_t rows, uint32_t width){
    board = new std::vector<Node*>[rows];
    total_rows = rows;
    board_width = width;
    tile_gap = (float)board_width / (float)total_rows;

    for (size_t i = 0; i < total_rows; ++i){
        for (size_t k = 0; k < total_rows; ++k)
            board[i].push_back(new Node(i, k, tile_gap, total_rows));
    }

    vertLine.setSize(sf::Vector2f(1,width));
    horLine.setSize(sf::Vector2f(width,1));
    green_tile.setSize(sf::Vector2f(tile_gap, tile_gap));
    red_tile.setSize(sf::Vector2f(tile_gap, tile_gap));

    start_node = nullptr;
    end_node = nullptr;
    
    const float ratio_row = 0.1555555556f;
    uint32_t row_pos = std::round(total_rows * ratio_row);
    uint32_t col_pos = total_rows / 2;
    board[row_pos][col_pos]->set_start();
    start_node = board[row_pos][col_pos];

    board[total_rows - row_pos - 1][col_pos]->set_target();
    end_node = board[total_rows - row_pos - 1][col_pos];
}

Graph::Graph(uint32_t rows, uint32_t width){
    vertLine.setFillColor(sf::Color::Black);
    horLine.setFillColor(sf::Color::Black);
    construct_graph(rows, width);

    green_tile.setFillColor(START_COLOR);
    red_tile.setFillColor(TARGET_COLOR);

    current_algo = PF_Algorithms::Astar;
    current_maze_algo = Maze_Algorithms::RM;
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
    for (size_t i = 0; i < total_rows; ++i){
        for (auto node : board[i]){
            if (!visualize_visiting)
                node->draw_node(window);
            else
                if (node->color != sf::Color(VISITED_COLOR))
                    node->draw_node(window);
        }
    }
}