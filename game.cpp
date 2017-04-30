/*
	main game
*/
#include <iostream>
#include <time.h>
#include "utilities.h"
#include "interface.h"
#include "game.h"
#include "node.h"


namespace {
	const int ELEMENTS = 9;
	const int DIMENSION = static_cast<int>(std::sqrt(ELEMENTS));
	//const std::string SAMPLES = "tests/200 Scrambled Puzzles.txt";
	const std::string SAMPLES = "tests/depth20.txt";

}


Game::Game() {
	this->reset_edge();
}


Game::~Game() {
	this->reset(nullptr);
}


int Game::run() {
	Interface interface(ELEMENTS);
	this->samples(SAMPLES, interface);
	//return this->input(interface);
	return 0;
}


void Game::samples(const std::string& filepath, Interface& interface) {
	if (!interface.bypass_file()) {
		std::vector<int*> configs = interface.get_configs(filepath);
		for (size_t i = 0; i < configs.size(); ++i) {
			if (this->is_solvable(configs[i])) {
				this->solve(configs[i], interface);
			} else {
				interface.not_solvable();
			}
		}
	}
}


int Game::input(Interface& interface) {
	while (true) {
		int* config = interface.prompt();
		if (this->exit_requested(config))
			return interface.completed();
		else if (this->is_solvable(config))
			this->solve(config, interface);
		else
			interface.not_solvable();
		this->reset(config);
	}
	return 0;
}


void Game::solve(int* config, Interface& interface) {
	this->solve_heuristic(
		config,&Game::manhattan_heuristic,
		"Manhattan Heuristic",interface);
	this->solve_heuristic(
		config,&Game::misplaced_heuristic,
		"Misplaced Heuristic",interface);
}


void Game::solve_heuristic(
	int* config, int(Game::*heuristic)(int*), 
	const std::string& type, Interface& interface)
{
	int* configuration = UTIL::copy_ptr(config, ELEMENTS);
	this->reset_edge();
	this->add_node(configuration, 0,
		(this->*heuristic)(configuration),
		nullptr, this->open_slot(configuration));
	while (!this->is_complete())
		this->select_move(heuristic);
	std::vector<Node*> path = this->create_path(frontier_.top());
	interface.print_heuristic(type,path, frontier_.size(), explored_.size());
	interface.print_heuristic(type, path, edge_, 0);
	this->reset(nullptr);
	UTIL::clear_vec(path);
}


// pass calculate heuristic function
void Game::move(Node* node, int(Game::*heuristic)(int*), int dir) {

	int* config = UTIL::copy_ptr(node->configuration_, ELEMENTS);
	int open = node->open_;
	UTIL::swap_indeces(config, open, open + dir);

	int key = this->hash_key(config);
	if (explored_.count(key))
		return;

	this->add_node(config, node->g_ + 1,
		(this->*heuristic)(config),
		node, open + dir);
}


// pass heuristic function in this method?
void Game::select_move(int(Game::*heuristic)(int*)) {

	Node* node = frontier_.top();
	frontier_.pop();
	int row = node->open_/DIMENSION,
		col = node->open_%DIMENSION;

	if (this->top_open(row))
		this->move(node, heuristic, DOWN);
	if (this->bottom_open(row))
		this->move(node, heuristic, UP);
	if (this->right_open(col))
		this->move(node, heuristic, LEFT);
	if (this->left_open(col))
		this->move(node, heuristic, RIGHT);
	
	int key = this->hash_key(node->configuration_);
	this->explored_[key] = node;
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
	++edge_;
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
	return inversions % 2 == 0;
}


inline bool Game::is_complete() {
	return frontier_.top()->h_ == 0;
}


inline bool Game::exit_requested(int* config) {
	return config == nullptr;
}


std::vector<Node*> Game::create_path(Node* init) {
	Node* node = init;
	std::vector<Node*> path;
	while (node != nullptr) {
		path.insert(path.begin(), node);
		node = node->parent_;
	}
	return path;
}


void Game::reset(int* config) {
	this->clear_frontier();
	this->clear_explored();
	UTIL::clear_ptr(config);
	this->reset_edge();
}


void Game::reset_edge() {
	edge_ = 0;
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
		if (iter->second != nullptr) {
			delete iter->second;
			iter->second = nullptr;
		}
	}
	explored_.clear();
}

