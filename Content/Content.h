#pragma once
#include <ctime>
#include "../String/String.h"
using namespace std;

class Content {
public:
	Content();
	Content(const char* new_author);
	Content(const Content& c);
	virtual ~Content();

	//������ � ����������

	virtual char* get_data() const = 0;
	virtual void set_data(const char* new_data) = 0;

	virtual Content* clone() const = 0;

	//������ � �����������

	char* get_author() const;
	time_t get_date() const;


	//�������� ��� �����������
	virtual const char* get_type();

	void operator =(const Content& another);

	operator char* ();

	virtual ostream& get(ostream& out) const = 0;
	virtual istream& set(istream& in);

	friend ostream& operator<< (ostream& out, const Content& c);
	friend istream& operator>> (istream& in, Content& c);

	virtual void save(ofstream& fout);
	friend Content* load_Content(ifstream& fin);

protected:
	String author;
	time_t date;
};




class Text_Content : public Content {
public:
	Text_Content();
	Text_Content(const char* new_text, const char* new_author);
	Text_Content(const Text_Content& c);
	~Text_Content() override;

	char* get_data() const override;
	void set_data(const char* new_data) override;

	Text_Content* clone() const override;

	const char* get_type() override;

	void operator=(const Text_Content& another);

	const Text_Content operator+(const Text_Content& another);
	const Text_Content operator+(const char* str);

	ostream& get(ostream& out) const override;
	istream& set(istream& in) override;

	void save(ofstream& fout) override;
	friend Content* load_Content(ifstream& fin);

protected:
	String data;
};



class Image_Content : public Content {
public:
	Image_Content();
	Image_Content(const char* new_picture, const char* new_device_name,
		int new_color_depth, const char* new_author);
	Image_Content(const Image_Content& c);
	~Image_Content() override;

	char* get_data() const override;
	void set_data(const char* new_data) override;

	Image_Content* clone() const override;

	char* get_device_name() const;
	int get_color_depth() const;

	const char* get_type() override;

	void operator=(const Image_Content& another);

	Image_Content operator+(const Image_Content& another);
	Image_Content operator+(const char* str);

	ostream& get(ostream& out) const override;
	istream& set(istream& in) override;

	void save(ofstream& fout) override;
	friend Content* load_Content(ifstream& fin);

protected:
	String picture;

	String device_name;
	int color_depth;
};




Content* load_Content(ifstream& fin);