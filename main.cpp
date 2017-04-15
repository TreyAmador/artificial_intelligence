#include <iostream>
#include "game_board.h"


int main(int argc, char* argv[]) {

	GameBoard board = GameBoard();
	board.print();
	if (board.is_complete())
		std::cout << "DONE!" << std::endl;

	return 0;
}

