#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include <vector>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    vector<Board> MakeBector(Board board, Side side);
    vector<Move*> MakeMovector(Board board, Side side);
    vector<Move*> MakeMovector2(Board board, Side side);
    Board FindMaxBoard(vector<Board> Bector, Side side);
    int FindMinBoard(vector<Board> Bector, Side side, int backup);
    int FindBoardScore(Board board, Side side);
    int Minimax(Board * board, Side side, int depth, int CurrentDepth,
                    int alpha, int beta);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    
    // state variables
    Side us;
    Side them;
    Board *gameboard;
};

#endif
