#pragma once
#include "../Content/Content.h"
#include "../Array/Array.h"

int likes_cmp(const void* a, const void* b);

int date_cmp(const void* a, const void* b);

class Post {
private:
	Array<Content> content_array;

	String author;
	time_t date;

	int likes_count;

	Array<String> comments;

public:
	Post();
	Post(const char* author);
	Post(Post& another);
	~Post();


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


	//Работа с комментариями

	void add_comment(const char* comment);
	void add_comment(String& comment);
	int get_comment_count() const;
	char* get_comment(int idx) const;


	//Работа с метаданными

	char* get_author() const;
	time_t get_date() const;
	

	//Получить пост в виде строки
	void get_post(String& buffer) const;

	void operator = (const Post& another);

	static const char* get_type();
private:


};
	