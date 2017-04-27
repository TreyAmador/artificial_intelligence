/*
	main game
*/

#include <time.h>

#include "utilities.h"
#include "interface.h"
#include "game.h"
#include "node.h"


namespace {
	const int ELEMENTS = 9;
	const int DIMENSION = static_cast<int>(std::sqrt(ELEMENTS));
}


Game::Game() {

}


Game::~Game() {

}


// pass heuristic function in this method?
void Game::select_move() {

	Node* node = frontier_.top();
	frontier_.pop();
	int row = node->open_/DIMENSION,
		col = node->open_%DIMENSION;

	if (this->top_open(row))
		this->move(node, DOWN);
	if (this->bottom_open(row))
		this->move(node, UP);
	if (this->right_open(col))
		this->move(node, LEFT);
	if (this->left_open(col))
		this->move(node, RIGHT);
	
	int key = this->hash_key(node->configuration_);
	this->explored_[key] = node;
}


// pass calculate heuristic function
void Game::move(Node* node, int dir) {

	int* config = UTIL::copy_ptr(node->configuration_, ELEMENTS);
	int open = node->open_;
	UTIL::swap_indeces(config, open, open + dir);
	
	int key = this->hash_key(config);
	if (explored_.count(key))
		return;
	
	this->add_node(config, node->g_+1,
		this->manhattan_heuristic(config),
		node, open+dir);
}


void Game::solve_heuristic(int* config, int (Game::*heuristic)(int*)) {
	std::cout << "in the solve heuristic fxn" << std::endl;
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
			int r = i / DIMENSION, c = i % DIMENSION;
			int o = config[i] / DIMENSION, p = config[i] % DIMENSION;
			displacement += (std::abs(r - o) + std::abs(c - p));
		}
	}
	return displacement;
}


int Game::open_slot(int* config) {
	for (int i = 0; i < ELEMENTS; ++i)
		if (config[i] == 0)
			return i;
	return -1;
}


// this should be revised...
// you won't use a map in final version
int Game::hash_key(int* config) {
	int key = 0;
	for (int i = 0; i < ELEMENTS; ++i)
		key += static_cast<int>(config[i] * std::pow(10, ELEMENTS - 1 - i));
	return key;
}


// perhaps copy config here rather than in move?
void Game::add_node(
	int* config,
	int cost, 
	int heuristic,
	Node* parent,
	int open)
{
	frontier_.push(new Node(
		config, 
		cost,
		heuristic,
		parent,
		open
	));
}


inline bool Game::top_open(int row) {
	return row < DIMENSION - 1;
}


inline bool Game::bottom_open(int row) {
	return row > 0;
}


inline bool Game::left_open(int col) {
	return col < DIMENSION - 1;
}


inline bool Game::right_open(int col) {
	return col > 0;
}


bool Game::is_solvable(int* config) {
	int inversions = 0;
	for (int i = 0; i < ELEMENTS; ++i)
		if (config[i] != 0)
			for (int j = i + 1; j < ELEMENTS; ++j)
				if (config[i] > config[j] && config[j] != 0)
					++inversions;
	std::cout << "The number of inversions is " << inversions << std::endl;
	return inversions % 2 == 0;
}


inline bool Game::is_complete() {
	return frontier_.top()->h_ == 0;
}


inline bool Game::exit_requested(int* config) {
	return config == nullptr;
}


std::vector<Node*> Game::path(Node* init) {
	Node* node = init;
	std::vector<Node*> path;
	while (node != nullptr) {
		path.insert(path.begin(), node);
		node = node->parent_;
	}
	return path;
}


void Game::reset() {
	this->clear_frontier();
	this->clear_explored();
}


void Game::clear_frontier() {
	while (!frontier_.empty()) {
		Node* elem = frontier_.top();
		if (elem != nullptr) {
			delete elem;
			elem = nullptr;
		}
		frontier_.pop();
	}
}


void Game::clear_explored() {
	for (auto iter = explored_.begin(); iter != explored_.end(); ++iter) {
		auto value = iter->second;
		if (value != nullptr) {
			delete value;
			value = nullptr;
		}
	}
}


/*

// init game board here
int Game::run() {

	Interface interface(ELEMENTS);
	std::vector<int*> configs = interface.get_configs("tests/configs.txt");
	std::vector<int*>::iterator iter = configs.begin();

	//int* config = *iter;

	//this->solve_heuristic(
	//	UTIL::copy_ptr(config,ELEMENTS),
	//	&Game::manhattan_heuristic);

	while (iter != configs.end()) {
		int* config = *iter;

		// manhattan_solve(config, function)
		// misplaced_solve(config, function)

		if (this->is_solvable(config)) {
			this->add_node(config, 0,
				this->manhattan_heuristic(config),
				nullptr, this->open_slot(config));
			while (!this->is_complete())
				this->select_move();
			interface.print_path(this->path(frontier_.top()));
			this->reset();
		} else {
			interface.not_solvable();
		}

		++iter;

	}

	return 0;
}

*/



// init game board here
int Game::run() {
	Interface interface(ELEMENTS);
	while (true) {
		int* config = interface.prompt();
		if (this->exit_requested(config))
			return interface.completed();
		if (this->is_solvable(config)) {
			this->add_node(config, 0, 
				this->manhattan_heuristic(config), 
				nullptr, this->open_slot(config));
			while (!this->is_complete())
				this->select_move();
			interface.print_path(this->path(frontier_.top()));
			this->reset();
		} else {
			interface.not_solvable();
		}
	}
	return 0;
}

