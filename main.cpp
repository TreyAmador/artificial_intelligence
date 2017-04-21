/*
	entry point for the program
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>
#include "game.h"



int main(int argc, char* argv[]) {
	Game game;
	return game.run();
}









/*

namespace {
	const int ELEMENTS = 9;
	const int limit = 1000000;
}


int hash(int* config) {
	unsigned long key = 0;
	for (int i = 0; i < ELEMENTS; ++i)
		key = ((key * 33) + key) + config[i];
	int shrunk_key = key % limit;
	return shrunk_key;
}


std::vector<int> permutations() {
	std::vector<int> explored;
	//explored.resize(3784180);
	explored.resize(limit);
	int digits[] = { 0,1,2,3,4,5,6,7,8 };
	int max = 0;
	do {
		int key = hash(digits);
		++explored[key];
	} while (std::next_permutation(digits,digits+ELEMENTS));
	std::cout << "after perm" << std::endl;
	return explored;
}


int main(int argc, char* argv[]) {
	//Game game;
	//return game.run();

	//int* config = new int[ELEMENTS];
	//for (int i = 0; i < ELEMENTS; ++i)
	//	config[i] = ELEMENTS-1-i;
	//
	//int key = 0;
	//for (int i = 0; i < ELEMENTS; ++i) {
	//	std::cout << config[i] << " ";
	//	key |= i << (config[i] * 4);
	//}
	//
	//std::cout << "\n" << key << std::endl;

	//int* config = new int[ELEMENTS];
	//for (int i = 0; i < ELEMENTS; ++i)
		//config[i] = i;
	//	config[i] = ELEMENTS - 1 - i;

	//int key = 0;
	//for (int i = 0; i < ELEMENTS; ++i) {
	//	std::cout << config[i] << " ";
	//	key = ((key << 1) + key) + config[i];
	//}
	//std::cout << "\n" << key << std::endl;
	



	//int single = 0, two = 0, three = 0, none = 0;
	//std::vector<int> explored = permutations();
	//for (size_t i = 0; i < explored.size(); ++i) {
	//	if (explored[i] == 1) {
	//		++single;
	//	}
	//	else if (explored[i] == 2) {
	//		++two;
	//	}
	//	else if (explored[i] == 3) {
	//		++three;
	//	}
	//	else {
	//		++none;
	//	}
	//}
	//std::cout << 
	//	"one: " << single << 
	//	", two: " << two << 
	//	", three: " << three <<
	//	", none: " << none << std::endl;
	

	//int nums[] = {8,7,6,5,4,3,2,1,0};
	//int max = hash(nums);
	//std::cout << max << std::endl;


}

*/


