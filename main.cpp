#include <iostream>
#include <Windows.h>
#include "Feed/Feed.h"

using namespace std;

void feed_test() {
	cout << "Posts generating..." << endl;
	Content c1;
	Content c2("test content string");
	Content c3(c2);

	Content c4("this is content 4");
	Content c5("this is content 5");


	Post p1("Custom User1");
	p1.add_content(c1);
	p1.add_content(c2);
	p1.add_content(c3);
	p1.add_like();
	p1.add_comment("ahahahahah");

	Sleep(1000);
	Post p2(p1);
	p2.add_like();
	p2.add_like();
	p2.add_like();
	p2.add_like();
	p2.add_comment("one more comment");

	Sleep(1000);
	Post p3;
	p3.add_content(c4);
	p3.add_like();
	p3.add_like();
	p3.add_comment("comment for post 3");

	Sleep(1000);
	Post p4("Custom User2");
	p4.add_content(c5);

	Sleep(1000);
	Post p5(p4);
	p5.add_comment("comment for post 5");
	p5.add_like();
	p5.add_like();
	p5.add_like();
	p5.add_like();


	Feed fd;
	fd.add_post(p1);
	fd.add_post(p2);
	fd.add_post(p3);
	fd.add_post(p4);
	fd.add_post(p5);

	system("cls");

	fd.user_intrface();
}

int main() {
	srand(time(NULL));

	feed_test();
	
	return 0;
}