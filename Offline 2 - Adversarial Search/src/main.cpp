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

    Player player1(PLAYER_1, 5, AI_VS_AI, HEURISTIC_STORAGE);
    Player player2(PLAYER_2, 12, AI_VS_AI, HEURISTIC_STORAGE);

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
