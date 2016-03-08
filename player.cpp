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
    
    if (testingMinimax) {

        // add opponent's move to our board
        gameboard->doMove(opponentsMove, them);

        if (gameboard->hasMoves(us))
        {
        // test print std::cerr << "Moves available" << std::endl;
        // test print std::cerr << "Getting move" << std::endl;
        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    Move * ourMove = new Move(i, j);
                    if (gameboard->checkMove(ourMove, us))
                    {
                        // test print std::cerr << "Placing piece at: " << ourMove->x << " " << ourMove->y
                        //          << std::endl;
                        // perform our move on our own board
                        gameboard->doMove(ourMove, us);
                        return ourMove;
                    }
                }
            }
        }
        return NULL;
    }

    // naive solution (working AI plays random valid moves)
    else {

        if (gameboard->hasMoves(us))
        {
            // test print std::cerr << "Moves available" << std::endl;
    		// test print std::cerr << "Getting move" << std::endl;
    		for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    Move * ourMove = new Move (i, j);
                    if (gameboard->checkMove(ourMove, us))
                    {
                        // test print std::cerr << "Placing piece at: " << ourMove->x << " " << ourMove->y
                        //          << std::endl;
                        // perform our move on our own board
                        gameboard->doMove(ourMove, us);
                        return ourMove;
                    }
                }
            }
    	}
        return NULL;
    }
}
