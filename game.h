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
	
	void solve_heuristic(int* config, int (Game::*heuristic)(int*));

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
	
	inline bool top_open(int row);
	inline bool bottom_open(int row);
	inline bool left_open(int col);
	inline bool right_open(int col);

	bool is_solvable(int* config);
	inline bool is_complete();
	inline bool exit_requested(int* config);

	std::vector<Node*> path(Node* node);
	void reset();
	void clear_frontier();
	void clear_explored();


private:
	Explored explored_;
	Frontier frontier_;
	

};


#endif
