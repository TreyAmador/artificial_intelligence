#ifndef  NODE_H_
#define NODE_H_
#include <iostream>


struct Node {

public:
	Node() :
		configuration_(nullptr),g_(0),h_(0),parent_(nullptr)
	{}
	Node(int* config, int g, int h, Node* parent) :
		configuration_(config),g_(g),h_(h),parent_(parent)
	{}
	~Node() {
		if (configuration_ != nullptr) {
			delete[] configuration_;
			configuration_ = nullptr;
		}
		if (parent_ != nullptr) {
			delete parent_;
			parent_ = nullptr;
		}
	}
	
	void print() {
		std::cout << "Config: ";
		for (int i = 0; i < 9; ++i)
			std::cout << configuration_[i] << " ";
		std::cout << "\n" << 
			"g(n) = " << g_ << ", " << 
			"h(n) = " << h_ << "\n" << std::endl;
	}


public:
	// the actual game board
	// hash function will match board configs to this
	int* configuration_;
	int g_, h_;
	Node* parent_;


};


#endif
