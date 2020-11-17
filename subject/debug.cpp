#include<iostream>
#include<string>
#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<algorithm>
#include<map>
#include<stack>
#include<vector>
#include"../H/Maxheap.h"
#include"../H/Vector.h"
#include"../H/Priority_queue.h"
#include<queue>

using namespace std;

int main() {
  Priority_queue<int> p;
  for (int i = 0; i < 10; i++) {
    p.push(i);
  }
  p.push(-10);
  while (!p.empty()) {
    cout << p.top();
    p.pop();
  }

 /* Vector<int> vec;
  for (int i = 0; i < 10; i++)
    vec.push_back(-i);
  MaxHeap<int> m(vec);
  m.erase(-5);
  while (!m.empty()) {
    cout << m.top();
    m.pop_heap();
  }*/
}