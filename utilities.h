#ifndef UTILITIES_H_
#define UTILITIES_H_
#include <vector>


namespace UTIL {


	 void swap_indeces(int* config, int a, int b) {
		int temp = config[a];
		config[a] = config[b];
		config[b] = temp;
	}


	int permutations(int elements) {
		int factorial = 1;
		for (int i = elements; i >= 2; --i)
			factorial *= i;
		return factorial;
	}


	int* copy_ptr(int* ptr, int size) {
		int* copy = new int[size];
		for (int i = 0; i < size; ++i)
			copy[i] = ptr[i];
		return copy;
	}


	void clear_ptr(int*& ptr) {
		if (ptr != nullptr) {
			delete[] ptr;
			ptr = nullptr;
		}
	}


	bool ptr_equal(int* ptr_a, int size_a, int* ptr_b, int size_b) {
		if (size_a != size_b) 
			return false;
		for (int i = 0; i < size_a; ++i)
			if (ptr_a[i] != ptr_b[i])
				return false;
		return true;
	}


	template<class T>
	void clear_vec(std::vector<T>& elements) {
		elements.clear();
		elements.shrink_to_fit();
	}

}


#endif
