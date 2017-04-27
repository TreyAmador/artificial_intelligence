#ifndef NODE_H_
#define NODE_H_
#include <iostream>


struct Node {

public:
	Node(int* config, int g, int h, Node* parent, int open) :
		configuration_(config),g_(g),h_(h),
		parent_(parent),open_(open)
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

public:
	int* configuration_;
	int g_,h_;
	Node* parent_;
	int open_;

};


#endif
