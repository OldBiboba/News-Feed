#pragma once
#include "../Post/Post.h"


class Unauthorized_Feed {
public:
	Unauthorized_Feed();
	Unauthorized_Feed(int post_count);
	Unauthorized_Feed(Unauthorized_Feed& another);
	virtual ~Unauthorized_Feed();

	//Начальный интерфейс
	virtual void user_interface();

	int get_post_count() const;

	const Post& get_post(int idx) const;

	void add_post(const Post& new_post);


protected:
	Array<Post> post_array;


	//Интерфейс просмотра постов по одному
	virtual void one_post_interface();

	//Вывод поста
	void print_post(int post_idx);


	//Сортировки постов

	void sort_by_likes();
	void sort_by_date();

	virtual const char* get_type() const;
};

class User_Feed :public Unauthorized_Feed {
public:
	User_Feed();
	User_Feed(int post_count);
	User_Feed(User_Feed& another);
	~User_Feed() override;


protected:
	void one_post_interface() override;

	const char* get_type() const override;

};

class Admin_Feed : public User_Feed {
public:
	Admin_Feed();
	Admin_Feed(int post_count);
	Admin_Feed(Admin_Feed& another);
	~Admin_Feed() override;



protected:
	void one_post_interface() override;

	const char* get_type() const override;

};