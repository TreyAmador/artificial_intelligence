#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_
#include <vector>


class GameBoard {

public:
	GameBoard();
	~GameBoard();

	int manhattan_heuristic();
	int misplaced_heuristic();

	bool is_solvable();
	bool is_complete();
	void in_order();
	void print();

	void test_case();

	int permutations();
	int hash_key(int* board);
	bool explored(int key);

	
private:
	


private:
	int* board_;
	bool* explored_;


};

#endif

