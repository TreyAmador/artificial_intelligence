#ifndef GAME_H_
#define GAME_H_
#include <vector>
#include <string>
#include <queue>
#include <map>
#include "node.h"


class Comparator {
public:
	bool operator()(Node*& a, Node*& b) {
		return a->h_+a->g_ > b->h_+b->g_;
	}
};

typedef std::priority_queue<Node*, std::vector<Node*>, Comparator> FrontierQueue;


enum {
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
	int hash_key(int* config);

	// this needs to be revised
	int permutations();

	void move();

	bool top_open(int row);
	bool bottom_open(int row);
	bool left_open(int col);
	bool right_open(int col);

	//void create_node(int* config);

	void move(Node* node, int dir);

	void swap_indeces(int* config, int a, int b);

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

	int* copy_config(int* config);

	void reset();

	//void test_cases();

	bool complete();



private:
	

	// this should be hashed-to
	// test the config of the game, then check against explored set
	// std::vector<Node*> explored_;
	std::map<int, Node*> explored_;


	// set of leaf nodes
	// set lowest h(n) as priority
	FrontierQueue frontier_;

};


#endif
