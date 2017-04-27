#include <iostream>
#include <fstream>
#include <sstream>
#include "interface.h"
#include "node.h"
typedef std::vector<Node*>::iterator nIter;


namespace {
	const std::string PROMPT = "Enter a string of non-repeating digits, 0 through 8: ";
	const std::string INVALID_INPUT = "Input not valid.";
	const std::string EXIT_COMMAND = "exit";
}


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
	std::vector<int> digits(ELEMENTS, 0);
	for (size_t i = 0; i < input.size(); ++i) {
		int d = static_cast<int>(input[i]-'0');
		if (d >= 0 && d <= 8) {
			++digits[d];
		}
	}
	for (size_t i = 0; i < digits.size(); ++i)
		if (digits[i] != 1)
			return false;
	return true;
}


int* Interface::prompt() {
	std::string input("");
	do {
		std::cout << PROMPT;
		std::getline(std::cin, input);
		if (this->input_valid(input))
			return this->convert(input);
		else if (this->exit_request(input))
			return nullptr;
		else
			std::cout << INVALID_INPUT << std::endl;
	} while (true);
	return nullptr;
}


bool Interface::exit_request(const std::string& input) {
	return input == EXIT_COMMAND;
}


int Interface::completed() {
	std::cout << "Simulation ended." << std::endl;
	return 0;
}


void Interface::not_solvable() {
	std::cout <<
		"This configuration is not solvable.\n" <<
		"Please try again:\n";
}


void Interface::print_node(Node* node) {
	int dim = static_cast<int>(std::sqrt(ELEMENTS));
	int* config = node->configuration_;
	for (int r = 0; r < dim; ++r) {
		for (int c = 0; c < dim; ++c) {
			std::cout << config[r*dim+c] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "g(n) = " << node->g_ << ", "
		<< "h(n) = " << node->h_ << "\n\n";
}


void Interface::print_path(std::vector<Node*>& path) {
	std::cout << "State path\n" << std::endl;
	for (nIter iter = path.begin(); iter != path.end(); ++iter)
		this->print_node(*iter);
}

