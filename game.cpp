#include "game.h"
#include "node.h"
#include "filemanager.h"


namespace {
	const int ELEMENTS = 9;
	const int DIMENSION = static_cast<int>(std::sqrt(ELEMENTS));

	// need to make this vector smaller!
	//const int VALUES = 123456780;
	//const int FACTORIAL = 362880;
}

/*
Game::Game() :
	board_(Board())
{}
*/

Game::Game() {

}


Game::~Game() {

}


// init game board here
int Game::run() {

	// temporary file reader for testing purposes
	FileManager manager;
	std::vector<int*> configs = manager.get_configs("tests/configs.txt");

	// this will be replaced by user input
	std::vector<int*>::iterator iter = configs.begin();
	while (iter != configs.end()) {
		// int* config = manager.prompt();
		int* config = *iter;
		



		frontier_.push(new Node(
			config, 0,
			this->manhattan_heuristic(config),
			nullptr));

		

		


		//this->reset();





		++iter;
	}

	Node* node = nullptr;
	while (!frontier_.empty()) {
		node = frontier_.top();
		node->print();
		frontier_.pop();
	}

	/*
	Node* node = nullptr;
	do {
		node = frontier_.top();
		node->print();
		frontier_.pop();
		//node->print();
	} while (node->parent_ != nullptr);
	this->reset();
	*/




	/*
	// have a while loop prompting user
	int* config = this->prompt();
	//frontier_.push(new Node(config, 0, 0, nullptr));

	

	// solve here!

	
	*/





	return 0;
}


int* Game::prompt() {
	int* test = new int[ELEMENTS];
	test[0] = 3;
	test[1] = 1;
	test[2] = 8;
	test[3] = 7;
	test[4] = 4;
	test[5] = 5;
	test[6] = 2;
	test[7] = 6;
	test[8] = 0;
	return test;
}


/*
// this should be revised...
// lots of wasted space!
int Game::hash_key(int* config) {
	int key = 0;
	for (int i = 0; i < ELEMENTS; ++i)
		key += static_cast<int>(config[i] * std::pow(10, ELEMENTS - 1 - i));
	return key;
}
*/

int Game::permutations() {
	int factorial = 1;
	for (int i = ELEMENTS; i >= 2; --i)
		factorial *= i;
	return factorial;
}


bool Game::in_explored(Node* node) {
	return node != nullptr;
}


//Node* Game::explored(int* config) {
//	return explored_[this->hash_key(config)];
//}




int Game::misplaced_heuristic(int* config) {
	int displaced = 0;
	for (int i = 0; i < ELEMENTS; ++i)
		if (config[i] != i && config[i] != 0)
			++displaced;
	return displaced;
}


int Game::manhattan_heuristic(int* config) {
	int displacement = 0;
	for (int i = 0; i < ELEMENTS; ++i) {
		if (config[i] != 0) {
			int r = i / DIMENSION, c = i%DIMENSION;
			int o = config[i] / DIMENSION, p = config[i] % DIMENSION;
			displacement += (std::abs(r - o) + std::abs(c - p));
		}
	}
	return displacement;
}



void Game::reset() {
	while (!frontier_.empty()) {
		auto elem = frontier_.top();
		if (elem != nullptr) {
			delete elem;
			elem = nullptr;
		}
		frontier_.pop();
	}
	for (auto iter = explored_.begin(); iter != explored_.end(); ++iter) {
		auto value = iter->second;
		if (value != nullptr) {
			delete value;
			value = nullptr;
		}
	}
}


