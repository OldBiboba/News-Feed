#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include "Post.h"

// Basic Post //

Post::Post() : author{ "Default User" } {
	likes_count = 0;
	date = time(NULL);
}

Post::Post(const char* new_author) : author{ new_author } {
	likes_count = 0;
	date = time(NULL);
}

Post::Post(const Post& another) : 
	author{ another.author }, content_array{ another.get_content_count() }  {
	likes_count = another.get_likes_count();
	date = another.get_date();

	for (int i = 0; i < another.get_content_count(); i++) {
		content_array.add_element(another.get_content_by_idx(i));
	}
}

Post::~Post() {}


void Post::add_content(const Content& new_content) {
	content_array.add_element(new_content);
}


void Post::remove_content(int idx) {
	for (int i = idx; i < content_array.get_count(); i++) {
		content_array.remove_element(idx);
	}
}

void Post::change_content(int idx, const char* new_data) {
	content_array.get_element(idx).set_data(new_data);
}

int Post::get_content_count() const {
	return content_array.get_count();
}

const Content& Post::get_content_by_idx(int idx) const {
	return content_array.get_element(idx);
}

void Post::add_like() {
	likes_count++;
}

void Post::remove_like() {
	if (likes_count > 0) {
		likes_count--;
	}
}

int Post::get_likes_count() const {
	return likes_count;
}

char* Post::get_author() const {
	return author.get_string();
}

time_t Post::get_date() const {
	return date;
}

void Post::get_post(String& buffer) const {
	for (int i = 0; i < content_array.get_count(); i++) {
		char* temp = content_array.get_element(i).get_data();
		buffer.add_str(temp);
		delete[] temp;
		buffer.add_str("\n");
	}

	buffer.add_str("-\nAuthor: ");
	buffer.add_str(author);

	buffer.add_str("\nLikes: ");
	buffer.add_str(likes_count);
	buffer.add_str("\nDate published: ");

	char time[20];
	strftime(time, 20, "%T %d %h %y", localtime(&date));
	buffer.add_str(time);
}

void Post::operator=(const Post& another) {
	author = another.author;
	date = another.get_date();
	likes_count = another.get_likes_count();

	for (int i = 0; i < another.get_content_count(); i++) {
		add_content(another.get_content_by_idx(i));
	}

}

const char* Post::get_type() const {
	return "Basic Post";
}




// User Post //

User_Post::User_Post() :Post() {}

User_Post::User_Post(const char* author) : Post(author) {}

User_Post::User_Post(const User_Post& another) : Post(another) {
	for (int i = 0; i < another.get_comment_count(); i++) {
		add_comment(another.comments.get_element(i));
	}
}

User_Post::~User_Post() {}

Post* User_Post::clone() const {
	User_Post* result = new User_Post(*this);
	return result;
}

void User_Post::get_post(String& buffer) const {
	Post::get_post(buffer);
	buffer.add_str("\n-\nComments:\n");
	for (int i = 0; i < comments.get_count(); i++) {
		buffer.add_str(comments.get_element(i));
		buffer.add_str("\n");
	}
}

void User_Post::add_comment(const char* comment) {
	String temp(comment);
	comments.add_element(temp);
}

void User_Post::add_comment(const String& comment) {
	comments.add_element(comment);
}

int User_Post::get_comment_count() const {
	return comments.get_count();
}

char* User_Post::get_comment(int idx) const {
	if (idx >= 0 && idx < comments.get_count()) {
		return comments.get_element(idx).get_string();
	}
	return nullptr;
}

const char* User_Post::get_type() const {
	return "User Post";
}




// Sponsored Post //

Sponsored_Post::Sponsored_Post() :Post(), sponsor_link{ "www.example.com" } {}

Sponsored_Post::Sponsored_Post(const char* author, const char* new_sponsor_link) :
	Post(author), sponsor_link{ new_sponsor_link } {}

Sponsored_Post::Sponsored_Post(const Sponsored_Post& another): 
	Post(another), sponsor_link(another.sponsor_link) {}

Sponsored_Post::~Sponsored_Post() {}

Post* Sponsored_Post::clone() const{
	Sponsored_Post* result = new Sponsored_Post(*this);
	return result;
}

void Sponsored_Post::get_post(String& buffer) const{
	Post::get_post(buffer);
	buffer.add_str("\n-\nSponsor link: ");
	buffer.add_str(sponsor_link);
	buffer.add_str("\n");
}

char* Sponsored_Post::get_sponsor_link() const{
	return sponsor_link.get_string();
}

void Sponsored_Post::set_sponsor_link(const char* new_sponsor_link){
	sponsor_link.set_str(new_sponsor_link);
}

const char* Sponsored_Post::get_type() const{
	return "Sponsored Post";
}






// Comparation functions //

int likes_cmp(const void* a, const void* b) {
	const Post** first = (const Post**)a;
	const Post** second = (const Post**)b;
	if ((*first)->get_likes_count() < (*second)->get_likes_count()) {
		return 1;
	}
	else if ((*((Post*)a)).get_likes_count() == (*((Post*)b)).get_likes_count()) {
		return 0;
	}
	return -1;
}

int date_cmp(const void* a, const void* b)
{
	const Post** first = (const Post**)a;
	const Post** second = (const Post**)b;
	if ((*first)->get_date() < (*second)->get_date()) {
		return 1;
	}
	else if ((*((Post*)a)).get_date() == (*((Post*)b)).get_date()) {
		return 0;
	}
	return -1;
}
