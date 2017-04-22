#include "filemanager.h"
#include <fstream>
#include <iostream>
#include <sstream>


FileManager::FileManager() {

}


FileManager::~FileManager() {

}


std::vector<int*> FileManager::get_configs(const std::string& filepath) {
	std::string line;
	std::vector<int*> configs;
	std::ifstream input(filepath.c_str());
	while (std::getline(input, line)) {
		configs.push_back(this->convert(line));
	}
	return configs;
}


int* FileManager::convert(const std::string& config) {
	int* configint = new int[config.size()];
	for (size_t i = 0; i < config.size(); ++i) {
		configint[i] = config[i] - '0';
	}
	return configint;
}


