#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    // Set to true now so that player stategy is minimax
    testingMinimax = true;
    
    // save sides
    us = side;
    them = (us == BLACK) ? WHITE : BLACK;

    // initialize a board to keep track of game state
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
    // add opponent's move to our board
    gameboard->doMove(opponentsMove, them);
    
    // print opponent move
    if (opponentsMove == NULL)
    {
        cerr << "PASS"<< endl;
    }
    else
    {
        cerr << "Opponent: " << opponentsMove->x << " " << opponentsMove->y << endl;
    }
    
    // implement Minimax
    if (testingMinimax) 
    {
        // make a vector of our moves at current depth
        vector<Move*> Movector = MakeMovector(*gameboard, us); 

        // check edge case
        if (Movector.empty())
        {
            return NULL;
        }

        // if moves exist
        else
        {
            int BestScore = -70; // want lowest value of score
            Move * BestMove = NULL;

            for (unsigned int i = 0; i < Movector.size(); i++)
            {
                Board * gameboardcopy = gameboard->copy();
                gameboardcopy->doMove(Movector[i], us);
                int score = Minimax(gameboardcopy, them, 5, 1);
                if (score > BestScore)
                {
                    BestMove = Movector[i];
                    BestScore = score;
                }
            }

            // perform our move on our own board
            gameboard->doMove(BestMove, us);

            cerr << "Grace: " << BestMove->x << " " << BestMove->y << endl;
            return BestMove;
        }
    }

    // naive solution (working AI plays random valid moves)
    else 
    {
        if (gameboard->hasMoves(us))
        {
    		for (int i = 0; i < 8; i++) 
            {
                for (int j = 0; j < 8; j++) 
                {
                    Move move(i, j);
                    if (gameboard->checkMove(&move, us))
                    {
                        // perform our move on our own board
                        Move * iMove = new Move(i, j);
                        gameboard->doMove(iMove, us);
                        // return move to actual game
                        return iMove;
                    }
                }
            }
    	}
    }
    
    // shouldn't actually hit this case...
    // std::cerr << "Grace: idk" << std::endl; 
    return NULL;
}


/* given starting board and a side, make a vector of the boards resulting from 
 * all your possible moves */
vector<Board> Player::MakeBector(Board board, Side side) {
    
    vector<Move*> MyMovector = MakeMovector(board, side);

    vector<Board> MyBector;
    for (unsigned int i = 0; i < MyMovector.size(); i++) 
    {
        // make a new board to explore with
        Board * testboard = board.copy();

        // perform our move on testboard
        testboard->doMove(MyMovector[i], side);

        // give testboard an origin move
        testboard->originMove = MyMovector[i];

        // add testboard to Bector
        MyBector.push_back(*testboard);
    }

    return MyBector;
}


/* given starting board, generate vector of possible moves */
vector<Move*> Player::MakeMovector(Board board, Side side) {

    vector<Move*> MyMovector;
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

/* Generate vector of possible moves by only checking the unoccuppied spaces
 */
vector <Move*> Player::MakeMovector2(Board board, Side side) {
    vector<Move*> MyMovector;
    
    // only check unoccuppied spaces
    std::set<Move>::iterator it;
    for (it = board.possible.begin(); it !=board.possible.end(); ++ it) {
        Move *move = &(*it);
        if (board.checkMove(move, side)) {
            MyMovector.push_back(move);
        }
    }
    
    return MyMovector;
}

/* this function finds the maximum score among the boards given a vector of 
 * boards and returns the correponding board */
Board Player::FindMaxBoard(vector<Board> Bector, Side side) {
    int maxScore = FindBoardScore(Bector[0], side);
    Board maxBoard;
    for (unsigned int i = 1; i < Bector.size(); i++) 
    {
        if (FindBoardScore(Bector[i], side) > maxScore) 
        {
            maxScore = FindBoardScore(Bector[i], side);
            maxBoard = Bector[i];
        }
    }
    return maxBoard;
}


/* this function finds the minimum score among the boards given a vector of 
 * boards returns the lowest score */
int Player::FindMinBoard(vector<Board> Bector, Side side, int backup) {
    // if opponent has no moves left, return original score
    if (Bector.empty())
    {
        return backup;
    }
    // else
    int minScore = FindBoardScore(Bector[0], side);
    Board minBoard;
    for (unsigned int i = 1; i < Bector.size(); i++) 
    {
        if (FindBoardScore(Bector[i], side) < minScore) 
        {
            minScore = FindBoardScore(Bector[i], side);
            minBoard = Bector[i];
        }
    }
    return minScore;
}


int Player::FindBoardScore(Board board, Side side) {
    if (side == WHITE) 
    {
        return board.countWhite() - board.countBlack();
    }
    else 
    {
        return board.countBlack() - board.countWhite();
    }
}


 /*
OUTLINE

minimax(Board, Side, Depth)
    int BestScore = -INFTY //best score for each level

    if no legal moves
        return current board score
    
    for each legal move
        Board.copy
        copy.domove
        score = minimax()
        compare score to BestScore, 
    return BestScore
 */

int Player::Minimax(Board * board, Side side, int depth, int CurrentDepth) {
    
    if (CurrentDepth == depth)
    {
        return FindBoardScore(*board, side);
    }

    // else
    vector<Move*> Movector = MakeMovector(*board, side);
    if (Movector.empty())
    {
        return FindBoardScore(*board, side);
    }

        // else

    // instead of switching checking for min / max every layer,
    // each recursive call looks 2 plays ahead and just returns the max
    if (CurrentDepth % 2 == 0) // parity 0, our side's move, maximize score
    {
        int BestScore = -70; 
        
        for (unsigned int i = 0; i < Movector.size(); i++)
        {
            // create an board one move into future
            Board * boardcopy = board->copy();
            boardcopy->doMove(Movector[i], side);
            
            Side nextside = (side == BLACK) ? WHITE : BLACK;
            
            // recursive call
            int score = Minimax(boardcopy, nextside, depth, CurrentDepth + 1);
            // update if appropriate
            if (score > BestScore)
            {
                BestScore = score;
            }
        }
        return BestScore;
    }

    else // parity 1, opponent's move, minimize score
    {
        int WorstScore = 70;
        for (unsigned int i = 0; i < Movector.size(); i++)
        {
            // create an board one move into future
            Board * boardcopy = board->copy();
            boardcopy->doMove(Movector[i], side);

            Side nextside = (side == BLACK) ? WHITE : BLACK;
            // recursive call
            int score = Minimax(boardcopy, nextside, depth, CurrentDepth + 1);
            // update if appropriate
            if (score < WorstScore)
            {
                WorstScore = score;
            }
        }
        return WorstScore;
    }

}
