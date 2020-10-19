#include"../H/Vector.h"

using namespace std;

int mian()
{
  Vector<int> v;
  for (int i = 0; i < 10; i++)
    v.push_back(i);
  for (int i = 0; i < 10; i++)
    cout << v[i] << ' ';
  cout << '\n';
  Vector<int> vec = v;
  for (int i = 0; i < 10; i++)
    cout << vec[i] << ' ';
  cout << '\n';
  return 0;
}