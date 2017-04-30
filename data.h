#ifndef DATUM_H_
#define DATUM_H_
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
class Interface;

typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;


struct Datum {
	std::string type_;
	TimePoint time_i_;
	double elapsed_;
	int visited_;
	int depth_;
};


#endif



#ifndef STATS_H_
#define STATS_H_


struct Statistics {
	std::string type_;
	int depth_;
	int samples_;
	double time_sum_;
	int visited_sum_;
};


#endif



#ifndef DATA_H_
#define DATA_H_


class Data {

public:
	Data();
	~Data();

	void init_trial();
	void incr_visit();
	void end_trial();

	void depth(int depth);
	
	void compile(Interface& interface);


private:
	TimePoint get_time();
	int last();


private:
	std::vector<Datum> data_;
	int max_depth_;


};


#endif
