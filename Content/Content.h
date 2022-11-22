#pragma once
#include <ctime>
#include "../String/String.h"
using namespace std;

class Content {
public:
	Content();
	Content(const char* new_data);
	Content(const Content& c);
	~Content();

	//������ � ����������

	char* get_data() const;
	void set_data(const char* new_data);


	//������ � �����������

	char* get_author() const;
	time_t get_date() const;


	//�������� ��� �����������
	static const char* get_type();

	void operator =(const Content& another);

private:
	String data;
	String author;
	time_t date;
};