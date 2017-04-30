#include "interface.h"
#include "data.h"


namespace {
	const int MAX_DEPTH = 24;
}


Data::Data() :
	max_depth_(0)
{}


Data::~Data() {

}


void Data::init_trial() {
	Datum datum;
	datum.elapsed_ = 0;
	datum.visited_ = datum.depth_ = 0;
	datum.time_i_ = this->get_time();
	data_.push_back(datum);
}


void Data::end_trial() {
	TimePoint time_f = this->get_time();
	std::chrono::duration<double> elapsed = 
		time_f - data_[this->last()].time_i_;
	data_[this->last()].elapsed_ = elapsed.count();

}


void Data::depth(int depth) {
	if (depth > max_depth_)
		max_depth_ = depth;
	data_[this->last()].depth_ = depth;
}


void Data::incr_visit() {
	++data_[this->last()].visited_;
}


TimePoint Data::get_time() {
	return std::chrono::system_clock::now();
}


int Data::last() {
	return data_.size()-1;
}


void Data::compile(Interface& interface) {
	
}



