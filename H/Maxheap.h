#pragma once
#include"Vector.h"

template<class T>
class MaxHeap {
public:
  MaxHeap() :_size(0) {}
  MaxHeap(Vector<T>& v) :_vec(v), _size(v.size()) {
    for (int i = _size - 1; i >= 0; i--) {
      this->fitdown(i);
    }
  }

  void push_heap(const T& item);
  void push_heap(const T&& item);
  void pop_heap();
  T top() const { return _vec[0]; }
  void erase(int ind);
  int  get_index(T item);
  bool empty() {
    return !_size;
  }

private:
  void fitdown(int ind);
  void fitup(int ind);
  //void swap(int ind1, int ind2);

private:
  Vector<T> _vec;
  int _size;
};

template<typename T>
void MaxHeap<T>::fitdown(int ind) {
  if ((ind << 1) + 1 >= _size)
    return;
  T val1 = _vec[(ind << 1) + 1];
  if ((ind << 1) + 2 >= _size) {
    if (_vec[ind] < val1) {
      _vec[(ind << 1) + 1] = _vec[ind];
      _vec[ind] = val1;
    }
  }
  else {
    T val2 = _vec[(ind << 1) + 2];
    if ((val2 < val1 || val2 == val1) && _vec[ind] < val1) {
      _vec[(ind << 1) + 1] = _vec[ind];
      _vec[ind] = val1;
      fitdown((ind << 1) + 1);
    }
    else if (val1 < val2 && _vec[ind] < val2) {
      _vec[(ind << 1) + 2] = _vec[ind];
      _vec[ind] = val2;
      fitdown((ind << 1) + 2);
    }
  }
}

template<typename T>
void MaxHeap<T>::fitup(int ind) {
  if (!ind)
    return;
  T val = _vec[(ind - 1) >> 1];
  if (val < _vec[ind]) {
    _vec[(ind - 1) >> 1] = _vec[ind];
    _vec[ind] = val;
    fitup((ind - 1) >> 1);
  }
}

template<typename T>
void MaxHeap<T>::push_heap(const T& item) {
  _vec.push_back(item);
  _size++;
  fitup(_size - 1);
}

template<typename T>
void MaxHeap<T>::push_heap(const T&& item) {
  _vec.push_back(item);
  _size++;
  fitup(_size - 1);
}

template<typename T>
void MaxHeap<T>::pop_heap() {
  erase(0);
}

template<typename T>
void MaxHeap<T>::erase(int ind) {
  if (!_size) {
    std::cout << "Heap is empty!" << '\n';
    return;
  }
  if (ind < 0) {
    std::cout << "the item is not in the heap!" << '\n';
    return;
  }
  _vec[ind] = _vec[_size - 1];
  _vec.pop_back();
  _size--;
  fitdown(ind);
}

template<typename T>
int MaxHeap<T>::get_index(T item) {
  if (!_size) {
    std::cout << "Heap is empty!" << '\n';
    return -1;
  }
  for (int i = 0; i < _size; i++) {
    if (_vec[i] == item)
      return i;
  }
  return -1;
}