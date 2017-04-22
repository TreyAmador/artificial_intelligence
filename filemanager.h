#ifndef FILEREADER_H_
#define FILEREADER_H_
#include <string>
#include <vector>


class FileManager {

public:
	FileManager();
	~FileManager();


	// gets configs for testing purposes
	std::vector<int*> get_configs(const std::string& filepath);
	int* convert(const std::string& filepath);


private:



};


#endif
