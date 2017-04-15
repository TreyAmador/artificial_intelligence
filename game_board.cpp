#include <iostream>
#include "game_board.h"


namespace {
	const int DEFAULT_DIMENSION = 9;
}


GameBoard::GameBoard() {
	this->initialize(DEFAULT_DIMENSION);
}


GameBoard::GameBoard(int dimension) {
	if (!this->is_square(dimension))
		dimension = DEFAULT_DIMENSION;
	this->initialize(dimension);
}


GameBoard::~GameBoard() {
	// clear vector
}


void GameBoard::initialize(int elements) {
	int dim = static_cast<int>(std::sqrt(elements));
	board_.resize(dim, std::vector<int>(dim));
	for (int i = 0; i < elements; ++i) {
		board_[i/dim][i%dim] = i;
	}
}


bool GameBoard::is_complete() {
	int dim = static_cast<int>(board_.size());
	int size = dim*dim;
	for (int i = 0; i < size; ++i)
		if (board_[i/dim][i%dim] != i)
			return false;
	return true;
}


bool GameBoard::is_square(int n) {
	if (n < 0)
		return false;
	int root = static_cast<int>(std::round(std::sqrt(n)));
	return n == root * root;
}


void GameBoard::print() {
	for (size_t r = 0; r < board_.size(); ++r) {
		for (size_t c = 0; c < board_[r].size(); ++c) {
			std::cout << board_[r][c] << " ";
		}
		std::cout << "\n";
	}
}


