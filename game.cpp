#include "game.h"
#include "node.h"
#include "filemanager.h"


namespace {
	const int ELEMENTS = 9;
	const int DIMENSION = static_cast<int>(std::sqrt(ELEMENTS));
}

Game::Game() {

}


Game::~Game() {

}


// init game board here
int Game::run() {

	FileManager manager;
	std::vector<int*> configs = manager.get_configs("tests/configs.txt");
	std::vector<int*>::iterator iter = configs.begin();
	
	// continues until user input complete
	while (iter != configs.end()) {

		int* config = *iter;
		frontier_.push(new Node(
			config, 0,
			this->manhattan_heuristic(config),
			nullptr,
			this->open_slot(config)));

		frontier_.top()->print();

		// while goal not reached ...
		for (int i = 0; i < 3; ++i)
			this->move();

		// move up tree to trace path


		this->reset();

		++iter;
	}

	return 0;
}


// pass heuristic function in this method?
void Game::move() {

	Node* node = frontier_.top();
	frontier_.pop();

	int row = node->open_/DIMENSION,
		col = node->open_%DIMENSION;

	if (this->top_open(row)) {
		this->move(node, DOWN);
	}
	if (this->bottom_open(row)) {
		this->move(node, UP);
	}
	if (this->right_open(col)) {
		this->move(node, LEFT);
	}
	if (this->left_open(col)) {
		this->move(node, RIGHT);
	}
	
	int key = this->hash_key(node->configuration_);
	this->explored_[key] = node;
	
}


bool Game::top_open(int row) {
	return row < DIMENSION-1;
}


bool Game::bottom_open(int row) {
	return row > 0;
}


bool Game::left_open(int col) {
	return col < DIMENSION - 1;
}


bool Game::right_open(int col) {
	return col > 0;
}


void Game::move(Node* node, int dir) {

	int* config = this->copy_config(node->configuration_);	
	int open = node->open_;
	this->swap_indeces(config, open, open+dir);

	// if config in explored then return
	int key = this->hash_key(config);
	if (explored_.count(key))
		return;

	Node* child = new Node(
		config,
		node->g_ + 1,
		this->manhattan_heuristic(config),
		node,
		open+dir);

	child->print();

	frontier_.push(child);

}


void Game::swap_indeces(int* config, int a, int b) {
	int temp = config[a];
	config[a] = config[b];
	config[b] = temp;
}


int Game::open_slot(int* config) {
	for (int i = 0; i < ELEMENTS; ++i)
		if (config[i] == 0)
			return i;
	return -1;
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


int* Game::copy_config(int* config) {
	int* copy = new int[ELEMENTS];
	for (int i = 0; i < ELEMENTS; ++i)
		copy[i] = config[i];
	return copy;
}


bool Game::in_explored(Node* node) {
	return node != nullptr;
}


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


bool Game::complete() {



}


