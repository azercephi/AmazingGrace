#ifndef __PLAYER_H__
#define __PLAYER_H__
#define PLYCOUNT 2

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


class MoveChooser {

public:
	MoveChooser(Board * board); // needs to take in current board
	~MoveChooser();

	// State variables: 

	// how far are we looking into the future?
	int PlyCount = PLYCOUNT;

	// what's our current test score?
	int TestScore;

	// move that got to current test board state
	Move *originMove;

	// vector member holding all possible moves from this point on
	std::vector<Move> possMoves;

	// vector of pointers for those moves, man
	std::vector<Move*> possMovesPtr;

	// final minimum child score
	int BranchMinScore;

};

#endif
