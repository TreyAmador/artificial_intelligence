#ifndef GAME_H_
#define GAME_H_
#include <vector>
#include <string>
#include <queue>
#include <map>
#include "board.h"
#include "node.h"


class Comparator {
public:
	bool operator()(Node*& a, Node*& b) {
		return a->h_ > b->h_;
	}
};

typedef std::priority_queue<Node*, std::vector<Node*>, Comparator> FrontierQueue;


enum Direction {
	UP = -3,
	DOWN = 3,
	LEFT = -1,
	RIGHT = 1
};


class Game {


public:
	Game();
	~Game();

	int run();

	// will need user input function
	// will nedd file reading functions


private:
	// hashes the configs
	//int hash_key(int* board);

	// this needs to be revised
	int permutations();

	void move(Node*& node);

	// return explored node,
	// or nullptr
	// then test if nullptr
	//Node* explored(int* config);

	// test after returning node
	bool in_explored(Node* node);

	//void read_file(const std::string& filepath);


	// pass in node->configuration_;
	int manhattan_heuristic(int* config);
	int misplaced_heuristic(int* config);

	int open_slot(int* config);

	// get user input
	int* prompt();

	void reset();


	//void test_cases();



private:
	// direction enum
	Direction direction_;


	// this should be hashed-to
	// test the config of the game, then check against explored set
	// std::vector<Node*> explored_;
	std::map<int, Node*> explored_;


	// set of leaf nodes
	// set lowest h(n) as priority
	FrontierQueue frontier_;

};


#endif
