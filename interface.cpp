#include <iostream>
#include <sstream>
#include "interface.h"
#include "node.h"


namespace {
	const std::string WRITE_PATH = "tests/output.txt";
}

typedef std::vector<Node*>::iterator nIter;


Interface::Interface(int elems) :
	ELEMENTS(elems),
	file_writer_(WRITE_PATH)
{}


Interface::~Interface() {
	file_writer_.close();
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
	for (size_t i = 0; i < config.size(); ++i)
		configint[i] = config[i] - '0';
	return configint;
}


bool Interface::input_valid(const std::string& input) {
	std::vector<int> digits(ELEMENTS, 0);
	for (size_t i = 0; i < input.size(); ++i) {
		int d = static_cast<int>(input[i]-'0');
		if (d >= 0 && d <= 8)
			++digits[d];
	}
	for (size_t i = 0; i < digits.size(); ++i)
		if (digits[i] != 1)
			return false;
	return true;
}


int* Interface::prompt() {
	std::string input("");
	while (true) {
		std::cout << 
			"Enter a string of non-repeating digits, 0 through 8, " << 
			"or type 'exit' to quit:\n";
		std::getline(std::cin, input);
		if (this->input_valid(input))
			return this->convert(input);
		else if (this->exit_request(input))
			return nullptr;
		else
			std::cout << "\nInput not valid.\n" << std::endl;
	}
}


bool Interface::exit_request(const std::string& input) {
	return input == "exit";
}


int Interface::completed() {
	std::cout << "\n\nSimulation ended.\n\n" << std::endl;
	return 0;
}


void Interface::not_solvable() {
	std::cout <<
		"\nThis configuration is not solvable.\n" <<
		"Please try again.\n\n";
}


bool Interface::bypass_file() {
	std::cout <<
		"Enter 'y' to run statistical analysis.\n" <<
		"Otherwise, press any key to run manual input.\n";
	std::string input;
	std::cin >> input;
	if (input != "y") {
		std::cout << "\nStatistical analyses bypassed\n\n" << std::endl;
		return true;
	}
	return false;
}


void Interface::write_stats(
	const std::string& heuristic,
	std::vector<Node*>& path,
	int explored, double elapsed) 
{
	file_writer_ << 
		path.size()-1 << "," << 
		heuristic << "," <<
		explored << "," << 
		elapsed << std::endl;
	std::cout << path.size()-1 << " ";
}


void Interface::print_heuristic(
	const std::string& heuristic,
	std::vector<Node*>& path,
	int explored)
{
	std::cout << "\n" << heuristic << "\n\n";
	this->print_path(path);
	this->print_stats(path.size()-1, explored);
}


void Interface::print_stats(int depth, int explored) {
	std::cout << 
		"\nThe total depth is " << depth << "." << "\n" <<
		"A total of " << explored << 
		" nodes were visited.\n\n" << std::endl;
}


void Interface::print_path(std::vector<Node*>& path) {
	std::cout << "\nState path\n" << std::endl;
	for (nIter iter = path.begin(); iter != path.end(); ++iter)
		this->print_node(*iter);
}


void Interface::print_node(Node* node) {
	int dim = static_cast<int>(std::sqrt(ELEMENTS));
	int* config = node->configuration_;
	for (int r = 0; r < dim; ++r) {
		for (int c = 0; c < dim; ++c) {
			std::cout << config[r*dim + c] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "g(n) = " << node->g_ << ", "
		<< "h(n) = " << node->h_ << "\n\n";
}
