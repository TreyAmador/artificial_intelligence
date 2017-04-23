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
		return a->cost() > b->cost();
	}
};

typedef std::priority_queue<Node*, std::vector<Node*>, Comparator> Frontier;
typedef std::map<int, Node*> Explored;
typedef Explored::iterator ExIter;


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


private:
	void select_move();
	void move(Node* node, int dir);
	
	int manhattan_heuristic(int* config);
	int misplaced_heuristic(int* config);

	int open_slot(int* config);
	int hash_key(int* config);
	void add_node(
		int* config,
		int cost,
		int heuristic,
		Node* parent,
		int open);
	
	bool top_open(int row);
	bool bottom_open(int row);
	bool left_open(int col);
	bool right_open(int col);
	bool in_explored(Node* node);
	bool is_complete();

	std::vector<Node*> path(Node* node);
	void reset();
	void clear_frontier();
	void clear_explored();


private:
	Explored explored_;
	Frontier frontier_;
	

};


#endif
