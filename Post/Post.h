#pragma once
#include "../Content/Content.h"
#include "../Array/Array.h"

int likes_cmp(const void* a, const void* b);

int date_cmp(const void* a, const void* b);

class Post {
public:
	Post();
	Post(const char* author);
	Post(const Post& another);
	virtual ~Post();

	virtual Post* clone() const = 0;

	//Работа с массивом содержимого

	void add_content(const Content& new_content);
	void remove_content(int idx);
	void change_content(int idx, const char* new_data);
	int get_content_count() const;
	const Content& get_content_by_idx(int idx) const;


	//Работа с количеством лайков
	void add_like();
	void remove_like();
	int get_likes_count() const;


	//Работа с метаданными

	char* get_author() const;
	time_t get_date() const;


	//Получить пост в виде строки
	virtual void get_post(String& buffer) const;

	void operator = (const Post& another);

	virtual const char* get_type() const;

	void operator+=(const Content& content);

	void operator--(int);
	void operator++(int);

	operator char* ();


protected:
	Array<Content> content_array;

	String author;
	time_t date;

	int likes_count;

};




class User_Post : public Post {
public:
	User_Post();
	User_Post(const char* author);
	User_Post(const User_Post& another);
	~User_Post() override;

	Post* clone() const override;

	void get_post(String& buffer) const override;


	//Работа с комментариями

	void add_comment(const char* comment);
	void add_comment(const String& comment);
	int get_comment_count() const;
	char* get_comment(int idx) const;


	const char* get_type() const override;

	User_Post operator+(const Content& content);
	User_Post operator+(const User_Post& another);

	friend ostream& operator<<(ostream& out, const User_Post& c);

protected:
	Array<String> comments;

};



class Sponsored_Post : public Post {
public:
	Sponsored_Post();
	Sponsored_Post(const char* author, const char* sponsor_link);
	Sponsored_Post(const Sponsored_Post& another);
	~Sponsored_Post() override;

	Post* clone() const override;

	void get_post(String& buffer) const override;


	char* get_sponsor_link() const;
	void set_sponsor_link(const char* sponsor_link);


	const char* get_type() const override;

	Sponsored_Post operator+(const Content& content);
	Sponsored_Post operator+(const Sponsored_Post& another);

	friend ostream& operator<<(ostream& out, const Sponsored_Post& c);

protected:
	String sponsor_link;

};