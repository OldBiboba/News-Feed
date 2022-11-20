#include "Content.h"

Content::Content() : author{ "Default User" }, data{"Default content string"} {
	date = time(NULL);
}

Content::Content(const char* new_data) : data{ new_data }, author{ "Default User" } {
	date = time(NULL);
}

Content::Content(const Content& c) : data{ c.data }, author{ c.author } {
	date = time(NULL);
}

Content::~Content() {}

const char* Content::get_data() const {
	return data.get_string();
}

void Content::set_data(const char* new_data) {
	data.set_str(new_data);
}

const char* Content::get_author() const {
	return author.get_string();
}

time_t Content::get_date() const {
	return date;
}

const char* Content::get_type() {
	return "Text";
}

void Content::operator=(const Content& another) {
	data.set_str(another.get_data());
	author.set_str(another.get_author());
	date = another.get_date();
}
