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
	// explored_ could also be a hash map
	// need to reduce size of explored_ to permutation
	// int hash_size = this->permutations();
	//int hash_size = static_cast<int>(std::pow(10,ELEMENTS));
	//explored_ = new bool[hash_size];
	//for (int i = 0; i < hash_size; ++i) {
	//	explored_[i] = false;
	//}

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
	//if (explored_ != nullptr) {
	//	delete[] explored_;
	//	explored_ = nullptr;
	//}
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


void Board::print() {
	for (int r = 0; r < DIMENSION; ++r) {
		for (int c = 0; c < DIMENSION; ++c) {
			std::cout << configuration_[r*DIMENSION + c] << " ";
		}
		std::cout << "\n";
	}
}





