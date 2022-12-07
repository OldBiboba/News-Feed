//#define __CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_NEW


#include <iostream>
#include <Windows.h>
#include "Feed/Feed.h"

using namespace std;

void feed_test() {
	cout << "Posts generating..." << endl;
	Text_Content tc1;
	Text_Content tc2("test content string", "User1");
	Text_Content tc3(tc2);

	Image_Content ic1;
	Image_Content ic2("  *  \n *** \n*****", "Apple Iphone 8", 1, "User2");
	Image_Content ic3(ic2);


	User_Post p1("User1");
	p1.add_content(tc1);
	p1.add_content(tc2);
	p1.add_content(tc3);
	p1.add_like();
	p1.add_comment("ahahahahah");


	Sleep(1000);
	User_Post p2(p1);
	p2.add_like();
	p2.add_like();
	p2.add_like();
	p2.add_like();
	p2.add_comment("one more comment");


	Sleep(1000);
	User_Post p3;
	p3.add_content(ic1);
	p3.add_like();
	p3.add_like();
	p3.add_comment("nice star!");

	Sleep(1000);
	Sponsored_Post p4("User2", "www.google.com");
	p4.add_content(ic2);

	Sleep(1000);
	Sponsored_Post p5(p4);
	p5.add_content(tc2);
	p4.set_sponsor_link("www.yandex.ru");
	p5.add_like();
	p5.add_like();
	p5.add_like();
	p5.add_like();

	Sleep(1000);
	Sponsored_Post p6;
	p6.add_content(ic1);


	Admin_Feed fd;
	fd.add_post(p1);
	fd.add_post(p2);
	fd.add_post(p3);
	fd.add_post(p4);
	fd.add_post(p5);
	fd.add_post(p6);
	
	system("cls");

	fd.user_interface();
}

int main() {
	srand(time(NULL));

	feed_test();

	
	//_CrtDumpMemoryLeaks();
	return 0;
}