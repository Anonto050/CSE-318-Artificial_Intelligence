#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <iostream>
#include <cmath>
#include <vector>
#include "Board.h"
#include "Color.h"
#include "Constants.h"

using namespace std;

//Heuristic 1: Storage

int heuristicStorage(int playerID ,Board currentBoard) {
   int opponentID = (playerID + 1) % NUM_PLAYERS;
   return currentBoard.getStorage()[playerID] - currentBoard.getStorage()[opponentID];
}

//Heuristic 2: Bins

int heuristicBins(int playerID, Board currentBoard) {
   int opponentID = (playerID + 1) % NUM_PLAYERS;
   int playerBins = 0;
    int opponentBins = 0;
    for(int i = 0; i < NUM_BINS; i++) {
        playerBins += currentBoard.getBin(playerID, i);
        opponentBins += currentBoard.getBin(opponentID, i);
    }
    return WEIGHT_STORAGE * heuristicStorage(playerID, currentBoard) + WEIGHT_BINS * (playerBins - opponentBins);
}

//Heuristic 3: Additional Moves

int heuristicAdditionalMoves(int playerID, int additionalMoves ,Board currentBoard) {
    return heuristicBins(playerID, currentBoard) + WEIGHT_AD_MOVES * additionalMoves;
}

//Heuristic 4: Close Win

int heuristicCloseWin(int playerID, Board currentBoard) {
    int halfStones = NUM_BINS * NUM_STONES ;
    int value = floor (100 * currentBoard.getStorage()[playerID] / halfStones);
    return value;
}       

//Heuristic 5: Far Win
//How many stones player captured in the last move
int heuristicCapture(int playerID, Board currentBoard, Board previousBoard) {
    int opponentID = (playerID + 1) % NUM_PLAYERS;
    int capturedStones = 0;
    for (int i = 0; i < NUM_BINS; i++) {
        int opponent_bin_num = NUM_BINS - i - 1;
        if((previousBoard.getBin(playerID, i) == 0) && (currentBoard.getBin(playerID, i) == 0)) {
            if((previousBoard.getBin(opponentID, opponent_bin_num) != 0) && (currentBoard.getBin(opponentID, opponent_bin_num) == 0)) {
                capturedStones += previousBoard.getBin(opponentID, opponent_bin_num);
            }
        }
    }
    return WEIGHT_CAPTURE * capturedStones;
}

//Heuristic 6: Extra Turn
//How many moves can lead to an extra turn
int heuristicExtraTurn(int playerID, Board currentBoard) {
    int extraTurns = 0;
    for(int i = 0; i < NUM_BINS; i++) {
        if(currentBoard.getBin(playerID, i) == (NUM_BINS - i)) {
            extraTurns++;
        }
    }
    return WEIGHT_EXTRA_TURN * extraTurns;
}

//Heuristic 7: Total Heuristic : Additional Moves + Close Win + Capture + Extra Turn
int heuristicTotal(int playerID, int additionalMoves, Board currentBoard, Board previousBoard) {
    return heuristicAdditionalMoves(playerID, additionalMoves, currentBoard) + heuristicCloseWin(playerID, currentBoard) 
         + heuristicCapture(playerID, currentBoard, previousBoard) + heuristicExtraTurn(playerID, currentBoard);
}

#endif // !HEURISTIC_H
