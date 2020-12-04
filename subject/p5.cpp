#include<iostream>
#include"../H/Priority_queue.h"

class customer {
public:
	customer() :number(0), time(0), flag(0) {}
	customer(int num, int t, bool f) :
		number(num), time(t), flag(f) {}
	int number;
	int time;
	bool flag;
	bool operator < (const customer& rhs)const {
		if (time < rhs.time)
			return false;
		else if (time == rhs.time && flag)
			return false;
		return true;
	}
	bool operator ==(const customer& rhs)const {
		if (number == rhs.number && time == rhs.time && flag == rhs.flag)
			return true;
		return false;
	}
};

int main() {
	int N;
	std::cin >> N;
	int x = 0;
	int time1 = 1, time2 = 2;
	Priority_queue<customer>p;
	while (N--) {
		std::cin >> x;
		if (x & 1) {
			p.push(customer(x, time1, true));
			time1++;
		}
		else {
			p.push(customer(x, time2, false));
			time2 += 2;
		}
	}
	while (!p.empty()) {
		std::cout << p.top().number << ' ';
		p.pop();
	}
}
