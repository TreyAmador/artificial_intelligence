#ifndef DATA_H_
#define DATA_H_
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
class Interface;

typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;


class Data {

public:
	Data();
	~Data();

	void init_trial();
	double elapsed_time();


private:
	TimePoint get_time();


private:
	TimePoint initial_;


};


#endif
