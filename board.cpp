#include <algorithm>
#include <iostream>
#include <numeric>
#include "board.h"


namespace {
	const int ELEMENTS = 9;
	const int DIMENSION = static_cast<int>(std::sqrt(ELEMENTS));
}


Board::Board() :
	configuration_(new int[ELEMENTS])
{
	// test case
	// init the gameboard config here
	// have a user input function in game obj?
	this->test_case();

	// set pointer to zero element
	for (int i = 0; i < ELEMENTS; ++i)
		if (configuration_[i] == 0)
			open_ptr_ = i;

}


Board::~Board() {
	if (configuration_ != nullptr) {
		delete[] configuration_;
		configuration_ = nullptr;
	}
}


int* Board::store_config() {
	int* config = new int[ELEMENTS];
	for (int i = 0; i < ELEMENTS; ++i)
		config[i] = configuration_[i];
	return config;
}


int* Board::configuration() {
	return configuration_;
}


int Board::misplaced_heuristic() {
	int displaced = 0;
	for (int i = 0; i < ELEMENTS; ++i)
		if (configuration_[i] != i && configuration_[i] != 0)
			++displaced;
	return displaced;
}


int Board::manhattan_heuristic() {
	int displacement = 0;
	for (int i = 0; i < ELEMENTS; ++i) {
		if (configuration_[i] != 0) {
			int r = i / DIMENSION, c = i%DIMENSION;
			int o = configuration_[i] / DIMENSION, p = configuration_[i] % DIMENSION;
			displacement += (std::abs(r-o) + std::abs(c-p));
		}
	}
	return displacement;
}


void Board::test_case() {
	configuration_[0] = 1;
	configuration_[1] = 2;
	configuration_[2] = 4;
	configuration_[3] = 0;
	configuration_[4] = 5;
	configuration_[5] = 6;
	configuration_[6] = 8;
	configuration_[7] = 3;
	configuration_[8] = 7;
}


// this should be revised...
// lots of wasted space!
int Board::hash_key(int* config) {
	int key = 0;
	for (int i = 0; i < ELEMENTS; ++i)
		key += static_cast<int>(config[i] * std::pow(10, ELEMENTS - 1 - i));
	return key;
}



void Board::in_order() {
	for (int i = 0; i < ELEMENTS; ++i)
		configuration_[i] = i;
}


bool Board::is_solvable() {
	return true;

}


bool Board::is_complete() {
	for (int i = 0; i < ELEMENTS; ++i)
		if (configuration_[i] != i)
			return false;
	return true;
}


void Board::set_configuration(int* config) {
	for (int i = 0; i < ELEMENTS; ++i)
		configuration_[i] = config[i];
}


void Board::print() {
	for (int r = 0; r < DIMENSION; ++r) {
		for (int c = 0; c < DIMENSION; ++c) {
			std::cout << configuration_[r*DIMENSION + c] << " ";
		}
		std::cout << "\n";
	}
}





