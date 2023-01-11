#include <iostream>
#include <locale.h>
#include "Feed.h"


// Unauthorized Feed //

Unauthorized_Feed::Unauthorized_Feed() {}

Unauthorized_Feed::Unauthorized_Feed(int post_count) : post_array{ post_array.get_count() } {}

Unauthorized_Feed::Unauthorized_Feed(Unauthorized_Feed& another) {
	for (int i = 0; i < another.get_post_count(); i++) {
		post_array.add_element(another.get_post(i));
	}
}

Unauthorized_Feed::~Unauthorized_Feed() {}

void Unauthorized_Feed::user_interface() {
	while (true) {
		int input;
		if (post_array.get_count() == 0) {
			cout << "You don't have any posts in your feed yet" << endl << endl;
		}
		cout << "1 - 5 most popular posts" << endl
			<< "2 - 5 latest posts" << endl
			<< "3 - Show posts by one" << endl
			<< "0 - exit" << endl;
		cin >> input;
		cout << endl;
		system("cls");
		if (input == 1) {
			sort_by_likes();
			for (int i = 0; i < min(5, post_array.get_count()); i++) {
				print_post(i);
			}
		}
		else if (input == 2) {
			sort_by_date();
			for (int i = 0; i < min(5, post_array.get_count()); i++) {
				print_post(i);
			}
		}
		else if (input == 3) {
			one_post_interface();
		}
		else if (input == 0) {
			break;
		}
		else {
			cout << "Unknown command" << endl;
		}
	}
}

int Unauthorized_Feed::get_post_count() const {
	return post_array.get_count();
}

const Post& Unauthorized_Feed::get_post(int idx) const {
	return post_array.get_element(idx);
}

void Unauthorized_Feed::add_post(const Post& new_post) {
	post_array.add_element(new_post);
}


void Unauthorized_Feed::one_post_interface() {
	int current_post_idx = 0;
	while (true) {
		if (post_array.get_count() == 0) {
			cout << "You don't have any posts in your feed yet" << endl << endl;
		}
		else {
			print_post(current_post_idx);
			cout << "1 - previous post" << endl
				<< "2 - next post" << endl;
		}
		cout << "0 - back to menu" << endl;
		int input;
		cin >> input;
		cout << endl;
		system("cls");
		if (input == 0) {
			break;
		}
		else if (post_array.get_count() == 0) {
			continue;
		}
		if (input == 1) {
			if (current_post_idx > 0) {
				current_post_idx--;
			}
		}
		else if (input == 2) {
			if (current_post_idx < post_array.get_count() - 1) {
				current_post_idx++;
			}
		}
	}
}

void Unauthorized_Feed::print_post(int post_idx) {
	String post;
	post_array.get_element(post_idx).get_post(post);
	char* c_post = post.get_string();
	cout << "________________________" << endl << c_post << "________________________" << endl << endl;
	delete[] c_post;
}


void Unauthorized_Feed::sort_by_likes() {
	post_array.sort(&likes_cmp);
}


void Unauthorized_Feed::sort_by_date() {
	post_array.sort(&date_cmp);
}

const char* Unauthorized_Feed::get_type() const {
	return "Unauthorized Feed";
}




// User Feed //

User_Feed::User_Feed() : Unauthorized_Feed() {}

User_Feed::User_Feed(int post_count) : Unauthorized_Feed(post_count) {}

User_Feed::User_Feed(User_Feed& another) : Unauthorized_Feed(another) {}

User_Feed::~User_Feed() {}

void User_Feed::one_post_interface() {
	int current_post_idx = 0;
	while (true) {
		if (post_array.get_count() == 0) {
			cout << "You don't have any posts in your feed yet" << endl << endl;
		}
		else {
			print_post(current_post_idx);
			cout << "1 - previous post" << endl
				<< "2 - next post" << endl
				<< "3 - like" << endl
				<< "4 - remove like" << endl;
		}
		cout << "0 - back to menu" << endl;
		int input;
		cin >> input;
		cout << endl;
		system("cls");
		if (input == 0) {
			break;
		}
		else if (post_array.get_count() == 0) {
			continue;
		}
		if (input == 1) {
			if (current_post_idx > 0) {
				current_post_idx--;
			}
		}
		else if (input == 2) {
			if (current_post_idx < post_array.get_count() - 1) {
				current_post_idx++;
			}
		}
		else if (input == 3) {
			post_array.get_element(current_post_idx).add_like();
		}
		else if (input == 4) {
			post_array.get_element(current_post_idx).remove_like();
		}
	}
}

const char* User_Feed::get_type() const {
	return "User Feed";
}




// Admin Feed //

Admin_Feed::Admin_Feed() : User_Feed() {}

Admin_Feed::Admin_Feed(int post_count) : User_Feed(post_count) {}

Admin_Feed::Admin_Feed(Admin_Feed& another) : User_Feed(another) {}

Admin_Feed::~Admin_Feed() {}

void Admin_Feed::one_post_interface() {
	int current_post_idx = 0;
	while (true) {
		if (post_array.get_count() == 0) {
			cout << "You don't have any posts in your feed yet" << endl << endl;
		}
		else {
			print_post(current_post_idx);
			cout << "1 - previous post" << endl
				<< "2 - next post" << endl
				<< "3 - like" << endl
				<< "4 - remove like" << endl
				<< "5 - delete this post" << endl;
		}
		cout << "0 - back to menu" << endl;
		int input;
		cin >> input;
		cout << endl;
		system("cls");
		if (input == 0) {
			break;
		}
		else if (post_array.get_count() == 0) {
			continue;
		}
		if (input == 1) {
			if (current_post_idx > 0) {
				current_post_idx--;
			}
		}
		else if (input == 2) {
			if (current_post_idx < post_array.get_count() - 1) {
				current_post_idx++;
			}
		}
		else if (input == 3) {
			post_array.get_element(current_post_idx).add_like();
		}
		else if (input == 4) {
			post_array.get_element(current_post_idx).remove_like();
		}
		else if (input == 5) {
			post_array.remove_element(current_post_idx);
			if (current_post_idx == post_array.get_count()) {
				current_post_idx--;
			}
		}
	}
}

const char* Admin_Feed::get_type() const {
	return "Admin Feed";
}

