#include<iostream>
#include<vector>
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
  std::priority_queue<int, std::vector<int>, std::greater<int> > queueA, queueB;
  int x = 0, n = N;
  while (n--) {
    std::cin >> x;
    if (x & 1)
      queueA.push(x);
    else
      queueB.push(x);
  }
  std::priority_queue<customer>queueC;
  int time1 = 1, time2 = 2;
  while (!queueA.empty()) {
    queueC.push(customer(queueA.top(), time1, true));
    time1++;
    queueA.pop();
  }
  while (!queueB.empty()) {
    queueC.push(customer(queueB.top(), time2, false));
    time2 *= 2;
    queueB.pop();
  }
  while (!queueC.empty()) {
    std::cout << queueC.top().number << ' ';
    queueC.pop();
  }
}