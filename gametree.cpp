#include <iostream>
#include "common.h"
#include "board.h"
#include <vector>
#include <stdio.h>
#include <assert.h>
using namespace std;

class GameTree {

private:
	struct Node {
		// number of many moves in the future
		// if odd -> opponent
		unsigned int layer;
		
		// current board
		Board* curr;
		
		// what move was taken to get here from previous step is stored 
		// in board object

		// pointer to vector of next possible set of boards
		vector<Node*> Bector;
		
		// constructor
		Node(Board* board, unsigned int l) {
			curr = board;
			layer = l;
		}
		
		// destructor
		~Node() {
			if (Bector.empty())
			{
				// delete all pointers in Bector
				for (auto &b : Bector)
				{
					delete b;
				}
			}
		}
		
		// populates Bector
		void MakeBector(Side nextSide) {
			assert(curr != NULL);
			
			// iterate through all squares to find valid moves
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					Move move(i, j);
					// if a valid move is found
					if (curr->checkMove(&move, nextSide))
					{
						// make a new board to explore with
						Board * testboard = curr->copy();

						// perform our move on testboard
						testboard->doMove(&move, nextSide);

						// give testboard an origin move
						testboard->originMove = &move;

						// create and add Node to Bector
						Node* newNode = new Node(testboard, layer + 1);
						Bector.push_back(newNode);
					}
				}
			}
		}
		
		// grow into a tree of desired depth
		int grow(unsigned int depth, Side us, Side them) {
			while (layer != depth)
			{
				// figure out which side is next
				Side nextSide = ((layer & 2) == 0) ? them : us;
				this->MakeBector(nextSide);
				
				// recurse
				for (auto &b : Bector) {
					b->grow(depth, us, them);
				}
			}
			
			return 1; // equivalent to return true
		}
	};
	
	// create a game tree of depth # of moves into future
	
	// minimax upwards
	
	Node * root;
	
	unsigned int depth;
	
	Side us, them;
	
public:
    GameTree(Board* curr, unsigned int ply, Side side) {
		// initialize total depth
		depth = ply;
		
		// initialize root node
		root->layer = 0;
		root->curr = curr;
		
		// save sides
		us = side;
		them = (us == BLACK) ? WHITE : BLACK; 
	}

    ~GameTree() { delete root; }
    
    int scry() {
		return root->grow(depth, us, them);
	}
};

int main()
{
	// Create board with example state. You do not necessarily need to use
    // this, but it's provided for convenience.
    char boardData[64] = {
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', 'b', ' ', ' ', ' ', ' ', ' ', ' ', 
        'b', 'w', 'b', 'b', 'b', 'b', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };
    Board *board = new Board();
    board->setBoard(boardData);
    
	GameTree* tree = new GameTree(board, 2, BLACK);
	
	return tree->scry();
}
