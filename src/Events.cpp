#include "Events.hpp"

Events_::Events_(sf::Vector2f &&windowSize) : graph(),
    texture_(graph.start_coord, graph.end_coord, windowSize){
    texture_.arrowSprite.setPosition(sf::Vector2f((graph.start_coord.x) + ((3.5f/768.0f) * sf::VideoMode::getDesktopMode().height), (graph.start_coord.y) + ((3.5f/768.0f) * sf::VideoMode::getDesktopMode().height)));
    texture_.targetSprite.setPosition(sf::Vector2f((graph.end_coord.x) + ((3.0f/768.0f) * sf::VideoMode::getDesktopMode().height), (graph.end_coord.y) + ((2.9f/768.0f) * sf::VideoMode::getDesktopMode().height)));
    visualizeInProgress = false;
    visualizeFinished = false;
    displayPath = false;
    algos = Algorithms_::Astar;
    totalTime = 0.0f;
    totalTime2 = 0.0f;
    visualizeRanges[0] = (588.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    visualizeRanges[1] = (796.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    visualizeRanges[2] = (26.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    visualizeRanges[3] = (87.0f/768.0f) * sf::VideoMode::getDesktopMode().height;

    reloadRanges[0] = (822.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    reloadRanges[1] = (871.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    reloadRanges[2] = (32.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    reloadRanges[3] = (81.0f/768.0f) * sf::VideoMode::getDesktopMode().height;

    clearRanges[0] = (437.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    clearRanges[1] = (551.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    clearRanges[2] = (51.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    clearRanges[3] = (68.0f/768.0f) * sf::VideoMode::getDesktopMode().height;

    AstarRanges[0] = (275.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    AstarRanges[1] = (303.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    AstarRanges[2] = (171.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    AstarRanges[3] = (200.0f/768.0f) * sf::VideoMode::getDesktopMode().height;

    dijkstraRanges[0] = (275.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    dijkstraRanges[1] = (303.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    dijkstraRanges[2] = (233.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    dijkstraRanges[3] = (262.0f/768.0f) * sf::VideoMode::getDesktopMode().height;

    bfsRanges[0] = (275.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    bfsRanges[1] = (303.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    bfsRanges[2] = (293.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    bfsRanges[3] = (323.0f/768.0f) * sf::VideoMode::getDesktopMode().height;

    dfsRanges[0] = (275.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    dfsRanges[1] = (303.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    dfsRanges[2] = (355.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    dfsRanges[3] = (384.0f/768.0f) * sf::VideoMode::getDesktopMode().height;
    
    choicePositions.push_back(sf::Vector2f((270.0f/768.0f) * sf::VideoMode::getDesktopMode().height,(152.0f/768.0f) * sf::VideoMode::getDesktopMode().height));
    choicePositions.push_back(sf::Vector2f((270.0f/768.0f) * sf::VideoMode::getDesktopMode().height,(213.0f/768.0f) * sf::VideoMode::getDesktopMode().height));
    choicePositions.push_back(sf::Vector2f((270.0f/768.0f) * sf::VideoMode::getDesktopMode().height,(274.0f/768.0f) * sf::VideoMode::getDesktopMode().height));
    choicePositions.push_back(sf::Vector2f((270.0f/768.0f) * sf::VideoMode::getDesktopMode().height,(335.0f/768.0f) * sf::VideoMode::getDesktopMode().height));
    texture_.checkSprite.setPosition(sf::Vector2f(choicePositions[0].x, choicePositions[0].y));
    objectCount = 1;
    visitedCount = 1;
    targetInDrag = false;
    startInDrag = false;
}

void Events_::clickEvents(sf::RenderWindow *window){
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if (!md_tile){
            if (!visualizeInProgress){
                for (auto curr_coord : graph.tileCoords){
                    float mousePos_x = mousePos.getPosition(*window).x;
                    float mousePos_y = mousePos.getPosition(*window).y;
                    if ((mousePos_x >= curr_coord.second.first.x && mousePos_x <= curr_coord.second.first.x + graph.objectSize) &&
                        (mousePos_y >= curr_coord.second.first.y && mousePos_y <= curr_coord.second.first.y + graph.objectSize)){
                        if (startInDrag){
                            if (!graph.tileCoords[curr_coord.first].second){
                                graph.point_index.first = curr_coord.first;
                                graph.start_coord.x = curr_coord.second.first.x;
                                graph.start_coord.y = curr_coord.second.first.y;

                                texture_.arrowSprite.setPosition(sf::Vector2f((graph.start_coord.x) + ((3.5f/768.0f) * sf::VideoMode::getDesktopMode().height), (graph.start_coord.y) + ((3.5f/768.0f) * sf::VideoMode::getDesktopMode().height)));
                                startInDrag = false;
                            }
                        } 
                        else if (targetInDrag){
                            if (!graph.tileCoords[curr_coord.first].second){
                                graph.point_index.second = curr_coord.first;
                                graph.end_coord.x = curr_coord.second.first.x;
                                graph.end_coord.y = curr_coord.second.first.y;

                                texture_.targetSprite.setPosition(sf::Vector2f((graph.end_coord.x) + ((3.0f/768.0f) * sf::VideoMode::getDesktopMode().height), (graph.end_coord.y) + ((2.9f/768.0f) * sf::VideoMode::getDesktopMode().height)));
                                targetInDrag = false;
                            }
                        }
                        else {
                            if (curr_coord.first != graph.point_index.first && curr_coord.first != graph.point_index.second){
                                    if (!curr_coord.second.second)
                                        graph.disconnectNode(curr_coord.first);
                                    // else 
                                    //     graph.reconnectNode(curr_coord.first);   
                            }
                            else {
                                if (curr_coord.first == graph.point_index.first)
                                    startInDrag = true;
                                else if (curr_coord.first == graph.point_index.second)
                                    targetInDrag = true;
                            }
                        }
                    }
                }
            }
            md_tile = true;
        }
    }
    else
        md_tile = false;
    


    /* STILL STATE */
    if (!visualizeInProgress){
        if (startInDrag)
            texture_.arrowSprite.setPosition(sf::Vector2f(mousePos.getPosition(*window).x, mousePos.getPosition(*window).y));
        if (targetInDrag)
            texture_.targetSprite.setPosition(sf::Vector2f(mousePos.getPosition(*window).x, mousePos.getPosition(*window).y));
        if (visualizeInRange()){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if (!md_visualize){
                    switch (algos){
                        case Algorithms_::Astar:
                            graph.WGA.A_star_search(graph.point_index.first, graph.point_index.second, graph.adjList, graph.tileCoords, graph.objectSize, graph.visitedNodes, graph.stopVisiting, graph.objectTiles);
    
                        break;
                        case Algorithms_::Dijkstra:
                            graph.WGA.dijkstra_algorithm(graph.point_index.first, graph.point_index.second, graph.adjList, graph.tileCoords, graph.objectSize, graph.visitedNodes, graph.stopVisiting, graph.objectTiles);
                            break;
                        case Algorithms_::BFS:
                            graph.UGA.bfs_algorithm(graph.point_index.first, graph.point_index.second, graph.adjList, graph.tileCoords, graph.objectSize, graph.visitedNodes, graph.stopVisiting, graph.objectTiles);
                            break;
                        case Algorithms_::DFS:
                            graph.UGA.dfs_algorithm(graph.point_index.first, graph.point_index.second, graph.adjList, graph.tileCoords, graph.objectSize, graph.visitedNodes, graph.stopVisiting, graph.objectTiles);
                            break;
                        default: break;
                    }
                    visualizeInProgress = true;
                    md_visualize = true;
                    sf::Cursor cursor;
                    cursor.loadFromSystem(sf::Cursor::Arrow);
                    window->setMouseCursor(cursor);
                }
            }
            else
                md_visualize = false;
            if (!visualize_handTrigger){
                sf::Cursor cursor;
                cursor.loadFromSystem(sf::Cursor::Hand);
                window->setMouseCursor(cursor);
                visualize_handTrigger = true;
            }
            
        }
        else {
            if (visualize_handTrigger){
                sf::Cursor cursor;
                cursor.loadFromSystem(sf::Cursor::Arrow);
                window->setMouseCursor(cursor);
                visualize_handTrigger = false; 
            }
        }

        if (AstarInRange()){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                algos = Algorithms_::Astar;
                texture_.checkSprite.setPosition(sf::Vector2f(choicePositions[algos].x, choicePositions[algos].y));
                md_checkBox = true;
            }
            else
                md_checkBox = false;
            if (!check_handTrigger){
                sf::Cursor cursor;
                cursor.loadFromSystem(sf::Cursor::Hand);
                window->setMouseCursor(cursor);
                check_handTrigger = true;
            }
        }
        else if (dijkstraInRange()){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                algos = Algorithms_::Dijkstra;
                texture_.checkSprite.setPosition(sf::Vector2f(choicePositions[algos].x, choicePositions[algos].y));
                md_checkBox = true;
            } else
               md_checkBox = false;
            if (!check_handTrigger){
                sf::Cursor cursor;
                cursor.loadFromSystem(sf::Cursor::Hand);
                window->setMouseCursor(cursor);
                check_handTrigger = true;
            }
        }
        else if (bfsInRange()){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                algos = Algorithms_::BFS;
                texture_.checkSprite.setPosition(sf::Vector2f(choicePositions[algos].x, choicePositions[algos].y));
                md_checkBox = true;
            } else
                md_checkBox = false;
            if (!check_handTrigger){
                sf::Cursor cursor;
                cursor.loadFromSystem(sf::Cursor::Hand);
                window->setMouseCursor(cursor);
                check_handTrigger = true;
            }
        }
        else if (dfsInRange()){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                algos = Algorithms_::DFS;
                texture_.checkSprite.setPosition(sf::Vector2f(choicePositions[algos].x, choicePositions[algos].y));
                md_checkBox = true;
            } else
                md_checkBox = false;
            if (!check_handTrigger){
                sf::Cursor cursor;
                cursor.loadFromSystem(sf::Cursor::Hand);
                window->setMouseCursor(cursor);
                check_handTrigger = true;
            }
        }
        else {
            if (check_handTrigger){
                sf::Cursor cursor;
                cursor.loadFromSystem(sf::Cursor::Arrow);
                window->setMouseCursor(cursor);
                check_handTrigger = false; 
            }
        }
    }
    else {
    }

}

void Events_::drawColoredTiles(sf::RenderWindow *window){
    if (visualizeInProgress){
        totalTime += dt;
        if (totalTime >= 0.013f){
            totalTime -= 0.013f;
            if (visitedCount != graph.visitedNodes.size())
                visitedCount++;
        }
        for (size_t i = 0; i < visitedCount; ++i){
            window->draw(graph.visitedNodes[i]);
            if (i == graph.visitedNodes.size() - 1)
                displayPath = true;
        }

        if (displayPath){
            totalTime2 += dt;
            if (totalTime2 >= 0.05f){
                totalTime2 -= 0.05f;
                if (objectCount != graph.objectTiles.size())
                    objectCount++;
            }
            for (size_t i = 0; i < objectCount; ++i){
                window->draw(graph.objectTiles[i]);
                if (i == graph.objectTiles.size() - 1)
                    visualizeFinished = true;
                    
            }
        }
    }

    if (visualizeFinished){
        if (reloadInRange()){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if (!md_reload){
                    visualizeFinished = false;
                    visualizeInProgress = false;
                    objectCount = 1;
                    graph.objectTiles.clear();
                    graph.visitedNodes.clear();
                    visitedCount = 1;
                    displayPath = false;
                    md_reload = true; 
                    this->graph.stopVisiting = false;
                    sf::Cursor cursor;
                    cursor.loadFromSystem(sf::Cursor::Arrow);
                    window->setMouseCursor(cursor);
                }
            }
            else
                md_reload = false;
            if (!reload_handTrigger){
                sf::Cursor cursor;
                cursor.loadFromSystem(sf::Cursor::Hand);
                window->setMouseCursor(cursor);
                reload_handTrigger = true;
            }
        }
        else {
            if (reload_handTrigger){
                sf::Cursor cursor;
                cursor.loadFromSystem(sf::Cursor::Arrow);
                window->setMouseCursor(cursor);
                reload_handTrigger = false;    
            }
        }
    }

    if (graph.obsCount > 0){
        if (!visualizeInProgress){
            if (clearInRange()){
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if (!md_clear){
                        graph.disconnectedNodes.clear();
                        graph.obstructions.clear();
                        graph.adjList = graph.adjListConstant;
                        graph.obsCount = 0;
                        for (auto &tile : graph.tileCoords)
                            tile.second.second = false;
                        sf::Cursor cursor;
                        cursor.loadFromSystem(sf::Cursor::Arrow);
                        window->setMouseCursor(cursor);
                        md_clear = true;
                    }
                }
                else
                    md_clear = false;
                if (!clear_handTrigger){
                    sf::Cursor cursor;
                    cursor.loadFromSystem(sf::Cursor::Hand);
                    window->setMouseCursor(cursor);
                    clear_handTrigger = true;  
                }
            }
            else {
                if (clear_handTrigger){
                    sf::Cursor cursor;
                    cursor.loadFromSystem(sf::Cursor::Arrow);
                    window->setMouseCursor(cursor);
                    clear_handTrigger = false; 
                }  
            }
        }
    }

    for (size_t i = 0; i < graph.obstructions.size(); ++i)
        window->draw(graph.obstructions[i]);

    if (visualizeFinished){
        window->draw(texture_.reloadSprite);
    }

    if (graph.obsCount > 0)
        window->draw(texture_.clearText);
}

bool Events_::visualizeInRange(){
    return ((mousePos.getPosition().x >= visualizeRanges[0] && mousePos.getPosition().x <= visualizeRanges[1]) &&
        (mousePos.getPosition().y >= visualizeRanges[2] && mousePos.getPosition().y <= visualizeRanges[3]));
}

bool Events_::reloadInRange(){
    return ((mousePos.getPosition().x >= reloadRanges[0] && mousePos.getPosition().x <= reloadRanges[1]) &&
        (mousePos.getPosition().y >= reloadRanges[2] && mousePos.getPosition().y <= reloadRanges[3]));
}

bool Events_::clearInRange(){
    return ((mousePos.getPosition().x >= clearRanges[0] && mousePos.getPosition().x <= clearRanges[1]) &&
        (mousePos.getPosition().y >= clearRanges[2] && mousePos.getPosition().y <= clearRanges[3]));
}

bool Events_::AstarInRange(){
    return ((mousePos.getPosition().x >= AstarRanges[0] && mousePos.getPosition().x <= AstarRanges[1]) &&
        (mousePos.getPosition().y >= AstarRanges[2] && mousePos.getPosition().y <= AstarRanges[3]));
}

bool Events_::dijkstraInRange(){
    return ((mousePos.getPosition().x >= dijkstraRanges[0] && mousePos.getPosition().x <= dijkstraRanges[1]) &&
        (mousePos.getPosition().y >= dijkstraRanges[2] && mousePos.getPosition().y <= dijkstraRanges[3]));
}

bool Events_::bfsInRange(){
    return ((mousePos.getPosition().x >= bfsRanges[0] && mousePos.getPosition().x <= bfsRanges[1]) &&
        (mousePos.getPosition().y >= bfsRanges[2] && mousePos.getPosition().y <= bfsRanges[3]));
}

bool Events_::dfsInRange(){
    return ((mousePos.getPosition().x >= dfsRanges[0] && mousePos.getPosition().x <= dfsRanges[1]) &&
        (mousePos.getPosition().y >= dfsRanges[2] && mousePos.getPosition().y <= dfsRanges[3]));
}