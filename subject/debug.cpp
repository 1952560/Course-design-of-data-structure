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
#include"../H/Vector.h"
#include"../H/Sort.h"

#define ll long long
#define lld long long double
#define ull unsigned long long
using namespace std;

const ll maxn = 1e2 + 10;

int main() {
  Vector<int> v=get_random(10);
  Vector<int> c;
  c = v;
  for (int i = 0; i < v.size(); i++)
    cout << c[i] << ' ';
}