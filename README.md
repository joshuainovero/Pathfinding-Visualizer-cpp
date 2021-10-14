# Pathfinding Visualizer #
Visualize common pathfinding algorithms through the animations of this application! 

## What is Pathfinding? ##
In computer science, there are a lot of situations that require us to find the shortest path between a set of points. Graphs are essential in pathfinding algorithms; in basic terms, graphs exist as an environment, and their traversals are calculated by the type of pathfinding algorithm being used.

## How to use ##
### Setting the starting node and the target node ###
If you want to move the starting node and target node from their default location, you can simply click them and drag them around the board.
### Adding a wall ###
The white tiles on the board are the only ones that can be used to place wall nodes. A "Clear Board" button will appear if there is a wall present on the board.
### Choosing an algorithm ###
The A* algorithm is selected by default. You can select a different a algorithm by clicking the other boxes on the left panel.
### Visualize! ###
After you set your configurations, you can now press the "Visualize" button at the middle-top of the screen.

## Available algorithms ##
- A* Search - The A* search algorithm extends the principles of Dijkstra's shortest path algorithm to provide a faster solution to the problem of finding the shortest path between two nodes. It accomplishes this by introducing a heuristic element to assist in determining the next node to consider as it moves along the path.
- Dijkstra's Algorithm - Dijkstra's algorithm finds the shortest path from a starting node to a target node in a weighted graph. The algorithm constructs a tree of the shortest paths from the starting vertex, known as the source, to all other points in the graph.
- Breadth-First Search - One of the fundamental graph traversal algorithms is breadth first search. It begins with a chosen node and visits all of its neighbors one hop away before moving on to all of its neighbors two hops away, and so on. Take note that this algorithm is only applicable to unweighted graphs.
- Depth-First Search - Depth First Search is the other fundamental graph traversal algorithm. It starts from a chosen node, picks one of its neighbors, and then traverses as far as it can along that path before backtracking. It also only applicable to unweighted graphs. Additionally, DFS is not optimal as it produce a much longer path than any pathfinding algorithms such as BFS. 

## Screenshots ##

