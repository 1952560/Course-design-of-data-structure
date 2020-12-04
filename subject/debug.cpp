#include<iostream>
#include<string>
#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<algorithm>
#include<map>
#include<set>
#include<stack>
#include<vector>
#include<queue>
#include<unordered_set>
#include<unordered_map>
#include<thread>
#include<mutex>
#include<chrono>

#define ll long long
#define lld long long double
#define ull unsigned long long
using namespace std;

const ll maxn = 1e2 + 10;
int counter = 0;
std::mutex mtx;

void increase(int time) {
	for (int i = 0; i < time; i++) {
		//当前线程休眠1毫秒
		mtx.lock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		counter++;
		mtx.unlock();
	}
}

int main() {
	std::thread t1(increase, 1000);
	std::thread t2(increase, 1000);
	t1.join();
	t2.join();
	std::cout << "counter:" << counter << std::endl;
	return 0;
}
