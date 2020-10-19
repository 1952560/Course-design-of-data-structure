#include"../H/cl_List.h"
int main()
{
  List<int> list1, list2,list3;
  int item = 0;
  while (true) {
    std::cin >> item;
    if (item == -1)
      break;
    list1.push(item);
  }
  while (true) {
    std::cin >> item;
    if (item == -1)
      break;
    list2.push(item);
  }
  ListNode<int>* itor1 = list1.begin();
  ListNode<int>* itor2 = list2.begin();
  while (itor1 != list1.end() && itor2 != list2.end()) {
    if (itor1->data() == itor2->data()) {
      list3.push(itor1->data() );
      itor1 = itor1->next(); itor2 = itor2->next();
    }
    else if (itor1->data() < itor2->data()) {
      itor1 = itor1->next();
    }
    else if (itor1->data() > itor2->data()) {
      itor2 = itor2->next();
    }
  }
  list3.print();
}