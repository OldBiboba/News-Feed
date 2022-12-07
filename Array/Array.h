#pragma once
#define MIN_CAPACITY 10
#include <algorithm>
#include "../String/String.h"
#include "../Content/Content.h"
#include "../Post/Post.h"

class Post;

template <typename T>
class Array
{
private:
	T** data;
	int count;
	int capacity;

public:
	Array() {
		capacity = MIN_CAPACITY;
		data = new T*[capacity];
		count = 0;
	}
	Array(int new_capacity) {
		capacity = max(MIN_CAPACITY, new_capacity);
		data = new T*[capacity];
		count = 0;
	}

	~Array(){
		for (int i = 0; i < count; i++) {
			delete data[i];
		}
		delete[] data;
	}

	int get_count() const{
		return count;
	}
	int get_capacity() const {
		return capacity;
	}


	T& get_element(int idx) const{
		return *(data[idx]);
	}
	


	void add_element(const String& element) {
		check_capacity();
		data[count] = new String;
		*(data[count++]) = element;
	}

	void add_element(const Post& element) {
		check_capacity();
		data[count] = new Post;
		*(data[count++]) = element;
	}

	void add_element(const Content& element) {
		check_capacity();
		data[count++] = element.clone();
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
		capacity *= 2;
		T** temp = new T*[capacity];
		copy(data, data + count - 1, temp);
		delete[] data;
		data = temp;
	}

	void reduce() {
		capacity = capacity * 2 / 3;
		T** temp = new T*[capacity];
		copy(data, data + count - 1, temp);
		delete[] data;
		data = temp;
	}

	void check_capacity() {
		if (count == capacity) {
			expand();
		}
		else if (count == capacity / 3 && capacity > MIN_CAPACITY * 1.5) {
			reduce();
		}
	}
};


