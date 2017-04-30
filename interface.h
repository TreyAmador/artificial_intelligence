#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
struct Node;


class Interface {

public:
	Interface(int elems);
	~Interface();

	std::vector<int*> get_configs(const std::string& filepath);
	int* convert(const std::string& filepath);

	int* prompt();
	bool exit_request(const std::string& input);
	int completed();

	void not_solvable();
	bool input_valid(const std::string& input);
	bool bypass_file();
	
	void write_stats(
		const std::string& heuristic,
		std::vector<Node*>& path,
		int explored, double elapsed);
	void print_heuristic(
		const std::string& heuristic,
		std::vector<Node*>& path,
		int explored);
	void print_stats(int depth, int explored);
	void print_path(std::vector<Node*>& path);
	void print_node(Node* node);


private:
	std::ofstream file_writer_;
	const int ELEMENTS;

};


#endif
