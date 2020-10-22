#pragma once
#include"Vector.h"

template<class T>
class Stack {
public:
  Stack():_size(_vec.size()){}
  Stack(Vector<T> vec, int s = 0) {
    _vec = vec;
    _size = vec.size();
  }
  ~Stack() = default;
public:
  void push(const T&& item);
  void push(const T& item);
  bool pop();
  T& top();
  const T& top()const;
  bool empty()const { return !_size; }
  int size()const { return _size; }
private:
  Vector<T> _vec;
  int _size;
};

template<typename T>
void Stack<T>::push(const T& item) {
  _vec.push_back(item);
  _size++;
}

template<typename T>
void Stack<T>::push(const T&& item) {
  _vec.push_back(item);
  _size++;
}

template<typename T>
bool Stack<T>::pop() {
  if (_vec.empty()) {
    std::cout << "the stack is empty!" << '\n';
    return false;
  }
  _vec.pop_back();
  _size--;
}

template<typename T>
T& Stack<T>::top() {
  if (_vec.empty()) {
    static T t;
    std::cout << "the stack is empty!" << '\n';
    return t;
  }
  return _vec[_size - 1];
}

template<typename T>
const T& Stack<T>::top()const {
  if (_vec.empty()) {
    static T t;
    std::cout << "the stack is empty!" << '\n';
    return t;
  }
  return _vec[_size - 1];
}