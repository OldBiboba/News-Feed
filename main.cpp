#include <iostream>
#include <Windows.h>
#include "Feed/Feed.h"

using namespace std;

void feed_test() {
	cout << "Posts generating..." << endl;
	Text_Content tc1;
	Text_Content tc2("test content string", "User1");
	Text_Content tc3(tc2);
	tc1 = tc1 + "\nNew added string";

	Image_Content ic1;
	Image_Content ic2("  *  \n *** \n*****", "Apple Iphone 8", 1, "User2");
	Image_Content ic3(ic1 + "\n" + ic2);


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
	Sponsored_Post p5(p4 + tc2);
	p4.set_sponsor_link("www.yandex.ru");
	p5.add_like();
	p5.add_like();
	p5.add_like();
	p5.add_like();

	Sleep(1000);
	Sponsored_Post p6;
	p6.add_content(ic3);

	User_Post p7(p1 + p3);

	Admin_Feed fd;
	fd += p1;
	fd += p2;
	fd += p3;
	fd += p4;
	fd += p5;
	fd += p6;
	fd += p7;
	
	system("cls");

	cout << p5;
	//fd.user_interface();
}

int main() {
	srand(time(NULL));

	feed_test();

	return 0;
}