#pragma once
#include<iostream>
#include<typeinfo>

template<class T> class List;

template<class T>
class ListNode
{
public:
  friend List<T>;
  ListNode() :_pre(nullptr), _next(nullptr) {}
  ListNode(const T& item) :_data(item), _pre(nullptr), _next(nullptr) {}
  ~ListNode() { _pre = nullptr, _next = nullptr; }//��������
  ListNode<T>* next()const { return this->_next; }//���غ���ָ��
  ListNode<T>* pre()const { return this->_pre; }//����ǰ��ָ��
  T data()const { return this->_data; }//��������
  void setData(T d) { _data = d; }//��������
private:
  T _data;//������
  ListNode* _next;//����ָ��
  ListNode* _pre;//ǰ��ָ��
};

template<class T>
class List
{
public:
  List() :_len(0), _head(new ListNode<T>()) {
    _head->_next = _head;
    _head->_pre = _head;
  }
  ~List() {
    this->clear();
    delete _head;
  }
public:
  ListNode<T>* find(const T& item)const;
  void clear();//���
  void push(const T& item);//���
  void push(const T&& item);
  bool insertBefore(const T& item, ListNode<T>* itor);//��itorǰ����
  bool insertAfter(const T& item, ListNode<T>* itor);//��itor�����
  bool insert(const T& item, int ind);//��indλ�ò���
  bool erase(ListNode<T>* itor);//ɾ��
  ListNode<T>* begin()const { return this->_head->_next; }
  ListNode<T>* end()const { return this->_head; }
  bool change(const T& newitem, ListNode<T>* itor);//�޸�
  int size()const { return this->_len; }
  bool empty()const { return!(this->_len); }
  void print()const;
private:
  int _len;//length
  ListNode<T>* _head;//the pointer to the first node
};

template<typename T>
void List<T>::clear() {
  if (this->empty())
    return;
  ListNode<T>* pmove = this->begin(), * pdel;
  while (pmove != this->end()) {
    pdel = pmove;
    pmove = pdel->next();
    delete pdel;
  }
  this->_len = 0;
  this->_head->_next = this->_head;
  this->_head->_pre = this->_head;
}

template<typename T>
void List<T>::push(const T& item) {
  ListNode<T>* newnode = new ListNode<T>(item);
  newnode->_next = this->_head;
  newnode->_pre = this->_head->_pre;
  this->_head->_pre->_next = newnode;
  this->_head->_pre = newnode;
  this->_len++;
}

template<typename T>
void List<T>::push(const T&& item) {
    ListNode<T>* newnode = new ListNode<T>(item);
    newnode->_next = this->_head;
    newnode->_pre = this->_head->_pre;
    this->_head->_pre->_next = newnode;
    this->_head->_pre = newnode;
    this->_len++;
}

template<typename T>
ListNode<T>* List<T>::find(const T& item)const {
  ListNode<T>* pmove = this->begin();
  while (pmove != this->_head) {
    if (pmove->_data == item)
      return pmove;
    pmove = pmove->next();
  }
  return pmove;
}

template<typename T>
bool List<T>::insertBefore(const T& item, ListNode<T>* itor) {
  if (!itor)
    return false;
  ListNode<T>* newnode = new ListNode<T>(item);
  newnode->_pre = itor->_pre;
  newnode->_next = itor;
  itor->_pre->_next = newnode;
  itor->_pre = newnode;
  this->_len++;
  return true;
}

template<typename T>
bool List<T>::insertAfter(const T& item, ListNode<T>* itor) {
  if (!itor)
    return false;
  ListNode<T>* newnode = new ListNode<T>(item);
  newnode->_pre = itor;
  newnode->_next = itor->_next;
  itor->_next->_pre = newnode;
  itor->_next = newnode;
  this->_len++;
  return true;
}

template<typename T>
bool List<T>::insert(const T& item, int ind) {
  if (ind <= 0 || ind > this->_len + 1)
    return false;
  ListNode<T>* pmove = this->_head;
  for (int i = 1; i < ind; i++) {
    pmove = pmove->next();
  }
  this->insertAfter(item, pmove);
  return true;
}

template<typename T>
bool List<T>::erase(ListNode<T>* itor) {
  if (itor == this->_head)
    return false;
  itor->_pre->_next = itor->_next;
  itor->_next->_pre = itor->_pre;
  this->_len--;
  delete itor;
  return true;
}

template<typename T>
bool List<T>::change(const T& newitem, ListNode<T>* itor) {
  if (!itor || itor == this->_head)
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