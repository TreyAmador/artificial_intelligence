#include <iostream>
#include "game_board.h"


int main(int argc, char* argv[]) {

	GameBoard board = GameBoard();
	
	board.test_case();
	board.print();

	//std::cout << board.misplaced_heuristic() << std::endl;
	//std::cout << board.manhattan_heuristic() << std::endl;

	std::cout << board.explored(0) << std::endl;

	return 0;
}

