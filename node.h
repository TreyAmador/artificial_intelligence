#ifndef  NODE_H_
#define NODE_H_
#include <iostream>


struct Node {


public:
	Node(int* config, int g, int h, Node* parent, int open) :
		configuration_(config),
		g_(g),h_(h),
		parent_(parent),
		open_(open)
	{}
	~Node() {
		if (configuration_ != nullptr) {
			delete[] configuration_;
			configuration_ = nullptr;
		}
	}
	int cost() {
		return g_ + h_;
	}
	void print() {
		std::cout << "Configuration:\n";
		for (int r = 0; r < 3; ++r) {
			for (int c = 0; c < 3; ++c) {
				std::cout << configuration_[r*3+c] << " ";
			}
			std::cout << "\n";
		}
		std::cout << 
			"g(n) = " << g_ << ", " << 
			"h(n) = " << h_ << "\n" <<
			"open: " << open_ << "\n\n";
		
		std::cout << "Parent:\n";
		if (parent_ != nullptr) {
			for (int r = 0; r < 3; ++r) {
				for (int c = 0; c < 3; ++c) {
					std::cout << parent_->configuration_[r * 3 + c] << " ";
				}
				std::cout << "\n";
			}
		} else {
			std::cout << "None\n";
		}
		std::cout << "\n\n" << std::endl;
	}


public:
	// the actual game board
	// hash function will match board configs to this
	int* configuration_;
	int g_,h_;
	Node* parent_;
	int open_;


};


#endif
