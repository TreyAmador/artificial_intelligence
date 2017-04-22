#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_
#include <vector>
#include <queue>
#include <map>
#include <queue>
struct Node;


class Board {

public:
	Board();
	~Board();

	// to be stored in new nodes
	int* store_config();
	int* configuration();

	// put new node in frontier if not explored
	void move(
		std::map<int,Node*> explored,
		std::priority_queue<Node*> frontier);

	int manhattan_heuristic();
	int misplaced_heuristic();

	// pass in config,
	// if in frontier, do not explore
	int hash_key(int* config);

	bool is_solvable();
	bool is_complete();
	void in_order();
	void print();

	void test_case();


	void set_configuration(int* config);

	
private:
	


private:
	int* configuration_;
	int open_ptr_;

};

#endif

