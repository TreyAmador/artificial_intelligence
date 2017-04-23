#include <iostream>
#include <fstream>
#include <sstream>
#include "media.h"
#include "node.h"


namespace {
	const int ELEMENTS = 9;
}


Media::Media() {

}


Media::~Media() {

}


std::vector<int*> Media::get_configs(const std::string& filepath) {
	std::string line;
	std::vector<int*> configs;
	std::ifstream input(filepath.c_str());
	while (std::getline(input, line))
		configs.push_back(this->convert(line));
	return configs;
}


int* Media::convert(const std::string& config) {
	int* configint = new int[config.size()];
	for (size_t i = 0; i < config.size(); ++i) {
		configint[i] = config[i] - '0';
	}
	return configint;
}


int* Media::prompt() {
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


void Media::output(std::vector<Node*>& path) {
	for (size_t i = 0; i < path.size(); ++i)
		path[i]->print();
}

