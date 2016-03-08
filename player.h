#ifndef __PLAYER_H__
#define __PLAYER_H__
#define PLYCOUNT 2

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
    vector<Board> MakeBector(Board * board, Side side);
    vector<Move*> MakeMovector(Board * board, Side side);
    Board FindMaxBoard(vector<Board> Bector, Side side);
    int FindMinBoard(vector<Board> Bector, Side side);
    int FindBoardScore(Board * board, Side side);

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

	// what's our current board score?
	int BoardScore;

	// vector member holding all possible moves from this point on
	vector<Move> possMoves;

	// vector of pointers for those moves, man
	vector<Move*> possMovesPtr;


	// move following two variables to board class
	// move that got to current test board state
	Move *originMove;

	// final minimum child score
	int ChildMinScore;

};

#endif
