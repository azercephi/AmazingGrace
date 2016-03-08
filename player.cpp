#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    
    // save side
    us = side;
    // Side them; 

    if (us == BLACK) 
    {
        them = WHITE;
    }
    else 
    {
        them = BLACK;
    }

    // initialize board
	gameboard = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete gameboard;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 

    // add opponent's move to our board
    gameboard->doMove(opponentsMove, them);
    
    if (testingMinimax) 
    {
        // make a vector of boards-result possibilities that spring from your original board, 
        // from which we will end up only choosing one
        vector<Board> OurBector = MakeBector(gameboard, us);

        // then let's iterate through the boards in that vector, updating their ChildMinScore
        // so we can choose the one with the lowest such score
        for (int i = 0; i < OurBector.size(); i++) 
        {
            // make a vector of the opponent's possible boards
            vector<Board> TheirBector = MakeBector(OurBector[i], them);

            // get the ChildMinScore
            OurBector[i].ChildMinScore = FindMinBoard(TheirBector, us);
        }

        // find the member of OurBector with the lowest ChildMinScore

        minChildMin = OurBector[0].ChildMinScore;
        minimaxBoard = OurBector[0];

        for (int i = 1; i < OurBector.size(); i++) 
        {
            if (OurBector[i].ChildMinScore > minChildMin)
            {
                minChildMin = OurBector[i].ChildMinScore;
                minimaxBoard = OurBector[i];
            }
        }

        gameboard->doMove(minimaxBoard->originMove, us);
    }

    // naive solution (working AI plays random valid moves)
    else 
    {

        if (gameboard->hasMoves(us))
        {
            // test print std::cerr << "Moves available" << std::endl;
    		// test print std::cerr << "Getting move" << std::endl;
    		for (int i = 0; i < 8; i++) 
            {
                for (int j = 0; j < 8; j++) 
                {
                    Move move(i, j);
                    if (gameboard->checkMove(&move, us))
                    {
                        // test print std::cerr << "Placing piece at: " << ourMove->x << " " << ourMove->y
                        //          << std::endl;
                        // perform our move on our own board
                        Move * iMove = new Move(i, j);
                        gameboard->doMove(iMove, us);
                        return iMove;
                    }
                }
            }
    	}
        return NULL;
    }
}



// given starting board and a side, make a vector of the boards resulting from all your 
// possible moves
vector<Board> MakeBector(Board board, Side side) {
    
    vector<Move*> MyMovector = MakeMovector(board, side);

    vector<Board> MyBector;
    for (int i = 0; i < MyMovector.size(); i++) 
    {
        // make a new board to explore with
        Board * testboard = board.copy();

        // perform our move on testboard
        testboard.doMove(MyMovector[i], side);

        // give testboard an origin move
        testboard.originMove = MyMovector[i];

        // add testboard to Bector
        MyBector.push_back(testboard);
    }

    return MyBector;
}


// given starting board, generate vector of possible moves
vector<Move*> MakeMovector(Board board, Side side) {

    vector<Move*> MyMovector;
    if (board.hasMoves(side))
    {
        for (int i = 0; i < 8; i++) 
        {
            for (int j = 0; j < 8; j++) 
            {
                Move move(i, j);
                if (board.checkMove(&move, side))
                {
                    Move * newMove = new Move(i, j);
                    MyMovector.push_back(newMove);
                }
            }
        }

        return MyMovector;
    }
    return NULL;
}


// this function finds the maximum score among the boards given a vector of boards
// returns the board
Board FindMaxBoard(vector<Board> Bector, Side side) {
    int maxScore = FindBoardScore(Bector[0], side);
    Board maxBoard;
    for (int i = 1; i < Bector.size(); i++) 
    {
        if (FindBoardScore(Bector[i], side) > maxScore) 
        {
            maxScore = FindBoardScore(Bector[i], side);
            maxBoard = Bector[i];
        }
    }
    return maxBoard;
}


// this function finds the minimum score among the boards given a vector of boards
// returns the board with the lowest score
int FindMinBoard(vector<Board> Bector, Side side) {
    int minScore = FindBoardScore(Bector[0], side);
    Board minBoard;
    for (int i = 1; i < Bector.size(); i++) 
    {
        if (FindBoardScore(Bector[i], side) < minScore) 
        {
            minScore = FindBoardScore(Bector[i], side);
            minBoard = Bector[i];
        }
    }
    return minScore;
}


int FindBoardScore(Board board, Side side) {
    if (side == WHITE) 
    {
        return board.countWhite() - board.countBlack();
    }
    else 
    {
        return board.countBlack() - board.countWhite();
    }
}


/* Initialize MoveChooser
 *
 *
 *
 *
 *
 */

MoveChooser::MoveChooser(Board * board) {
    // needs to take in current board
}


MoveChooser::~MoveChooser() {

}

// move that got to current proposed board state
Move *originMove;

// vector member holding all possible moves from this point

// final minimum child score
int BranchMinScore;