#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include "Post.h"
#include <stdexcept>
#include <exception>

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
		char* temp = nullptr;
		try {
			temp = (char*)content_array.get_element(i);
			buffer.add_str(temp);
			buffer.add_str("\n");
		}
		catch (const exception& ex) {}
		delete[] temp;
	}

	try {
		buffer.add_str("-\nAuthor: ");
		buffer.add_str(author);
	}
	catch (const exception& ex) {}

	try {
		buffer.add_str("\nLikes: ");
		buffer.add_str(likes_count);
	}
	catch (const exception& ex) {}

	try {
		buffer.add_str("\nDate published: ");
		char time[20];
		strftime(time, 20, "%T %d %h %y", localtime(&date));
		buffer.add_str(time);
	}
	catch (const exception& ex) {}
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



void Post::operator--(int) {
	remove_like();
}

void Post::operator++(int) {
	add_like();
}

Post::operator char* () {
	String s_post;
	get_post(s_post);
	return s_post.get_string();
}

istream& Post::set(istream& in){
	in >> author;
	in >> date;
	in >> likes_count;
	return in;
}

void Post::save(ofstream& fout){
	if (!fout.is_open()) {
		return;
	}
	
	int content_count = content_array.get_count();
	fout.write((char*)&content_count, sizeof(int));

	for (int i = 0; i < content_count; i++) {
		content_array.get_element(i).save(fout);
	}

	author.save(fout);
	fout.write((char*)&date, sizeof(time_t));
	fout.write((char*)&likes_count, sizeof(int));
}

void Post::operator+=(const Content& content) {
	add_content(content);
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
		try {
			buffer.add_str(comments.get_element(i));
			buffer.add_str("\n");
		}
		catch (const std::exception& ex) {}
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


User_Post User_Post::operator+(const Content& content) {
	User_Post result(*this);
	result += content;
	return result;
}

User_Post User_Post::operator+(const User_Post& another) {
	User_Post result(*this);
	for (int i = 0; i < another.content_array.get_count(); i++) {
		result += another.get_content_by_idx(i);
	}
	return result;
}

void User_Post::save(ofstream& fout){
	if (!fout.is_open()) {
		return;
	}
	
	char type = 1;
	fout.write(&type, sizeof(char));

	int comments_count = comments.get_count();
	fout.write((char*)&comments_count, sizeof(int));

	for (int i = 0; i < comments_count; i++) {
		comments.get_element(i).save(fout);
	}

	Post::save(fout);
}

istream& operator>>(istream& in, Post& c){
	return c.set(in);
}


ostream& operator<<(ostream& out, const User_Post& c){
	out << "User_Post{" << endl << endl;
	for (int i = 0; i < c.content_array.get_count(); i++) {
		out << c.get_content_by_idx(i) << ",\n\n";
	}
	out << c.author << ", " << c.date << ", " << c.likes_count << ",\n";
	for (int i = 0; i < c.comments.get_count(); i++) {
		out << "\"" << c.get_comment(i) << "\"" << ",\n";
	}
	out << "}";
	return out;
}


// Sponsored Post //

Sponsored_Post::Sponsored_Post() :Post(), sponsor_link{ "www.example.com" } {}

Sponsored_Post::Sponsored_Post(const char* author, const char* new_sponsor_link) :
	Post(author), sponsor_link{ new_sponsor_link } {}

Sponsored_Post::Sponsored_Post(const Sponsored_Post& another) :
	Post(another), sponsor_link(another.sponsor_link) {}

Sponsored_Post::~Sponsored_Post() {}

Post* Sponsored_Post::clone() const {
	Sponsored_Post* result = new Sponsored_Post(*this);
	return result;
}

void Sponsored_Post::get_post(String& buffer) const {
	Post::get_post(buffer);
	try {
		buffer.add_str("\n-\nSponsor link: ");
		buffer.add_str(sponsor_link);
		buffer.add_str("\n");
	}
	catch (const std::exception& ex) {}
}

char* Sponsored_Post::get_sponsor_link() const {
	return sponsor_link.get_string();
}

void Sponsored_Post::set_sponsor_link(const char* new_sponsor_link) {
	try {
		sponsor_link.set_str(new_sponsor_link);
	}
	catch (const std::invalid_argument& ex) {}
}

const char* Sponsored_Post::get_type() const {
	return "Sponsored Post";
}


Sponsored_Post Sponsored_Post::operator+(const Content& content) {
	Sponsored_Post result(*this);
	result += content;
	return result;
}

Sponsored_Post Sponsored_Post::operator+(const Sponsored_Post& another) {
	Sponsored_Post result(*this);
	for (int i = 0; i < another.content_array.get_count(); i++) {
		result += another.get_content_by_idx(i);
	}
	return result;
}

istream& Sponsored_Post::set(istream& in){
	Post::set(in);
	in >> sponsor_link;
	return in;
}

void Sponsored_Post::save(ofstream& fout){
	if (!fout.is_open()) {
		return;
	}

	char type = 2;
	fout.write(&type, sizeof(char));

	sponsor_link.save(fout);
	
	Post::save(fout);
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

ostream& operator<<(ostream& out, const Sponsored_Post& c){
	out << "Sponsored_Post{" << endl << endl;
	for (int i = 0; i < c.content_array.get_count(); i++) {
		out << c.get_content_by_idx(i) << ",\n\n";
	}
	out << c.author << ", " << c.date << ", " << c.likes_count << ", " << c.sponsor_link << "\n";
	out << "}";
	return out;
}




Post* load_Post(ifstream& fin){
	if (!fin.is_open()) {
		return nullptr;
	}

	char type;
	fin.read(&type, sizeof(char));

	Post* result = nullptr;

	if (type == 1) {
		User_Post* tmp = new User_Post;

		int comments_count;
		fin.read((char*)&comments_count, sizeof(int));

		for (int i = 0; i < comments_count; i++) {
			String comment;
			comment.load(fin);
			tmp->add_comment(comment);
		}

		result = tmp;
	}
	else if (type == 2) {
		Sponsored_Post* tmp = new Sponsored_Post;

		tmp->sponsor_link.load(fin);

		result = tmp;
	}
	
	if (result == nullptr) {
		return nullptr;
	}

	int content_count;
	fin.read((char*)&content_count, sizeof(int));

	for (int i = 0; i < content_count; i++) {
		Content* content = load_Content(fin);
		if (content != nullptr) {
			result->add_content(*content);
			delete content;
		}
	}

	result->author.load(fin);
	fin.read((char*)&(result->date), sizeof(time_t));
	fin.read((char*)&(result->likes_count), sizeof(int));

	return result;
}