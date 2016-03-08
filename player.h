#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    
    // state variables
    Side us;
    Side them;
    Board *gameboard;
};


class WhichMove {

public:
	ChooseMove(Board board); // needs to take in current board
	~ChooseMove();

	// State variables: 

	// move that got to current proposed board state
	Move *originMove;

	// vector member holding all possible moves from this point
	Move *possibleMove;

	// final minimum child score
	int BranchMinScore;

};

#endif
