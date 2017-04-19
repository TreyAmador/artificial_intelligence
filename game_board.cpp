#include <algorithm>
#include <iostream>
#include <numeric>
#include "game_board.h"


namespace {
	const int ELEMENTS = 9;
}


GameBoard::GameBoard() :
	board_(new int[ELEMENTS])
{}


GameBoard::~GameBoard() {
	if (board_ != nullptr) {
		delete[] board_;
		board_ = nullptr;
	}
}


int GameBoard::misplaced_heuristic() {
	int displaced = 0;
	for (int i = 0; i < ELEMENTS; ++i)
		if (board_[i] != i)
			++displaced;
	return displaced;
}


int GameBoard::manhattan_heuristic() {
	int displaced = 0;

	return 0;
}


void GameBoard::test_case() {
	board_[0] = 1;
	board_[1] = 2;
	board_[2] = 4;
	board_[3] = 0;
	board_[4] = 5;
	board_[5] = 6;
	board_[6] = 8;
	board_[7] = 3;
	board_[8] = 7;

}

void GameBoard::in_order() {
	for (int i = 0; i < ELEMENTS; ++i)
		board_[i] = i;
}



bool GameBoard::is_solvable() {
	return true;
}


bool GameBoard::is_complete() {
	for (int i = 0; i < ELEMENTS; ++i)
		if (board_[i] != i)
			return false;
	return true;
}


void GameBoard::print() {
	int dim = static_cast<int>(std::sqrt(ELEMENTS));
	for (int r = 0; r < dim; ++r) {
		for (int c = 0; c < dim; ++c) {
			std::cout << board_[r*dim + c] << " ";
		}
		std::cout << "\n";
	}
}


