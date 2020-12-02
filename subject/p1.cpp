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
  int _number;//ѧ��
  std::string _name;//����
  std::string _sex;//�Ա�
  int _age;//����
  std::string _type;//��������
};

std::istream& operator>>(std::istream& is, student& student){
  is >> student._number >> student._name >> student._sex >> student._age >> student._type;
  if (is.fail()){
    std::cout << "����������������룡" << '\n';
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
  bool seek();//3����
  bool del();//2ɾ��
  bool insert();//1����
  void statistics() const;//5ͳ��
  bool revise();//4�޸�
  const List<student>& getList() const { return this->_list; }
  void print()const;//���
private:
  List<student> _list;
};
//EMIS stus;

void EMIS::print() const {
  std::cout.setf(std::ios::left);
  std::cout << std::setw(blankspace_num) << "����" << std::setw(blankspace_num) << "����"
    << std::setw(blankspace_num) << "�Ա�" << std::setw(blankspace_num) << "����"
    << std::setw(blankspace_num) << "��������" << '\n';
  ListNode<student>* itor;
  for (itor = this->_list.begin(); itor != this->_list.end(); itor = itor->next()) {
    std::cout << itor->data();
  }
}

bool EMIS::insert(){
  int place = -1;
  std::cout << "��������Ҫ����Ŀ�����λ�ã�";
  std::cin >> place;
  while (place <= 0 || place > this->_list.size() + 1) {
    std::cout << "����ʧ�ܣ����������룺" ;
    std::cin >> place;
  }
  std::cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������ͣ�" << '\n';
  student stu;
  std::cin >> stu;
  this->_list.insert(stu, place);
  return true;
}

bool EMIS::seek(){
  std::cout << "������Ҫ���ҵĿ����Ŀ���:";
  int number = 0;
  std::cin >> number;
  ListNode<student>* itor;
  for (itor = _list.begin(); itor != _list.end(); itor = itor->next()){
    if (itor->data().number() == number){
      std::cout.setf(std::ios::left);
      std::cout << std::setw(blankspace_num) << "����" << std::setw(blankspace_num) << "����"
        << std::setw(blankspace_num) << "�Ա�" << std::setw(blankspace_num) << "����"
        << std::setw(blankspace_num) << "��������" << '\n';
      std::cout << itor->data();
      return true;
    }
  }
  if (itor == _list.end()) {
    std::cout << "������Ϣϵͳ�޸ÿ�����Ϣ" << '\n';
    return false;
  }
  return false;
}

bool EMIS::del(){
  std::cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
  int number = -1;
  std::cin >> number;
  ListNode<student>* itor;
  for (itor = _list.begin(); itor != _list.end(); itor = itor->next()){
    if (itor->data().number() == number){
      student s = itor->data();
      std::cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << s;
      _list.erase(itor);
      return true;
    }
  }
  if (itor == _list.end()) {
    std::cout << "ɾ��ʧ��" << '\n';
    return false;
  }
  return false;
}

void EMIS::statistics()const{
  print();
}

bool EMIS::revise(){
  std::cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
  int number = 0;
  std::cin >> number;
  ListNode<student>* itor;
  for (itor = _list.begin(); itor != _list.end(); itor = itor->next()){
    if (itor->data().number() == number){
      std::cout << "������Ҫ�޸ĵĿ������������Ա����估�������ͣ�" << '\n';
      student a;
      std::cin >> a._name >> a._sex >> a._age >> a._type;
      a._number = number;
      _list.change(a, itor);
      return true;
    }
  }
  if (itor == _list.end()) {
    std::cout << "������Ϣϵͳ�޸ÿ�����Ϣ" << '\n';
    return false;
  }
  return false;
}

void solve(){
  EMIS stus;
  std::cout << "�����뽨��������Ϣϵͳ��" << '\n';
  int num = 0;
  std::cout << "�����뿼������:";
  std::cin >> num;
  while (num < 0) {
      std::cout << "������һ����Ȼ����";
      std::cin >> num;
  }
  std::cout << "���������뿼���Ŀ��ţ��������Ա����估�������ͣ�" << '\n';
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
  std::cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << '\n' << '\n';
  while (true)
  {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(100, '\n');
    }
    int order = 6;
    std::cout << "��ѡ����Ҫ���еĲ�����";
    std::cin >> order;
    if (order < 0 || order>5) {
      std::cout << "�����������������" << '\n';
      continue;
    }
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(100, '\n');
      std::cout << "�����������������" << '\n';
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
      std::cout << '\n';
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
