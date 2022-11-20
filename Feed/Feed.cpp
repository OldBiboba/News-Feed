#include "Feed.h"

Feed::Feed() {}

Feed::Feed(int post_count) : post_array{post_array.get_count()} {}

Feed::Feed(Feed& another){
	for (int i = 0; i < another.get_post_count(); i++) {
		post_array.add_element(another.get_post(i));
	}
}

Feed::~Feed(){

}

void Feed::user_intrface()
{
	while (true) {
		int input;
		cout << "1 - 5 most popular posts" << endl
			<< "2 - 5 latest posts" << endl
			<< "3 - Show posts by one" << endl
			<< "4 - exit" << endl;
		cin >> input;
		cout << endl;
		system("cls");
		if (input == 1) {
			sort_by_likes();
			for (int i = 0; i < 5; i++) {
				print_post(i);
			}
		}
		else if (input == 2) {
			sort_by_date();
			for (int i = 0; i < 5; i++) {
				print_post(i);
			}
		}
		else if (input == 3) {
			one_post_interface();
		}
		else if (input == 4) {
			break;
		}
		else {
			cout << "Unknown command" << endl;
		}
	}
}

int Feed::get_post_count() const {
	return post_array.get_count();
}

const Post& Feed::get_post(int idx) const {
	return post_array.get_element(idx);
}

void Feed::add_post(const Post& new_post) {
	post_array.add_element(new_post);
}



void Feed::one_post_interface()
{

	int current_post_idx = 0;
	while (true) {
		print_post(current_post_idx);
		cout << "1 - previous post" << endl
			<< "2 - next post" << endl
			<< "3 - like" << endl
			<< "4 - remove like" << endl
			<< "5 - back to menu" << endl;
		int input;
		cin >> input;
		cout << endl;
		system("cls");
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
			break;
		}
	}
}

void Feed::print_post(int post_idx) {
	String post;
	post_array.get_element(post_idx).get_post(post);
	cout << "________________________" << endl << post.get_string() << "________________________" << endl << endl;
}

#if 0
void Feed::add_like(int idx) {
	post_array.get_element(idx).add_like();
}

void Feed::remove_like(int idx) {
	post_array.get_element(idx).remove_like();
}
#endif

void Feed::sort_by_likes() {
	post_array.sort(&likes_cmp);
}


void Feed::sort_by_date() {
	post_array.sort(&date_cmp);
}

const char* Feed::get_type(){
	return "User Feed";
}


