#include "String.h"
#include <stdexcept>
#include <exception>

String::String() {
	length = 1;
	data = new char[length];
	data[0] = '\0';
}

String::String(const char* str) {
	if (str == nullptr) {
		*this = String();
	}
	else {
		length = str_length(str);
		data = new char[length];
		copy_str(data, str, length);
	}
}

String::String(const String& s) {
	length = s.get_length();
	data = s.get_string();
}

String::~String() {
	delete[] data;
}

String* String::clone() const{
	String* result = new String(*this);
	return result;
}

int String::get_length() const {
	return length;
}

char* String::get_string() const{
	char* result = new char[length];
	copy_str(result, (const char*)data, length);
	return result;
}


void String::set_str(const char* str) {
	if (str == nullptr) {
		throw std::invalid_argument("set_str: \"str\" is nullptr");
	}
	delete[] data;
	length = str_length(str);
	data = new char[length];
	copy_str(data, str, length);
}


void String::add_str(const char* str) {
	if (str == NULL) {
		throw std::invalid_argument("add_str: \"str\" is nullptr");
	}
	int str_len = str_length(str);
	char* temp = new char[length - 1 + str_len];
	copy_str(temp, data, length - 1);
	copy_str(temp + length - 1, str, str_len);
	delete[]data;
	data = temp;
	length += str_len - 1;
}


void String::add_str(const String& str) {
	int str_len = str.get_length();
	char* new_data = new char[length - 1 + str_len];
	copy_str(new_data, data, length - 1);
	char* temp = str.get_string();
	copy_str(new_data + length - 1, temp, str_len);
	delete[] temp;
	delete[] data;
	data = new_data;
	length += str_len - 1;
}

void String::add_str(int num) {
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
	} while (num != 0);
	add_str(str);
	delete[] str;
}

void String::operator=(const String& str) {
	delete[] data;
	length = str.get_length();
	data = str.get_string();
}

int String::str_length(const char* str) {
	for (int i = 0;; i++) {
		if (str[i] == '\0')
			return i + 1;
	}
}

void String::copy_str(char* dest, const char* str, int size) const{
	for (int i = 0; i < size; i++) {
		dest[i] = str[i];
	}
}
