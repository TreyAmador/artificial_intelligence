#include "game.h"


namespace {
	const int ELEMENTS = 9;
}


Game::Game() :
	board_(Board()) {

	// init game board
	// init frontier
	// init explored





}


Game::~Game() {

}


// init game board here
int Game::run() {

	
	return 0;
}



// this should be revised...
// lots of wasted space!
int Game::hash_key(int* config) {
	int key = 0;
	for (int i = 0; i < ELEMENTS; ++i)
		key += static_cast<int>(config[i] * std::pow(10, ELEMENTS - 1 - i));
	return key;
}



int Game::permutations() {
	int factorial = 1;
	for (int i = ELEMENTS; i >= 2; --i)
		factorial *= i;
	return factorial;
}


bool Game::in_explored(Node* node) {
	return node != nullptr;
}


Node* Game::explored() {
	return explored_[this->hash_key(board_.configuration())];
}







