#include<iostream>
#include<queue>
#include"../H/Priority_queue.h"
#include<limits.h>

struct Int{
	Int()=default;
	Int(int v){val=v;}
	int val;
	bool operator < (const Int&rhs){
		return val>rhs.val;
	}
	bool operator == (const Int&rhs){
		return val==rhs.val;
	}
};

int main() {
	int N;
	std::cin >> N;
	while(std::cin.fail()||N<1){
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		std::cout<<"input error,please re-enput!"<<'\n';
		std::cin>>N;
	}
	Priority_queue<Int> p;
	for (int i = 0, x; i < N; i++) {
		std::cin >> x;
		while(std::cin.fail()||x<=0){
			std::cin.clear();
			std::cin.ignore(INT_MAX,'\n');
			std::cout<<"input error,please re-enput!"<<'\n';
			std::cin>>x;
		}
		p.push(Int(x));
	}
	int ans = 0;
	for (int i = 0; i < N - 1; i++) {
		int u = p.top().val; p.pop();
		int v = p.top().val; p.pop();
		ans += u + v;
		p.push(u + v);
	}
	if(N==1)
		ans+=p.top().val;
	std::cout << ans << '\n';
}
