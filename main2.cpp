#include <iostream>
#include <fstream>
#include <ranges>
#include <vector>
#include <string>
using namespace std;

struct Account {
	unsigned id;
	string login;
	string name;
	string shell;
	string home_dir;
};


int main() {
	vector<Account> users;
	for(ifstream input("/etc/passwd"); !input.eof();) {
		Account acc = { 0 };
		string s;

		getline(input, acc.login, ':');
		if (input.eof()) break;
		getline(input, s, ':');

		for (char c; (c = input.get()) != ':';)
			acc.id = acc.id * 10 + c - '0';

		getline(input, s, ':');
		getline(input, acc.name, ':');
		getline(input, acc.home_dir, ':');
		getline(input, acc.shell);

		users.push_back(acc);
	}



	return 0;
}
