#include "game.h"
#include "node.h"


namespace {
	const int ELEMENTS = 9;
	
	// need to make this vector smaller!
	const int VALUES = 123456780;
	//const int FACTORIAL = 362880;
}


Game::Game() :
	board_(Board())
{}


Game::~Game() {

}


// init game board here
int Game::run() {

	
	int test[] = {3,1,8,7,4,5,2,6,0};

	/*
	Node node;
	node.configuration_ = new int[ELEMENTS];
	for (int i = 0; i < ELEMENTS; ++i) {
		node.configuration_[i] = test[i];
		std::cout << test[i] << " ";
	}
	std::cout << "\n\n";
	int key = this->hash_key(test);
	explored_[key] = new Node(node);

	Node* anothernode = explored_[key];
	anothernode->print();
	*/

	board_.set_configuration(test);
	board_.print();
	std::cout << board_.manhattan_heuristic() << std::endl;
	std::cout << board_.misplaced_heuristic() << std::endl;




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


Node* Game::explored(int* config) {
	return explored_[this->hash_key(config)];
}







