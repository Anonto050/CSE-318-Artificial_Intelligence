#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <climits>
#include <cmath>
#include "Constants.h"
#include "Color.h"

using namespace std;

class Board {

    int bins[NUM_PLAYERS][NUM_BINS];
    int storage[NUM_PLAYERS];

    public :
     
    Board() {
        
        for(int i = 0; i < NUM_PLAYERS; i++) {
            storage[i] = 0;
            for(int j = 0; j < NUM_BINS; j++) {
                bins[i][j] = NUM_STONES;
            }
        }
    }

    void copyBoard(Board board) {
        for(int i = 0; i < NUM_PLAYERS; i++) {
            storage[i] = board.storage[i];
            for(int j = 0; j < NUM_BINS; j++) {
                bins[i][j] = board.bins[i][j];
            }
        }
    }

    int* getStorage() {
        return storage;
    }

    int getBin(int player, int bin) {
        return bins[player][bin];
    }

    void setBin(int player, int bin, int value) {
        bins[player][bin] = value;
    }
    
    bool checkValidBoard() {
        //check all stones in board are equal to TOTAL_STONES
        int totalStones = 0;
        for(int i = 0; i < NUM_PLAYERS; i++) {
            for(int j = 0; j < NUM_BINS; j++) {
                totalStones += bins[i][j];
            }
        }
        totalStones += storage[0] + storage[1];
        return totalStones == TOTAL_STONES;
    }

    int playMove (int player, int bin_num) {
        int stones = bins[player][bin_num];
        bins[player][bin_num] = 0;
        
        //check for errors
        if((bin_num < 0) || (bin_num >= NUM_BINS) || (stones == 0)) {
            cout << "Invalid bin" << endl;
            return INT_MIN;
        }
        
        //play move
        int opponent = (player + 1) % NUM_PLAYERS;
        int nextPlayer = opponent;

        int totalBins = NUM_BINS * NUM_PLAYERS + 1;
        int stonesPerBin = floor(stones / totalBins);
        int extraStones = stones % totalBins;

        //distribute stones
        for (int i = 0; i < NUM_BINS; i++) {
            bins[player][i] += stonesPerBin;
            bins[opponent][i] += stonesPerBin;
        }
        storage[player] += stonesPerBin;

        /* If there are 13 stones, then the last stone falls into 
        the starting bin of the player. So player gets opposite stones with 
        his own last stone */

        if (stones == 13) {
            storage[player] += bins[opponent][NUM_BINS - bin_num - 1];
            storage[player]++;
            bins[opponent][NUM_BINS - bin_num - 1] = 0;
            bins[player][bin_num] = 0;
        }

        //distribute extra stones
        for (int i = bin_num + 1; i < NUM_BINS; i++) {
            if(extraStones > 0) {
                bins[player][i]++;
                extraStones--;

                if((extraStones == 0) && (bins[player][i] == 1)) {
                    if (bins[opponent][NUM_BINS - i - 1] > 0) {
                        storage[player] += bins[opponent][NUM_BINS - i - 1];
                        storage[player]++;
                        bins[opponent][NUM_BINS - i - 1] = 0;
                        bins[player][i] = 0;
                    }
                    
                }
            }
            
        }

        if (extraStones > 0) {
            storage[player]++;
            extraStones--;

            if (extraStones == 0) {
                nextPlayer = player;
            }
        }

        //Now stones goes to opponent bin
        for (int i = 0; i < NUM_BINS; i++) {
            if(extraStones > 0) {
                bins[opponent][i]++;
                extraStones--;
            }
        }
        
        for(int i = 0; i <=bin_num && extraStones > 0; i++) {
            bins[player][i]++;
            extraStones--;

            if((extraStones == 0) && (bins[player][i] == 1)) {
                if (bins[opponent][NUM_BINS - i - 1] > 0) {
                    storage[player] += bins[opponent][NUM_BINS - i - 1];
                    storage[player]++;
                    bins[opponent][NUM_BINS - i - 1] = 0;
                    bins[player][i] = 0;
                }
                
            }
        }

        return nextPlayer;

    }

    bool gameOver() {
        //check if both storage have 48 stones
        if (storage[0] + storage[1] == TOTAL_STONES) {
            return true;
        }

        //check if first player has no stones in bins
        int totalStones = 0;
        for(int i = 0; i < NUM_BINS; i++) {
            totalStones += bins[PLAYER_1][i];
        }
        if (totalStones == 0) {
            return true;
        }

        //check if second player has no stones in bins
        totalStones = 0;
        for(int i = 0; i < NUM_BINS; i++) {
            totalStones += bins[PLAYER_2][i];
        }
        if (totalStones == 0) {
            return true;
        }

        return false;
    }

    int get_winner() {
        if(gameOver() == false) {
            printRed("Game is not over yet");
            return INT_MIN;
        }

        int Player1Stones = storage[PLAYER_1];
        int Player2Stones = storage[PLAYER_2];

        for(int i = 0; i < NUM_BINS; i++) {
            Player1Stones += bins[PLAYER_1][i];
            Player2Stones += bins[PLAYER_2][i];
        }

        if(Player1Stones > Player2Stones) {
            return PLAYER_1;
        } else if(Player1Stones < Player2Stones) {
            return PLAYER_2;
        } else {
            return DRAW;
        }
    }

    void print_board () {
        cout<<endl;
        cout<<"                 Player 2      "<<endl<<endl;

        cout<<"   ";
        for (int i = NUM_BINS - 1; i >= 0; i--) {
            cout << " < " << i << " > ";
        }

        cout<<endl;
        cout<<"   ";
        for (int i = NUM_BINS - 1; i >= 0; i--) {
            cout << "   " << bins[PLAYER_2][i] << "   ";
        }
        cout<<endl; 
        cout<<storage[PLAYER_2];
        cout<<"                     ";

        for(int i = 0; i < NUM_BINS; i++) {
            cout<<"  ";
        }
        cout<<"          ";
        cout<<storage[PLAYER_1];
        cout<<endl;
        cout<<"   ";
        for (int i = 0; i < NUM_BINS; i++) {
            cout << "   " << bins[PLAYER_1][i] << "   ";
        }
        cout<<endl;
        cout<<"   ";

        for (int i = 0; i < NUM_BINS; i++) {
            cout << " < " << i << " > ";
        }
        cout<<endl<<endl;
        cout<<"                 Player 1      "<<endl<<endl;
    }
};


#endif // !CONSTANTS_H