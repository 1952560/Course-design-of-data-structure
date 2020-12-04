#include<iostream>
#include<queue>

int main() {
	int N;
	std::cin >> N;
	std::priority_queue<int, std::vector<int>, std::greater<int> >p;
	for (int i = 0, x; i < N; i++) {
		std::cin >> x;
		p.push(x);
	}
	int ans = 0;
	for (int i = 0; i < N - 1; i++) {
		int u = p.top(); p.pop();
		int v = p.top(); p.pop();
		ans += u + v;
		p.push(u + v);
	}
	std::cout << ans << '\n';

}
