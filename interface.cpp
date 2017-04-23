#include <iostream>
#include <fstream>
#include <sstream>
#include "interface.h"
#include "node.h"


Interface::Interface(int elems) :
	ELEMENTS(elems) 
{}


Interface::~Interface() {

}


std::vector<int*> Interface::get_configs(const std::string& filepath) {
	std::string line;
	std::vector<int*> configs;
	std::ifstream input(filepath.c_str());
	while (std::getline(input, line))
		configs.push_back(this->convert(line));
	return configs;
}


int* Interface::convert(const std::string& config) {
	int* configint = new int[config.size()];
	for (size_t i = 0; i < config.size(); ++i) {
		configint[i] = config[i] - '0';
	}
	return configint;
}


bool Interface::input_valid(const std::string& input) {
	if (input.size() != ELEMENTS)
		return false;
	std::vector<int> digits(ELEMENTS, 0);
	for (int i = 0; ELEMENTS; ++i) {
		int d = input[i] - '0';
		if (d <= 8 && d >= 0)
			++digits[d];
		else
			return false;
	}
	for (int i = 0; i < ELEMENTS; ++i)
		if (digits[i] != 1)
			return false;
	return true;
}


int* Interface::prompt() {

	int* config = nullptr;
	while (true) {
		std::string input;
		std::cout << "Enter a string of numbers 0 to 8\n";
		std::cin >> input;
		
		if (this->input_valid(input)) {
			std::cout << "input valid" << std::endl;
			config = this->convert(input);
		} else {
			std::cout << "input not valid" << std::endl;
		}
	}

	return config;
}


void Interface::not_solvable() {
	std::cout <<
		"This configuration is not solvable.\n" <<
		"Please try again:\n";
}


void Interface::output(std::vector<Node*>& path) {
	for (size_t i = 0; i < path.size(); ++i)
		path[i]->print();
}

