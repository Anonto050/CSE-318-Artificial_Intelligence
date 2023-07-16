# Adversarial Search with Alpha-Beta Pruning and Minimax Algorithm

This is an implementation of an adversarial search algorithm using the Minimax algorithm with Alpha-Beta pruning. The program allows two AI players to play against each other in the game of Mancala. The Minimax algorithm is used to search through the game tree and determine the best possible move for each player.

## How to Use

1. Clone the repository to your local machine or download the source code files.

2. Compile the code using a C++ compiler. For example, you can use g++ to compile the code:

   ```
   g++ main.cpp -o mancala
   ```

3. Run the executable:

   ```
   ./mancala
   ```

4. The program will prompt you to enter the depth and heuristic values for each player. The depth determines how far ahead the algorithm will search in the game tree, and the heuristic determines the evaluation function used to estimate the desirability of a particular game state.

5. The program will display the current state of the game board and indicate which player's turn it is. The players will take turns making moves.

6. Enter the chosen move by specifying the index of the bin you want to pick from. The bins are numbered from left to right, starting from 0.

7. The program will update the game board and display the new state.

8. The game continues until one of the players wins or the game ends in a draw. The final result will be displayed, indicating the winning player or a draw.

## Heuristics

The program provides a set of heuristics that can be used to evaluate the game state. During the initialization, you will be asked to choose a heuristic value for each player. Here are the available heuristics:

1. Storage: Evaluates the number of stones in the player's storage bin.
2. Bins: Evaluates the difference in the number of stones between the player's bins and the opponent's bins.
3. Additional Moves: Evaluates the number of additional moves the player can make based on the last move.
4. Close Win: Evaluates whether the player is close to winning the game.
5. Capture: Evaluates the number of captures the player can make based on the last move.
6. Extra Turn: Evaluates the number of extra turns the player can get based on the last move.

## Dependencies

The code relies on the following dependencies:

- `lib/Constants.h`: Contains the constant values used in the game.
- `lib/Board.h`: Represents the game board and provides functions to manipulate the board state.
- `lib/Heuristic.h`: Defines the heuristics used to evaluate the game state.
- `lib/Color.h`: Provides functions to print colored text in the console.
- `lib/Player.h`: Represents a player and provides functions to make moves based on the chosen heuristic and search depth.

Ensure that these dependencies are present in the same directory as the main code file.

## Contributions

Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request on the [GitHub repository](https://github.com/your-username/repository).
