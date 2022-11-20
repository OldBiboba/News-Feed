#pragma once
#include "../Post/Post.h"
#include <iostream>
#include <locale.h>
#include "../Array/Array.h"


class Feed {
private:
	Array<Post> post_array;


public:
	Feed();
	Feed(int post_count);
	Feed(Feed& another);
	~Feed();

	//Начальный интерфейс
	void user_intrface();

	int get_post_count() const;

	const Post& get_post(int idx) const;

	void add_post(const Post& new_post);
private:


	//Интерфейс просмотра постов по одному
	void one_post_interface();

	//Вывод поста
	void print_post(int post_idx);


	//Работа с лайками

	void add_like(int idx);
	void remove_like(int idx);


	//Сортировки постов

	void sort_by_likes();
	void sort_by_date();

	static const char* get_type();
};
