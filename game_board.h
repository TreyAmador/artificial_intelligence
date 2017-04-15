#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_
#include <vector>


class GameBoard {

public:
	GameBoard();
	GameBoard(int dimension);
	~GameBoard();

	bool is_complete();
	void print();


private:
	void initialize(int dimension);
	bool is_square(int n);
	

private:
	// this doesn't have to be 2D array
	std::vector<std::vector<int> > board_;


};

#endif

