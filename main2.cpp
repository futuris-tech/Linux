#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct Account {
	unsigned id;
	string login;
	string name;
	string shell;
	string home_dir;
};
ostream& operator<<(ostream& os, Account& acc) {
	os	<< acc.id << '\t'
		<< acc.login << '\t'
		<< acc.name << '\t'
		<< acc.name << '\t'
		<< acc.home_dir;
	return os;
}
ostream& operator<<(ostream& os, vector<Account>& users) {
	for (auto& user : users)
		os << user << '\n';
	return os;
}


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

	vector<Account> v1;
	auto begin = users.begin();
	auto end = users.end();
	while (true) {
		begin = ranges::find_if(begin, end, [](const Account& user) {
			return user.shell == "/bin/bash";
		});
		if (begin == end) break;
		v1.push_back(*begin++);
	}
	cout << v1 << '\n';

	vector<Account> v2;
	map<unsigned, Account> m;
	for (auto& user : users)
		m[user.id] = user;
	for (auto& item : m) {
		if (item.first >= 1000) break;
		v2.push_back(item.second);
	}
	cout << v2 << '\n';

	struct counter {
		unsigned i = 0;
	};
	unordered_map<string, counter> v3;
	for (auto& user : users)
		v3[user.shell].i++;
	for (auto& shell : v3)
		cout << shell.first << ':' << '\t' << shell.second.i << '\n';
	cout << '\n';

	vector<Account> v4;
	unordered_set<unsigned> unique, duplicate;
	for (auto& user : users)
		if (unique.contains(user.id))
			duplicate.insert(user.id);
		else unique.insert(user.id);
	for (auto& user : users)
		if (duplicate.contains(user.id))
			v4.push_back(user);
	cout << v4 << '\n';
	
	
	return 0;
}
