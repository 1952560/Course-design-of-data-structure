#include"../H/Sort.h"
#include<vector>

int main() {
	Vector<int> v = get_random(100);
	// Vector<int> v;
	// for (int i = 0; i < 10; i++)
	//  	v.push_back(20 - i);
	for (int i = 0; i < 100; i++) {
		std::cout << v[i] << ' ';
	}
	std::cout << '\n' << '\n';
	radix_sort(v);
	for (int i = 0; i < 100-1; i++) {
		if (v[i] > v[i + 1])
			std::cout << "error";
	}
	std::cout<<'\n';
	for (int i = 0; i < 100; i++) {
		std::cout << v[i] << ' ';
	}
}
