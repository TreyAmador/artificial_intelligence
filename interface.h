#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <string>
#include <vector>
struct Node;


class Interface {

public:
	Interface(int elems);
	~Interface();

	std::vector<int*> get_configs(const std::string& filepath);
	int* convert(const std::string& filepath);
	void output(std::vector<Node*>& path);
	int* prompt();
	bool input_valid(const std::string& input);
	void not_solvable();


private:
	const int ELEMENTS;


};


#endif
