#include"../H/Sort.h"

int main() {
	// Vector<int> v = get_random(100);
	// // Vector<int> v;
	// // for (int i = 0; i < 100; i++)
	// // 	v.push_back(100 - i);
	// for (int i = 0; i < 100; i++) {
	// 	std::cout << v[i] << ' ';
	// }
	// std::cout << '\n' << '\n';
	// radix_sort(v);
	// for (int i = 0; i < 100 - 1; i++) {
	// 	if (v[i] > v[i + 1])
	// 		std::cout << "error";
	// }
	// for (int i = 0; i < 100; i++) {
	// 	std::cout << v[i] << ' ';
	// }
	Vector<int> v=get_random(10);
	Vector<int> a=v;
	Vector<int> b;
	b=a;
	for(int i=0;i<10;i++){
		std::cout<<v[i]<<' '<<a[i]<<' '<<b[i]<<'\n';
	}
}
