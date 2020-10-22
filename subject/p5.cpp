#include<iostream>
#include<queue>

class customer {
public:
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
};

int main() {
  int N;
  std::cin >> N;
  int x = 0;
  int time1 = 1, time2 = 2;
  std::priority_queue<customer>q;
  while (N--) {
    std::cin >> x;
    if (x & 1) {
      q.push(customer(x, time1, true));
      time1++;
    }
    else {
      q.push(customer(x, time2, false));
      time2 += 2;
    }
  }
  while (!q.empty()) {
    std::cout << q.top().number << ' ';
    q.pop();
  }
}