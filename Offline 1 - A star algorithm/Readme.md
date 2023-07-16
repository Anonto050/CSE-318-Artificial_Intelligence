## A* Search for N-Puzzle Problem

This is an implementation of the A* search algorithm for solving the N-Puzzle problem. The N-Puzzle problem involves a grid of numbers where one number is missing, and the goal is to rearrange the numbers in the grid to reach the desired configuration.

### Usage

To use the code, follow these steps:

1. Provide the size of the grid (`k`) as input.
2. Enter the numbers for the initial grid row by row.

The program will then solve the N-Puzzle problem using two different heuristics: the Hamming distance heuristic and the Manhattan distance heuristic. It will print the minimum number of moves required to solve the puzzle, the number of nodes expanded, and the number of nodes explored. It will also print the steps to reach the goal state.

### Node Class

The `Node` class represents a state in the N-Puzzle problem. It stores the grid configuration, the number of moves made to reach the current state, the position of the empty cell, and a pointer to the previous node. The class provides various utility functions such as checking for goal state, calculating distances, getting children nodes, and more.

### NPuzzle Class

The `NPuzzle` class handles the solving of the N-Puzzle problem using the A* algorithm with different heuristics. It contains functions for solving the problem with the Hamming distance heuristic and the Manhattan distance heuristic. It also includes helper functions for counting inversions, checking solvability, and printing the path to the goal state.

### How to Run

To run the code, compile and execute it in a C++ compiler. Make sure to include the necessary headers (`iostream`, `vector`, `queue`, `algorithm`, `unordered_set`, `string`) before compiling the code.

```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<unordered_set>
#include<string>

// ... (Code omitted for brevity)
```

After running the program, follow the instructions on the console to provide the input for the grid size and the initial grid configuration. The program will then solve the N-Puzzle problem and display the results.

Note: This code assumes valid input is provided, and error handling is not implemented for simplicity.

### Heuristics

The code uses two different heuristics to estimate the cost of reaching the goal state:

1. **Hamming Distance Heuristic**: The Hamming distance is the number of misplaced tiles in the current state compared to the goal state. It calculates the number of tiles that are not in their correct position.

2. **Manhattan Distance Heuristic**: The Manhattan distance is the sum of the horizontal and vertical distances of each tile from its goal position. It calculates the total number of moves required to move each tile to its desired position.

The A* algorithm uses these heuristics to prioritize the nodes for exploration and find the optimal solution efficiently.

### Solvability Check

Before solving the N-Puzzle problem, the code checks if the initial configuration is solvable. It uses the concept of inversions to determine solvability. An inversion occurs when a tile precedes another tile with a lower value. The code counts the number of inversions in the grid and checks if it satisfies the conditions for solvability based on the grid size (`k`). The details of the solvability check can be found in the `isSolvable` and `countInversions` functions.

### Summary

This code provides an implementation of the A* search algorithm for solving the N-Puzzle problem. It uses two different heuristics, the Hamming distance and the Manhattan distance, to estimate the cost of reaching the goal state. The code also includes a solvability check to ensure the provided initial configuration is solvable. By following the instructions and providing the necessary input, the code can be used to solve N-Puzzle problems efficiently.
