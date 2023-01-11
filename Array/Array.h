#pragma once
#define MIN_CAPACITY 10
#include <algorithm>
#include <exception>


template <typename T>
class Array{
public:
	Array() {
		capacity = MIN_CAPACITY;
		data = new T* [capacity];
		count = 0;
	}
	Array(int new_capacity) {
		capacity = max(MIN_CAPACITY, new_capacity);
		data = new T* [capacity];
		count = 0;
	}

	~Array() {
		for (int i = 0; i < count; i++) {
			delete data[i];
		}
		delete[] data;
	}

	int get_count() const {
		return count;
	}
	int get_capacity() const {
		return capacity;
	}


	T& get_element(int idx) const {
		return *(data[idx]);
	}


	void add_element(const T& element) {
		try {
			check_capacity();
			data[count++] = element.clone();
		}
		catch (const bad_alloc& ex) {}
	}


	void remove_element(int idx) {
		if (idx >= 0 && idx < count) {
			delete data[idx];
			for (int i = idx; i < count - 1; i++) {
				data[i] = data[i + 1];
			}
			count--;
		}
		check_capacity();
	}

	void sort(int(*cmp_func)(const void* a, const void* b)) {
		qsort(data, count, sizeof(T*), cmp_func);
	}

private:
	void expand() {
		int new_capacity = capacity *= 2;
		T** temp = new T* [new_capacity];
		copy(data, data + count - 1, temp);
		delete[] data;
		data = temp;
		capacity = new_capacity;
	}

	void reduce() {
		int new_capacity = capacity * 2 / 3;
		T** temp = new(nothrow) T* [new_capacity];
		if (temp != nullptr) {
			copy(data, data + count - 1, temp);
			delete[] data;
			data = temp;
			capacity = new_capacity;
		}
	}

	void check_capacity() {
		if (count == capacity) {
			expand();
		}
		else if (count == capacity / 3 && capacity > MIN_CAPACITY * 1.5) {
			reduce();
		}
	}


private:
	T** data;
	int count;
	int capacity;

};

