#pragma once

#include <ostream>

using namespace std;

class String {
public:
	String();
	String(const char* str);
	String(const String& s);
	~String();

	String* clone() const;

	int get_length() const;
	char* get_string() const;
	
	void set_str(const char* str);
	void add_str(const char* str); 
	void add_str(const String& str);
	void add_str(int num);

	void operator = (const String& str);

	friend ostream& operator << (ostream& out, const String& s);

private:
	char* data;
	int length;

	int str_length(const char* str);

	void copy_str(char* dest, const char* str, int size) const;
};