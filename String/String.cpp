#include "String.h"

String::String() {
	length = 1;
	data = new char[length];
	data[0] = '\0';
}

String::String(const char* str) {
	length = str_length(str);
	data = new char[length];
	copy_str(data, str, length);
}

String::String(const String& s) {
	length = s.get_length();
	data = new char[length];
	copy_str(data, s.get_string(), length);
}

String::~String() {
		delete[] data;
}

int String::get_length() const {
	return length;
}

const char* String::get_string() const{
	return data;
}


void String::set_str(const char* str){
	delete[] data;
	length = str_length(str);
	data = new char[length];
	copy_str(data, str, length);
}


void String::add_str(const char* str) {
	int str_len = str_length(str);
	char* temp = new char[length - 1 + str_len];
	copy_str(temp, data, length - 1);
	copy_str(temp + length - 1, str, str_len);
	delete[]data;
	data = temp;
	length += str_len - 1;
}


void String::add_str(const String& str){
	int str_len = str.get_length();
	char* temp = new char[length - 1 + str_len];
	copy_str(temp, data, length - 1);
	copy_str(temp + length - 1, str.get_string(), str_len);
	delete[] data;
	data = temp;
	length += str_len - 1;
}

void String::add_str(int num){
	int str_length = 1;
	if (num == 0) {
		str_length = 1;
	}
	else {
		str_length = 0;
		for (int num_copy = num; num_copy != 0; num_copy /= 10) {
			str_length++;
		}
	}
	char* str = new char[++str_length];
	str[--str_length] = '\0';
	do {
		str[--str_length] = num % 10 + '0';
		num /= 10;
	} 	while (num != 0);
	add_str(str);
	delete[] str;
}

void String::operator=(const String& str){
	delete[] data;
	length = str.get_length();
	data = new char[length];
	copy_str(data, str.get_string(), length);
}

int String::str_length(const char* str) {
	for (int i = 0;; i++) {
		if (str[i] == '\0')
			return i + 1;
	}
}

void String::copy_str(char* dest, const char* str, int size) {
	for (int i = 0; i < size; i++) {
		dest[i] = str[i];
	}
}
