#ifndef GAME_H_
#define GAME_H_
#include <vector>
#include <queue>
#include "board.h"
struct Node;


class Game {


public:
	Game();
	~Game();

	int run();

	// will need user input function
	// will nedd file reading functions


private:
	// hashes the configs
	int hash_key(int* board);

	// this needs to be revised
	int permutations();

	// return explored node,
	// or nullptr
	// then test if nullptr
	Node* explored();

	// test after returning node
	bool in_explored(Node* node);


private:
	// inlcudes config of game
	Board board_;

	// this should be hashed-to
	// test the config of the game, then check against explored set
	// this could be implemented as an unordered_map as well
	std::vector<Node*> explored_;
	//Node* explored_;

	// set of leaf nodes
	std::priority_queue<Node*> frontier_;
	

};


#endif
