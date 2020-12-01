#pragma once
#include"Vector.h"
#include<random>
#include<ctime>

/*
1.冒泡 2.选择 3.直接插入 4.希尔排序 5.快速排序
6.堆排序 7.归并 8 基数 9 退出程序
*/

template<typename T>
void swap(T& a, T& b) {
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
}

Vector<int> get_random(int size) {
  std::default_random_engine e;
  std::uniform_int_distribution<int> u(-INT_MAX-1, INT_MAX);
  e.seed(time(0));
  Vector<int> v;
  for (int i = 0; i < size; i++)
    v.push_back(u(e));
  return v;
}

//bubble_sort(1)
template<typename T>
void bubble_sort(Vector<T>& v) {
  if (v.size() <= 1)
    return;
  for (int i = 0; i < v.size() - 1; i++) {
    for (int j = 0; j < v.size() - i - 1; j++) {
      if (v[j] > v[j + 1]) {
        swap<T>(v[j], v[j + 1]);
      }
    }
  }
}

//select_sort(2)
template<typename T>
void select_sort(Vector<T>& v) {
  if (v.size() <= 1)
    return;
  for (int i = 0; i < v.size() - 1; i++) {
    int min_index = i;
    for (int j = i + 1; j < v.size(); j++) {
      if (v[j] < v[min_index])
        min_index = j;
    }
    if (min_index != i)
      swap<T>(v[i], v[min_index]);
  }
}

//insert_sort(3)
template<typename T>
void insert_sort(Vector<T> &v) {
  if (v.size() <= 1)
    return;
  for (int i = 1; i < v.size(); i++) {
    int key = v[i];
    int j = i - 1;
    while (j >= 0 && key < v[j]) {
      v[j + 1] = v[j];
      j--;
    }
    v[j + 1] = key;
  }
}

//merge_sort(7)
template<typename T>
void merge_sort(Vector<T> &v, int start, int end) {
  if (start >= end)
    return;
  int len = end - start, mid = (len >> 1) + start;
  int start1 = start, end1 = mid;
  int start2 = mid + 1, end2 = end;
  merge_sort(v,start1, end1);
  merge_sort(v,start2, end2);
  Vector<T> reg;
  while (start1 <= end1 && start2 <= end2)
    reg.push_back(v[start1] < v[start2] ? v[start1++] : v[start2++]);
  while (start1 <= end1)
    reg.push_back(v[start1++]);
  while (start2 <= end2)
    reg.push_back(v[start2++]);
  for(int i=0;i<reg.size();i++)
    v[start+i] = reg[i];
}
