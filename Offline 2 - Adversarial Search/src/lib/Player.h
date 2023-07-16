#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <climits>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>        
#include <random>
#include <cstdlib>

#include "Constants.h"
#include "Board.h"
#include "Heuristic.h"
#include "Color.h"

using namespace std;

class Player {

    int player_id;
    int depth;
    int mode;
    int additional_turn;
    int heuristic;

    int estimateCost(Board currentBoard, Board previousBoard) {
        switch (heuristic) {
            case HEURISTIC_STORAGE:
                return heuristicStorage(player_id, currentBoard);
            case HEURISTIC_BINS:
                return heuristicBins(player_id, currentBoard);
            case HEURISTIC_AD_MOVES:
                return heuristicAdditionalMoves(player_id, additional_turn, currentBoard);
            case HEURISTIC_CLOSE_WIN:
                return heuristicCloseWin(player_id, currentBoard);
            case HEURISTIC_CAPTURE:
                return heuristicCapture(player_id, currentBoard, previousBoard);
            case HEURISTIC_EXTRA_TURN:
                return heuristicExtraTurn(player_id, currentBoard);
            case HEURISTIC_TOTAL:
                return heuristicTotal(player_id, additional_turn ,currentBoard, previousBoard);
            default:
                return 0;
            
        }
    }

    int min_max (Board currentBoard, Board prevBoard, bool isMAx, int alpha, int beta, int depthToReach) {
        int opponent_id = (player_id == PLAYER_1) ? PLAYER_2 : PLAYER_1;

        if(currentBoard.gameOver()) {
            if(currentBoard.get_winner() == player_id) {
                return INT_MAX/2;
            } else if(currentBoard.get_winner() == opponent_id) {
                return INT_MIN/2;
            } else {
                return estimateCost(currentBoard, prevBoard);
            }
        }

        if(depthToReach == 0) {
            return estimateCost(currentBoard, prevBoard);
        }

        Board tempBoard;
        tempBoard.copyBoard(currentBoard);

        if(isMAx){
            int maxEval = INT_MIN;
            int successor = -1;

            //Move ordering
            vector<int> serialMaxBins , serialMaxBinsRest;

            //bins that have chances to give extra turn go to serialMaxBins
            for(int i = 0; i < NUM_BINS; i++) {
                if(currentBoard.getBin(player_id, i) == (NUM_BINS - i)) {
                    serialMaxBins.push_back(i);
                }
                else {
                    serialMaxBinsRest.push_back(i);
                }
            }

            //move the rest ones to serialMaxBins to now
            for(int i = 0; i < serialMaxBinsRest.size(); i++) {
                serialMaxBins.push_back(serialMaxBinsRest.at(i));
            }

            // shuffle the serialMaxBins
            random_shuffle(serialMaxBins.begin(), serialMaxBins.end());

            //apply alpha beta pruning
            for (int i = 0; i < NUM_BINS; i++) {
                int presentMove = serialMaxBins.at(i);

                if(currentBoard.getBin(player_id, presentMove) > 0) {
                    int nextPlayer = currentBoard.playMove(player_id, presentMove);
                    int presentEval;

                    if(nextPlayer == player_id) {
                        additional_turn++;
                        presentEval = min_max(currentBoard, tempBoard, true, alpha, beta, depthToReach - 1);
                        additional_turn--;
                    } else {
                        presentEval = min_max(currentBoard, tempBoard, false, alpha, beta, depthToReach - 1);
                    }

                    if(presentEval > maxEval) {
                        maxEval = presentEval;
                        successor = presentMove;
                    }

                    alpha = max(alpha, maxEval);

                    if(beta <= alpha) {
                        break;
                    }

                    currentBoard.copyBoard(tempBoard);
                }
            }

            if(depthToReach == depth) {
                return successor;
            } else {
                return maxEval;
            }
        }

        else {
             int opponent_id = (player_id == PLAYER_1) ? PLAYER_2 : PLAYER_1;

            int minEval = INT_MAX;

            //Move ordering
            vector<int> serialMinBins , serialMinBinsRest;

            //bins that have chances to give extra turn go to serialMinBins
            for(int i = 0; i < NUM_BINS; i++) {
                if(currentBoard.getBin(player_id, i) == (NUM_BINS - i)) {
                    serialMinBins.push_back(i);
                }
                else {
                    serialMinBinsRest.push_back(i);
                }
            }

            //move the rest ones to serialMinBins to now
            for(int i = 0; i < serialMinBinsRest.size(); i++) {
                serialMinBins.push_back(serialMinBinsRest.at(i));
            }

            // shuffle the serialMinBins
            random_shuffle(serialMinBins.begin(), serialMinBins.end());


            //apply alpha beta pruning
            for (int i = 0; i < NUM_BINS; i++) {
                int presentMove = serialMinBins.at(i);

                if(currentBoard.getBin(opponent_id, presentMove) > 0) {
                    int nextPlayer = currentBoard.playMove(opponent_id, presentMove);
                    int presentEval;

                    if(nextPlayer == opponent_id) {
                        additional_turn--;
                        presentEval = min_max(currentBoard, tempBoard, false, alpha, beta, depthToReach - 1);
                        additional_turn++;
                    } else {
                        presentEval = min_max(currentBoard, tempBoard, true, alpha, beta, depthToReach - 1);
                    }

                    if(presentEval < minEval) {
                        minEval = presentEval;
                    }

                    beta = min(beta, minEval);

                    if(beta <= alpha) {
                        break;
                    }

                    currentBoard.copyBoard(tempBoard);
                }
            }

            return minEval;
        }
    }

    int moveOfHuman (Board currentBoard) {
        int move;
        cout << "Enter the bin number to move: ";
        cin >> move;
        while(currentBoard.getBin(player_id, move) == 0) {
            cout << "Invalid move. Enter the bin number to move: ";
            cin >> move;
        }
        return move;
    }

    public :

        Player(int player_id, int depth, int mode, int heuristic) {
            this->player_id = player_id;
            this->depth = depth;
            this->mode = mode;
            this->heuristic = heuristic;
            this->additional_turn = 0;
        }

        int getPlayerID() {
            return player_id;
        }

        int getDepth() {
            return depth;
        }

        int getMode() {
            return mode;
        }

        int getHeuristic() {
            return heuristic;
        }

        int getAdditionalTurn() {
            return additional_turn;
        }
        void setMode(int mode) {
            this->mode = mode;
        }

        void setAdditionalTurn(int additional_turn) {
            this->additional_turn = additional_turn;
        }

        int playMove(Board currentBoard) {
            switch (mode)
            {
          case AI_VS_AI:{
            additional_turn = 0;
            int move = min_max(currentBoard, currentBoard, true, INT_MIN, INT_MAX, depth);
            printYellow("Player " + to_string(player_id + 1) + " played move " + to_string(move + 1) + "\n");
            return move;
          }
            case PLAYER_VS_AI:{
               return moveOfHuman(currentBoard);
            }

            default:
                return -1;
           
        }
     }
    
};
    

#endif // !PLAYER_H