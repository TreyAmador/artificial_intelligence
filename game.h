#ifndef GAME_H_
#define GAME_H_
#include <vector>
#include <string>
#include <queue>
#include <map>
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
	Node* explored(int* config);

	// test after returning node
	bool in_explored(Node* node);

	//void read_file(const std::string& filepath);


private:
	// inlcudes config of game
	Board board_;

	// this should be hashed-to
	// test the config of the game, then check against explored set
	// std::vector<Node*> explored_;
	std::map<int, Node*> explored_;


	// set of leaf nodes
	std::priority_queue<Node*> frontier_;
	

};


#endif
