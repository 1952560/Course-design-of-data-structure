#pragma once
#include<iostream>

template<class T>
class Vector {
public:
  Vector<T>(int s = 64) : _size(s) {
    _len = 0;
    _head = new T[s];
    _end = _head;
  }
  ~Vector<T>() {
    if (_head) delete[] _head;
    _end = nullptr;
  }

  int size()const { return _size; }
  int len()const { return _len; }
  bool empty() const { return !_len; }
  bool resize(int s);
  void push_back(T& item);
  void push_back(T&& item);
  bool pop_back();
  void clear();
  int find(T item);
  bool rease(int ind);

  T& operator[] (int ind)const;

  Vector<T> operator =(Vector<T>& vec);

private:
  int _size, _len;//len为数组有效长度，size为数组容量
  T* _head;
  T* _end;
  //to avoid vesting memory,when len*4<size then shrink
  void shrink();
  void expand();
};

template<typename T>
void Vector<T>::shrink() {
  if ((_len << 2) < _size) {
    this->resize(_len ? _len << 1 : _size >> 1);
  }
}

template<typename T>
void Vector<T>::expand() {
  if (_len == _size) {
    this->resize(_size << 1);
  }
}

template<typename T>
bool Vector<T>::resize(int s) {
  if (this->_len < s)
    return false;
  T* newhead = new T[s];
  for (int i = 0; i < this->_len; i++) {
    newhead[i] = this->_head[i];
  }
  delete[] this->_head;
  this->_head = newhead;
  this->_end = this->_head + (_len ? _len - 1 : 0);
  this->_size = s;
  return true;
}

template<typename T>
void Vector<T>::push_back(T& item) {
  this->_head[_len++] = item;
  this->_end = this->_head + _len - 1;
  this->expand();
}

template<typename T>
void Vector<T>::push_back(T&& item) {
  this->_head[_len++] = item;
  this->_end = this->_head + _len - 1;
  this->expand();
}

template<typename T>
bool Vector<T>::pop_back() {
  if (this->_len == 0)
    return false;
  this->_len--;
  this->_end = this->_head + (_len ? _len - 1 : 0);
  this->shrink();
  return true;
}

template<typename T>
void Vector<T>::clear() {
  this->_end = this->_head;
  this->_len = 0;
  shrink();
}

template<typename T>
T& Vector<T>::operator[](int ind)const {
  static T t;
  if (ind >= _size || ind < 0) {
    std::cout << "the index if out of the vector" << '\n';
    return t;
  }
  return this->_head[ind];
}

template<typename T>
Vector<T> Vector<T>::operator =(Vector<T>& vec) {
  this->_size = vec.size();
  this->_len - vec.len();
  T* itor = this->_head;
  if (itor)
    delete[] itor;
  for (int i = 0; i < this->_len; i++)
    this->_head[i] = vec[i];
  return *this;
}

template<typename T>
int Vector<T>::find(T item) {
  for (int i = 0; i < this->_len; i++) {
    if ((*this)[i] == item)
      return i;
  }
  return -1;
}

template<typename T>
bool Vector<T>::rease(int ind) {
  if (ind < 0 || ind >= this->_len) {
    std::cout << "the index is out of the vector" << '\n';
    return false;
  }
  for (int i = ind; i < this->_len - 1; i++) {
    this->_head[i] = this->_head[i + 1];
  }
  this->pop_back();
  return true;
}