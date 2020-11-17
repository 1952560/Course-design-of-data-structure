#pragma once
#include"Maxheap.h"

template<class T>
class Priority_queue {
public:
  Priority_queue():_size(0){}
  
  void push(const T& item);
  void push(const T&& item);
  void pop();
  T top() const;
  int size() const { return _size; }
  bool empty() const { return !_size; }

private:
  MaxHeap<T> _heap;
  int _size;
};

template<typename T>
void Priority_queue<T>::push(const T& item) {
  _size++;
  _heap.push_heap(item);
}

template<typename T>
void Priority_queue<T>::push(const T&& item) {
  _size++;
  _heap.push_heap(item);
}

template<typename T>
void Priority_queue<T>::pop() {
  _heap.pop_heap();
  _size--;
}

template<typename T>
T Priority_queue<T>::top() const{
  if (!size()) {
    static T item;
    std::cout << "Heap is empty!" << '\n';
    return item;
  }
  return _heap.top();
}