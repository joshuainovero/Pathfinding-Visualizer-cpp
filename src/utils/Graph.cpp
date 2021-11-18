#include "Graph.hpp"
#include <iostream>

Graph::Graph(uint32_t rows, uint32_t width){
    vertLine.setFillColor(sf::Color::Black);
    horLine.setFillColor(sf::Color::Black);

    green_tile.setFillColor(START_COLOR);
    red_tile.setFillColor(TARGET_COLOR);

    construct_graph(rows, width);
}

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
    
    board[(size_t)std::round(total_rows * Graph::ratio_row)][total_rows/2]->set_start();
    start_node = board[(size_t)std::round(total_rows * Graph::ratio_row)][total_rows/2];

    board[total_rows - (size_t)std::round(total_rows * Graph::ratio_row) - 1][total_rows/2]->set_target();
    end_node = board[total_rows - (size_t)std::round(total_rows * Graph::ratio_row) - 1][total_rows/2];

    search_algorithms.push_back(new Astar_(board, total_rows, start_node, end_node));
    search_algorithms.push_back(new Dijkstra_(board, total_rows, start_node, end_node));
    search_algorithms.push_back(new BFS_(board, total_rows, start_node, end_node));
    search_algorithms.push_back(new DFS_(board, total_rows, start_node, end_node));

    terrain_algorithms.push_back(new RecursiveMaze(board, total_rows));
    terrain_algorithms.push_back(new RandomTerrain(board, total_rows));

    current_search_algo = search_algorithms[Enum_Search::ASTAR];
    current_terrain_algo = terrain_algorithms[Maze_Algorithms::RM];
    current_maze_algo = Maze_Algorithms::RM;
}

void Graph::clear_graph(){
    for (size_t i = 0; i < total_rows; ++i){
        for (Node *node : board[i]) {
            delete node;
        }
        board[i].clear();
    }
    delete [] board;
    for (auto algo : search_algorithms)
        delete algo;

    for (auto algo : terrain_algorithms)
        delete algo;

    search_algorithms.clear();
    terrain_algorithms.clear();
}


sf::Vector2u Graph::rowcol_pos_click(sf::Vector2i pos){
    uint32_t y = pos.x;
    uint32_t x = pos.y;
    uint32_t row = y / tile_gap;
    uint32_t col = x / tile_gap;
    return sf::Vector2u(row, col);
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

void Graph::assign_start(Node* v__){ 
    start_node = v__; 
    start_node->set_start();
}

void Graph::assign_end(Node* v__) { 
    end_node = v__; 
    end_node->set_target();
}

void Graph::remove_start() { start_node = nullptr; }

void Graph::remove_end() { end_node = nullptr; }

void Graph::assign_curr_search_algo(Enum_Search v__){
    current_search_algo = search_algorithms[v__];
}

void Graph::assign_curr_terr_algo(Maze_Algorithms v__){
    current_maze_algo = v__;
    current_terrain_algo = terrain_algorithms[current_maze_algo];
}

void Graph::draw_ST_tiles(sf::RenderWindow* window, sf::Mouse& mousePos){
    if (start_node == nullptr){
        green_tile.setPosition(mousePos.getPosition(*window).x, mousePos.getPosition(*window).y);
        window->draw(green_tile);
    }
    else if (end_node == nullptr){
        red_tile.setPosition(mousePos.getPosition(*window).x, mousePos.getPosition(*window).y);
        window->draw(red_tile);
    }
}

std::vector<Node*>* Graph::get_board() const { return board; }

uint32_t Graph::get_total_rows() const { return total_rows ;}

std::pair<Node*, Node*> Graph::STNodes() const { return std::make_pair(start_node, end_node); }

Search_* Graph::g_curr_search_algo() const { return current_search_algo; }

Algorithm_* Graph::g_curr_terr_algo() const { return current_terrain_algo; }

Maze_Algorithms Graph::g_curr_maze_algo() const { return current_maze_algo; }