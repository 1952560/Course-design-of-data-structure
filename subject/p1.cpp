#include<algorithm>
#include<string>
#include<iomanip>
#include"../H/bc_List.h"

const int blankspace_num = 10;
class EMIS;

class student{
public:
  student() = default;
  friend class EMIS;
  friend std::istream& operator>>(std::istream& is, student& student);
  friend std::ostream& operator<<(std::ostream& os, const student& student);
  const int number()const { return _number; }
  const std::string name()const { return _name; }
  const std::string sex()const { return _sex; }
  const int age()const { return _age; }
  const std::string type()const { return _type; }
  void set(int number, std::string name, std::string sex, int age, std::string type) {
    _number = number; _name = name; _sex = sex; _age = age; _type = type;
  }
private:
  int _number;
  std::string _name;
  std::string _sex;
  int _age;
  std::string _type;//
};

std::istream& operator>>(std::istream& is, student& student){
  is >> student._number >> student._name >> student._sex >> student._age >> student._type;
  if (is.fail()){
    std::cout << "输入错误，请重新输入！" << '\n';
    return is;
  }
  return is;
}
std::ostream& operator<<(std::ostream& os, const student& student){
  os.setf(std::ios::left);
  os << std::setw(blankspace_num) << student.number() << std::setw(blankspace_num) << student.name()
    << std::setw(blankspace_num) << student.sex() << std::setw(blankspace_num) << student.age()
    << std::setw(blankspace_num) << student.type() << '\n';
  return os;
}

class EMIS{
public:
  EMIS() = default;
  void push(const student& stu) { _list.push(stu); }
  bool seek();//3
  bool del();//2
  bool insert();//1
  void statistics() const;//5
  bool revise();
  const List<student>& getList() const { return this->_list; }
  void print()const;
private:
  List<student> _list;
};
//EMIS stus;

void EMIS::print() const {
  std::cout.setf(std::ios::left);
  std::cout << std::setw(blankspace_num) << "考号" << std::setw(blankspace_num) << "姓名"
    << std::setw(blankspace_num) << "性别" << std::setw(blankspace_num) << "年龄"
    << std::setw(blankspace_num) << "报考类型" << '\n';
  ListNode<student>* itor;
  for (itor = this->_list.begin(); itor != this->_list.end(); itor = itor->next()) {
    std::cout << itor->data();
  }
}

bool EMIS::insert(){
  int place = -1;
  std::cout << "请输入你要插入的考生的位置：";
  std::cin >> place;
  if (place <= 0 || place > this->_list.size() + 1) {
    std::cout << "插入失败" << '\n';
    return false;
  }
  std::cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类型！" << '\n';
  student stu;
  std::cin >> stu;
  this->_list.insert(stu, place);
  return true;
}

bool EMIS::seek(){
  std::cout << "请输入要查找的考生的考号:";
  int number = 0;
  std::cin >> number;
  ListNode<student>* itor;
  for (itor = _list.begin(); itor != _list.end(); itor = itor->next()){
    if (itor->data().number() == number){
      std::cout.setf(std::ios::left);
      std::cout << std::setw(blankspace_num) << "考号" << std::setw(blankspace_num) << "姓名"
        << std::setw(blankspace_num) << "性别" << std::setw(blankspace_num) << "年龄"
        << std::setw(blankspace_num) << "报考类型" << '\n';
      std::cout << itor->data();
      return true;
    }
  }
  if (itor == _list.end()) {
    std::cout << "考生信息系统无该考生信息" << '\n';
    return false;
  }
  return false;
}

bool EMIS::del(){
  std::cout << "请输入要删除的考生的考号：";
  int number = -1;
  std::cin >> number;
  ListNode<student>* itor;
  for (itor = _list.begin(); itor != _list.end(); itor = itor->next()){
    if (itor->data().number() == number){
      student s = itor->data();
      std::cout << "你删除的考生信息是：" << s;
      _list.erase(itor);
      return true;
    }
  }
  if (itor == _list.end()) {
    std::cout << "删除失败" << '\n';
    return false;
  }
  return false;
}

void EMIS::statistics()const{
  print();
}

bool EMIS::revise(){
  std::cout << "请输入要修改的考生的考号：";
  int number = 0;
  std::cin >> number;
  ListNode<student>* itor;
  for (itor = _list.begin(); itor != _list.end(); itor = itor->next()){
    if (itor->data().number() == number){
      std::cout << "请输入要修改的考生的姓名，性别，年龄及报考类型！" << '\n';
      student a;
      std::cin >> a._name >> a._sex >> a._age >> a._type;
      a._number = number;
      _list.change(a, itor);
      return true;
    }
  }
  if (itor == _list.end()) {
    std::cout << "考生信息系统无该考生信息" << '\n';
    return false;
  }
  return false;
}

void solve(){
  EMIS stus;
  std::cout << "首先请建立考生信息系统！" << '\n';
  int num = 0;
  std::cout << "请输入考生人数:";
  std::cin >> num;
  std::cout << "请依次输入考生的考号，姓名，性别，年龄及报考类型！" << '\n';
  for (int i = 1; i <= num;){
    student stu;
    std::cin >> stu;
    if (std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(100, '\n');
    }
    else{
      stus.push(stu); i++;
    }
  }
  std::cout << '\n';
  stus.print();
  std::cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << '\n' << '\n';
  while (true)
  {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(100, '\n');
    }
    int order = 6;
    std::cout << "请选择您要进行的操作：";
    std::cin >> order;
    if (order < 0 || order>5) {
      std::cout << "输入错误，请重新输入" << '\n';
      continue;
    }
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(100, '\n');
      std::cout << "输入错误，请重新输入" << '\n';
      continue;
    }
    if (order == 1){
      stus.insert();
      std::cout << '\n';
      stus.print();
    }
    else if (order == 2){
      stus.del();
      std::cout << '\n';
      stus.print();
    }
    else if (order == 3){
      stus.seek();
    }
    else if (order == 4){
      stus.revise();
      std::cout << '\n';
      stus.print();
    }
    else if (order == 5){
      stus.statistics();
    }
    else if (order == 0)
      break;
  }
}

int main(){
  solve();
}
