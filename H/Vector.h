#pragma once
#include<iostream>

template<class T>
class Vector {
public:
  Vector<T>(int n = 64) : _capacity(n) {
    _size = 0;
    _head = new T[n];
    _end = _head;
  }
   Vector<T>(const Vector<T>& vec) {
    this->_size = vec.size();
    this->_capacity = vec._capacity;
    T* newhead = new T[_capacity];
    if (_head != nullptr)
      delete[] _head;
    for (int i = 0; i < this->_size; i++)
      *(newhead + i) = *(vec.begin() + i);
    this->_head = newhead;
    this->_end = this->_head + (_size ? _size - 1 : 0);
  }
  ~Vector<T>() {
    if (_head != nullptr) delete[] _head;
    _end = nullptr;
    _head = nullptr;
  }
public:

  int size()const { return _size; }
  bool empty() const { return !_size; }
  T* begin()const { return this->_head; }
  bool resize(int s);
  void push_back(const T& item);
  void push_back(const T&& item);
  bool pop_back();
  void clear();
  int find(const T& item);
  bool erase(int ind);

  T& operator[] (int ind)const;

  void operator=(Vector<T>& vec);

private:
  int _size,_capacity;//size为数组有效长度，capacity为数组容量
  T* _head;
  T* _end;
  //when size*4<capacity then shrink
  void shrink();
  void expand();
};

template<typename T>
void Vector<T>::shrink() {
  if ((_size << 2) < _capacity) {
    this->resize(_size ? _size << 1 : _capacity >> 1);
  }
}

template<typename T>
void Vector<T>::expand() {
  if (_size == _capacity) {
    this->resize(_capacity << 1);
  }
}

template<typename T>
bool Vector<T>::resize(int s) {
  if (this->_size < s)
    return false;
  T* newhead = new T[s];
  for (int i = 0; i < this->_size; i++) {
    newhead[i] = this->_head[i];
  }
  delete[] this->_head;
  this->_head = newhead;
  this->_end = this->_head + (_size ? _size - 1 : 0);
  this->_size = s;
  return true;
}

template<typename T>
void Vector<T>::push_back(const T& item) {
  this->_head[_size++] = item;
  this->_end = this->_head + _size - 1;
  this->expand();
}

template<typename T>
void Vector<T>::push_back(const T&& item) {
  this->_head[_size++] = item;
  this->_end = this->_head + _size - 1;
  this->expand();
}

template<typename T>
bool Vector<T>::pop_back() {
  if (this->_size == 0)
    return false;
  this->_size--;
  this->_end = this->_head + (_size ? _size - 1 : 0);
  this->shrink();
  return true;
}

template<typename T>
void Vector<T>::clear() {
  this->_end = this->_head;
  this->_size = 0;
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
void Vector<T>::operator=(Vector<T>& vec) {
  this->_size = vec.size();
  this->_capacity = vec._capacity;
  T* newhead = new T[_capacity];
  if (_head != nullptr)
    delete[] _head;
  for (int i = 0; i < this->_size; i++)
    *(newhead + i) = *(vec.begin() + i);
  this->_head = newhead;
  this->_end = this->_head + (_size ? _size - 1 : 0);
  //return *this;
}

template<typename T>
int Vector<T>::find(const T& item) {
  for (int i = 0; i < this->_size; i++) {
    if ((*this)[i] == item)
      return i;
  }
  return -1;
}

template<typename T>
bool Vector<T>::erase(int ind) {
  if (ind < 0 || ind >= this->_size) {
    std::cout << "the index is out of the vector" << '\n';
    return false;
  }
  for (int i = ind; i < this->_size - 1; i++) {
    this->_head[i] = this->_head[i + 1];
  }
  this->pop_back();
  return true;
}
