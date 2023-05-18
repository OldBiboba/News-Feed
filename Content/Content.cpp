#include "Content.h"
#include <exception>
#include <stdexcept>

Content::Content() : author{ "Default User" } {
	date = time(NULL);
}

Content::Content(const char* new_author) : author{ new_author } {
	date = time(NULL);
}

Content::Content(const Content& c) : author{ c.author } {
	date = c.get_date();
}

Content::~Content() {}


char* Content::get_author()const {
	return author.get_string();
}

time_t Content::get_date() const {
	return date;
}

const char* Content::get_type() {
	return "Basic Content";
}

void Content::operator=(const Content& another) {
	author = another.author;
	date = another.get_date();
	char* tmp = another.get_data();
	set_data(tmp);
	delete[]tmp;
}

Content::operator char* (){
	return get_data();
}

istream& Content::set(istream& in){
	in >> author;
	in >> date;
	return in;
}

void Content::save(ofstream& fout){
	if (!fout.is_open()) {
		return;
	}

	author.save(fout);
	fout.write((char*)&date, sizeof(time_t));
}


Text_Content::Text_Content() : Content(), data{ "Default content string" } {}

Text_Content::Text_Content(const char* new_text, const char* new_author) : Content(new_author), data{ new_text } {}

Text_Content::Text_Content(const Text_Content& c) : Content(c), data{ c.data } {}

Text_Content::~Text_Content() {}

char* Text_Content::get_data() const{
	return data.get_string();
}

void Text_Content::set_data(const char* new_data){
	try {
		data.set_str(new_data);
	}
	catch (const std::invalid_argument& ex) {}
}

Text_Content* Text_Content::clone ()const{
	Text_Content* result = new Text_Content(*this);
	return result;
}

void Text_Content::operator=(const Text_Content& another){
	Content::operator=(another);
}

const Text_Content Text_Content::operator+(const Text_Content& another){
	Text_Content result(*this);
	result.data.add_str(another.data);
	return result;
}

const Text_Content Text_Content::operator+(const char* str){
	Text_Content result(*this);
	result.data.add_str(str);
	return result;
}

ostream& Text_Content::get(ostream& out) const{
	out << "Text_Content(\n\"" << data << "\",\n" << author << ", " << date << ")";
	return out;
}

istream& Text_Content::set(istream& in){
	Content::set(in);
	in >> data;
	return in;
}

void Text_Content::save(ofstream& fout){
	Content::save(fout);
	char type = 1;
	fout.write(&type, sizeof(char));
	data.save(fout);
}

const char* Text_Content::get_type(){
	return "Text Content";
}

ostream& operator<<(ostream& out, const Content& c){
	return c.get(out);
}

istream& operator>>(istream& in, Content& c){
	return c.set(in);
}






Image_Content::Image_Content():Content(),picture{"  *  \n*****\n * * "},device_name{"Unknown device"}{
	color_depth = 1;
}

Image_Content::Image_Content(const char* new_picture, const char* new_device_name, int new_color_depth, const char* new_author):
	Content(new_author),picture{new_picture},device_name{new_device_name}{
	color_depth = new_color_depth;
}

Image_Content::Image_Content(const Image_Content& c):Content(c),picture{c.picture},device_name{c.device_name}{
	color_depth = c.get_color_depth();
}

Image_Content::~Image_Content() {}

char* Image_Content::get_data() const{
	return picture.get_string();
}

void Image_Content::set_data(const char* new_data){
	try {
		picture.set_str(new_data);
	}
	catch (const std::invalid_argument& ex) {}
}

Image_Content* Image_Content::clone() const{
		Image_Content* result = new Image_Content(*this);
		return result;
}

const char* Image_Content::get_type(){
	return "Image Content";
}

char* Image_Content::get_device_name() const{
	return device_name.get_string();
}

int Image_Content::get_color_depth() const{
	return color_depth;
}

void Image_Content::operator=(const Image_Content& another){
	Content::operator=(another);
	device_name = another.device_name;
	color_depth = another.get_color_depth();
}

Image_Content Image_Content::operator+(const Image_Content& another) {
	Image_Content result(*this);
	result.picture.add_str(another.picture);
	return result;
}

Image_Content Image_Content::operator+(const char* str) {
	Image_Content result(*this);
	result.picture.add_str(str);
	return result;
}

ostream& Image_Content::get(ostream& out) const{
	out << "Image_Content(\"\n" << picture << "\",\n" << author << ", " << date << ", "
		<< device_name << ", " << color_depth << ")";
	return out;
}

istream& Image_Content::set(istream& in){
	Content::set(in);
	in >> picture;
	in >> device_name;
	in >> color_depth;
	return in;
}

void Image_Content::save(ofstream& fout){
	Content::save(fout);
	char type = 2;
	fout.write(&type, sizeof(char));
	picture.save(fout);
	device_name.save(fout);
	fout.write((char*)&color_depth, sizeof(int));
}






Content* load_Content(ifstream& fin){
	if (!fin.is_open()) {
		return nullptr;
	}

	String author;
	author.load(fin);

	time_t date;
	fin.read((char*)&date, sizeof(time_t));

	char type;
	fin.read(&type, sizeof(char));

	if (type == 1) {
		Text_Content* result = new Text_Content;

		result->data.load(fin);
		result->author = author;
		result->date = date;

		return result;
	}
	else if (type == 2) {
		Image_Content* result = new Image_Content;

		result->picture.load(fin);
		result->device_name.load(fin);
		fin.read((char*)&(result->color_depth), sizeof(int));
		result->author = author;
		result->date = date;

		return result;
	}

	return nullptr;
		
}