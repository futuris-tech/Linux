#include <iostream>
#include <array>
#include <tuple>
using namespace std;

void message(ostream& is, const char* str) {
	is << str;
}
template <typename T0, typename... T>
void message(ostream& is, const char* str, T0 first, T... args) {
	while (true) {
		if (!*str) return;
		if (*str == '%') {
			is << first;
			return message(is, str + 1, args...);
		}
		is << *str;
		str++;
	}
}

template <typename T, size_t N>
auto cat(const array<T, N>& first) {
	return first;
}
template <typename T, size_t N1, size_t N2, typename... Args>
auto cat(const array<T, N1>& first, const array<T, N2>& second, Args&... args) {
	array<T, N1 + N2> new_arr;
	copy(first.begin(), first.end(), new_arr.begin());
	copy(second.begin(), second.end(), new_arr.begin()+N1);
	return cat(new_arr, args...);
}

template <class T, int N, int M>
struct Tie {
	T* ptr[M];
	void operator=(const array<T, N*M>& rhs) {
		auto src = rhs.data();
		for (auto dst : ptr) {
			copy(src, src + N, dst);
			src += N;
		}
	}
};
template <typename T>
auto tie_help(T** ptr) {}
template <typename T, size_t N, typename... Args>
auto tie_help(T** ptr, array<T, N>& first, Args&... args) {
	*ptr = first.data();
	if constexpr (sizeof...(args))
		tie_help(ptr + 1, args...);
}
template <typename T, size_t N, typename... Args>
auto tie(array<T, N>& first, Args&... args) {
	Tie<T, N, 1 + sizeof...(args)> t;
	tie_help(t.ptr, first, args...);
	return t;
}


int main() {
	message(cout, "% + % = %\n", 'a', 2, 3.0);

	array<float, 3> a = { 1,2,3 };
	array<float, 3> b = { 4,5,6 };
	array<float, 6> c = { 7,8,9,10,11,12 };
	auto x = cat(a, b, c);
	for (auto f : x)
		cout << f << '\t';
	cout << '\n';

	tie(a, b) = c;
	for (auto f : a)
		cout << f << '\t';
	cout << '\n';
	for (auto f : b)
		cout << f << '\t';
	cout << '\n';

	return 0;
}
