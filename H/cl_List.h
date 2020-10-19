#pragma once
#include<iostream>
#include<typeinfo>

template<class T> class List;

template<class T>
class ListNode
{
public:
  friend List<T>;
  ListNode():_data(NULL),_next(nullptr){}//构造函数
  ListNode(const T& item,ListNode<T>* n=nullptr)
    :_data(item),_next(n){}
  ~ListNode() {//析构函数
    _next = nullptr;
  }
  ListNode<T>* next()const { return this->_next; }//返回后置指针
  T data()const { return this->_data; }//返回数据
  void setData(T& d) { _data = d; }//设置数据
private:
  T _data;//存数据
  ListNode* _next;//后置指针
};

template<class T>
class List
{
public:
  List() :_len(0),_head(new ListNode<T>()),_last(nullptr) {//构造函数
    _head->_next= _head;
    _last = _head;
  }
  ~List() {//析构函数
    this->clear();
    delete _head;
  }
public:
  ListNode<T>* find(const T& item)const;
  void clear();//清除
  void push(const T& item);//后插
  bool insert(const T& item, int ind = 0);//插入
  bool erase(const T& item);//删除
  ListNode<T>* begin()const { return this->_head->_next; }
  ListNode<T>* end()const { return this->_head; }
  bool change(const T& newitem, ListNode<T>* itor);//修改
  int size()const { return this->_len; }
  bool empty()const { return !(this->_len); }
  void print()const;
private:
  int _len;
  ListNode<T>* _head;
  //head is a pointer to the first list node
  ListNode<T>* _last;
  //last is a pointer to the last node
};

template<typename T>
void List<T>::clear() {
  if (this->empty())
    return;
  ListNode<T>* pmove = this->begin(), * pdel;
  while (pmove != this->_head) {
    pdel = pmove;
    pmove = pdel->_next;
    delete pdel;
  }
  this->_len = 0;
  this->_head->_next = this->_head;
  this->_last = this->_head;
}

template<typename T>
void List<T>::push(const T& item) {
  ListNode<T>* newnode = new ListNode<T>(item);
  newnode->_next = this->_head;
  this->_last->_next = newnode;
  _last = newnode;
  this->_len++;
}

template<typename T>
ListNode<T>* List<T>::find(const T& item)const {
  ListNode<T>* pmove = this->begin();
  while (pmove != this->_head) {
    if (pmove->data() == item)
      return pmove;
    pmove = pmove->_next;
  }
  return pmove;
}

template<typename T>
bool List<T>::insert(const T& item, int ind) {
  if (ind <= 0||ind>this->_len+1)
    return false;
  if (ind == this->_len + 1) {
    this->push(item);
    this->_last = this->_last->_next;
    this->_len++;
    return true;
  }
  ListNode<T> *newnode = new ListNode<T>(item), * pmove = this->_head;
  for (int i = 1; i < ind; i++) {
    pmove = pmove->_next;
  }
  newnode->_next = pmove->_next;
  pmove->_next = newnode;
  this->_len++;
  return true;
}

template<typename T>
bool List<T>::erase(const T& item) {
  ListNode<T>* pmove = this->_head, * q=nullptr;
  while (pmove->_next != this->_head) {
    if (pmove->_next->data() == item) {
      q = pmove;
      pmove = pmove->_next;
      break;
    }
    else
      pmove = pmove->_next;
  }
  if (pmove->_next == this->_head)
    return false;
  q->_next = pmove->_next;
  this->_len--;
  delete pmove;
  return true;
}

template<typename T>
bool List<T>::change(const T& newitem, ListNode<T>* itor) {
  if (!itor||itor==this->_head)
    return false;
  itor->setData(newitem);
  return true;
}

template<typename T>
void List<T>::print()const {
  if (this->empty()) {
    std::cout << "NULL";
    return;
  }
  ListNode<T>* itor = this->begin();
  for (; itor != this->end(); itor = itor->_next) {
    std::cout << itor->_data << ' ';
  }
  std::cout << '\n';
}