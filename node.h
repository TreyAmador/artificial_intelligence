#ifndef  NODE_H_
#define NODE_H_


struct Node {

public:
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


public:
	// the actual game board
	// hash function will match board configs to this
	int* configuration_;
	int g_, h_;
	Node* parent_;


};


#endif
