#ifndef CONSTANTS_H
#define CONSTANTS_H

// Mancala game constants
#define NUM_BINS 6
#define NUM_PLAYERS 2
#define NUM_STONES 4
#define TOTAL_STONES NUM_BINS * NUM_STONES * NUM_PLAYERS 


// Minmax algorithm constants
#define MINMAX_DEPTH 5

// Game mode constants
#define AI_VS_AI 0
#define PLAYER_VS_AI 1
#define MODE_ITERATIVE 2

// Player constants
#define PLAYER_1 0
#define PLAYER_2 1
#define DRAW 2

// Heuristic constants weights
#define WEIGHT_STORAGE 5
#define WEIGHT_BINS 2
#define WEIGHT_AD_MOVES 6
#define WEIGHT_CLOSE_WIN 8
#define WEIGHT_CAPTURE 2
#define WEIGHT_EXTRA_TURN 6

// Heuristic options constants
#define HEURISTIC_STORAGE 0
#define HEURISTIC_BINS 1
#define HEURISTIC_AD_MOVES 2
#define HEURISTIC_CLOSE_WIN 3
#define HEURISTIC_CAPTURE 4
#define HEURISTIC_EXTRA_TURN 5

#define HEURISTIC_TOTAL 100

#endif // CONSTANTS_H


