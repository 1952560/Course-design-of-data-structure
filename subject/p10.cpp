#include"../H/Sort.h"

int main() {
  Vector<int> v = get_random(100);
  for (int i = 0; i < 100; i++) {
    std::cout << v[i] << ' ';
  }
  std::cout << '\n'<<'\n';
  insert_sort(v);
  for (int i = 0; i < 100-1; i++) {
    if (v[i] > v[i + 1])
      std::cout << "error";
  }
  for (int i = 0; i < 100; i++) {
    std::cout << v[i] << ' ';
  }
}