#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_
#include <vector>
#include <queue>


class Board {

public:
	Board();
	~Board();

	// to be stored in new nodes
	int* store_config();
	int* configuration();

	int manhattan_heuristic();
	int misplaced_heuristic();

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

