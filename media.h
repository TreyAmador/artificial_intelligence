#ifndef FILEREADER_H_
#define FILEREADER_H_
#include <string>
#include <vector>


class Media {

public:
	Media();
	~Media();


	// gets configs for testing purposes
	std::vector<int*> get_configs(const std::string& filepath);
	int* convert(const std::string& filepath);
	int* prompt();


private:



};


#endif
