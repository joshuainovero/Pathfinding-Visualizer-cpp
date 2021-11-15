# Pathfinding Visualizer #
Visualize common pathfinding algorithms through the animations of this application! 

## What is Pathfinding? ##
In computer science, there are a lot of situations that require us to find the shortest path between a set of points. Graphs are essential in pathfinding algorithms; in basic terms, graphs exist as an environment, and their traversals are calculated by the type of pathfinding algorithm being used.

## For Linux ##
If you want to build binaries from source in linux, you must install the SFML package:
```sh
sudo apt-get install libsfml-dev
```

## How to use ##
### Setting the starting node and the target node ###
If you want to move the starting node and target node from their default location, you can simply right click them and drag them around the board.
### Adding and deleting a wall ###
The white tiles on the board are the only ones that can be used to place wall nodes. To delete a wall, you can right click the tiles that are marked as obstructed. The obstructions can be cleared with a button if you've placed too many obstacles on the board or created a maze.
### Choosing an algorithm ###
The A* algorithm is selected by default. You can select a different a algorithm by clicking the other boxes on the left panel.
### Visualize! ###
After you set your configurations, you can now press the "Visualize" button at the middle-top of the screen.

## Available algorithms ##
- A* Search - the A* search algorithm extends the principles of Dijkstra's shortest path algorithm to provide a faster solution to the problem of finding the shortest path between two nodes. It accomplishes this by introducing a heuristic element to assist in determining the next node to consider as it moves along the path.
- Dijkstra's Algorithm - Dijkstra's algorithm finds the shortest path from a starting node to a target node in a weighted graph. The algorithm constructs a tree of the shortest paths from the starting vertex, known as the source, to all other points in the graph.
- Breadth-First Search - one of the fundamental graph traversal algorithms is breadth first search. It begins with a chosen node and visits all of its neighbors one hop away before moving on to all of its neighbors two hops away, and so on. Take note that this algorithm is only applicable to unweighted graphs.
- Depth-First Search - Depth-First Search is the other fundamental graph traversal algorithm. It starts from a chosen node, picks one of its neighbors, and then traverses as far as it can along that path before backtracking. It is also only applicable to unweighted graphs. Additionally, DFS is not optimal as it produce a much longer path than any pathfinding algorithms such as BFS. 

## Maze Algorithms ##
- Recursive Backtracker - a randomized version of the depth-first search algorithm. It generates a perfect maze with no closed off areas or loops.
- Random Terrain - generates random tile obstructions and uses the simple rand() function. The generated random terrain may obstruct both the start node and the target node.

## Screenshots ##
![1](https://user-images.githubusercontent.com/78135477/138394780-b488789b-34d7-4fd3-9d4b-c017cdbdca79.png)
![2](https://user-images.githubusercontent.com/78135477/138394790-9bbc951d-bf16-4093-9426-9c9de3c7a895.png)
![3](https://user-images.githubusercontent.com/78135477/138394793-8f617ef9-e1a1-4043-8eed-6c4796099c66.png)
![4](https://user-images.githubusercontent.com/78135477/138394801-298ca8d9-ab06-4fb5-ba29-acb5b1ed98ce.png)
![5](https://user-images.githubusercontent.com/78135477/138394802-012e00c5-bc6c-46d5-ae62-92d01bb7cd12.png)
![6](https://user-images.githubusercontent.com/78135477/138394853-18efe4ee-32da-495a-888c-7b7626efd066.png)