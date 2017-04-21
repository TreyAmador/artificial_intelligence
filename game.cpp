#include "game.h"
#include "node.h"


namespace {
	const int ELEMENTS = 9;
	
	// need to make this vector smaller!
	const int VALUES = 123456780;
	//const int FACTORIAL = 362880;
}


Game::Game() :
	board_(Board()),
	explored_(std::vector<Node*>(VALUES))
{
	// this needs to be revised to require fewer entries
	//explored_.resize(this->permutations(),nullptr);
	//explored_.resize(values, nullptr);

	//explored_ = std::vector<Node*>(10);

	//explored_.resize(VALUES);

	std::cout << explored_.size() << std::endl;
	std::cout << "nodes initialized" << std::endl;

	// init frontier
	// it can be empty now?
	// or fill it with first config?


}


Game::~Game() {

}


// init game board here
int Game::run() {

	
	Node node_a, node_b;
	node_a.configuration_ = new int[ELEMENTS];
	for (int i = 0; i < ELEMENTS; ++i) {
		node_a.configuration_[i] = i;
	}
	//explored_[]
	int key_a = this->hash_key(node_a.configuration_);

	explored_[key_a] = new Node(node_a);

	std::cout << "node a at " << key_a << std::endl;
	explored_[key_a]->print();
	
	
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







