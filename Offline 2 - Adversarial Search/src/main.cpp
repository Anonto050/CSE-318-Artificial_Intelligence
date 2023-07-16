#include<iostream>
#include<climits>
#include<cmath>
#include<vector>
#include<string>

#include "lib/Constants.h"
#include "lib/Board.h"
#include "lib/Heuristic.h"
#include "lib/Color.h"
#include "lib/Player.h"

using namespace std;

int main() {
    Board board;

    // Take depths and heuristics from user
    
    int depth1, depth2, heuristic1, heuristic2;
    cout << "Enter depth for player 1: ";
    cin >> depth1;
    cout << "Enter depth for player 2: ";
    cin >> depth2;

    // show list of heuristics
    cout << "Heuristic list: " << endl;
    cout << "1. Storage" << endl;
    cout << "2. Bins" << endl;
    cout << "3. Additional Moves" << endl;
    cout << "4. Close Win" << endl;
    cout << "5. Capture" << endl;
    cout << "6. Extra Turn" << endl;

    cout << "Enter heuristic for player 1: ";
    cin >> heuristic1;
    cout << "Enter heuristic for player 2: ";
    cin >> heuristic2;

    Player player1(PLAYER_1, depth1, AI_VS_AI, heuristic1);
    Player player2(PLAYER_2, depth2, AI_VS_AI, heuristic2);

    // Player player1(PLAYER_1, 6, AI_VS_AI, HEURISTIC_STORAGE);
    // Player player2(PLAYER_2, 8, AI_VS_AI, HEURISTIC_STORAGE);

    int player_turn = PLAYER_1;
    int move;
    int previous_turn = -1;

    board.print_board();

    while(!board.gameOver()) {
        if(player_turn == INT_MIN){
            printRed("Illegal move, try again");
            player_turn = previous_turn;
        }

        previous_turn = player_turn;
        printGreen("Player " + to_string(player_turn + 1) + " turn\n");

        if(player_turn == PLAYER_1) {
            move = player1.playMove(board);
        } else if(player_turn == PLAYER_2) {
            move = player2.playMove(board);
        }
        else {
            cout << "Invalid player turn" << endl;
        }

        player_turn = board.playMove(player_turn, move);
        board.print_board();

        if(board.checkValidBoard()==false) {
            printRed("Invalid board");
            break;
        }

    }

    int mancalaWinner = board.get_winner();

    printBlue("Game is over");

    if(mancalaWinner == DRAW) {
        printBlue("It's a draw");
    } else {
        printBlue("Player " + to_string(mancalaWinner + 1) + " wins");
    }

    return 0;
}
