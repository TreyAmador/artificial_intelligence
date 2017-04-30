#include "data.h"


namespace {
	const int MAX_DEPTH = 24;
}


Data::Data() {

}


Data::~Data() {

}


void Data::init_trial() {
	initial_ = this->get_time();
}


double Data::elapsed_time() {
	std::chrono::duration<double> elapsed = this->get_time() - initial_;
	return elapsed.count();
}


TimePoint Data::get_time() {
	return std::chrono::system_clock::now();
}

