#include<algorithm>
#include<string>
#include<iomanip>
#include"../H/bc_List.h"

const int blankspace_num = 10;
class EMIS;

class student {
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
	int _number;//学号
	std::string _name;//姓名
	std::string _sex;//性别
	int _age;//年龄
	std::string _type;//报名类型
};

std::istream& operator>>(std::istream& is, student& student) {
	is >> student._number >> student._name >> student._sex >> student._age >> student._type;
	if (is.fail()) {
		std::cout << "Input errors,please re-enter!" << '\n';
		return is;
	}
	return is;
}
std::ostream& operator<<(std::ostream& os, const student& student) {
	//os.setf(std::ios::left);
	os << std::setiosflags(std::ios::left)<< std::setw(blankspace_num) << student.number() << std::setw(blankspace_num) << student.name()
		<< std::setw(blankspace_num) << student.sex() << std::setw(blankspace_num) << student.age()
		<< std::setw(blankspace_num) << student.type() << '\n';
	return os;
}

class EMIS {
public:
	EMIS() = default;
	void push(const student& stu) { _list.push(stu); }
	bool seek();//3查找
	bool del();//2删除
	bool insert();//1插入
	void statistics() const;//5统计
	bool revise();//4修改
	const List<student>& getList() const { return this->_list; }
	void print()const;//输出
private:
	List<student> _list;
};
//EMIS stus;

void EMIS::print() const {
	//std::cout.setf(std::ios::left);
	std::cout << std::setiosflags(std::ios::left)<<std::setw(blankspace_num) << "test number" << std::setw(blankspace_num) << "name"
		<< std::setw(blankspace_num) << "sex" << std::setw(blankspace_num) << "age"
		<< std::setw(blankspace_num) << "application type" << '\n';
	ListNode<student>* itor;
	for (itor = this->_list.begin(); itor != this->_list.end(); itor = itor->next()) {
		std::cout << itor->data();
	}
}

bool EMIS::insert() {
	int place = -1;
	std::cout << "Please enter the position of the candidate you want to insert:";
	std::cin >> place;
	while (place <= 0 || place > this->_list.size() + 1) {
		std::cout << "Insertion failed, please re-enter:";
		std::cin >> place;
	}
	std::cout << "Please input the candidate number,name,gender,age and application type of the candidate to be inserted in sequence!" << '\n';
	student stu;
	std::cin >> stu;
	this->_list.insert(stu, place);
	return true;
}

bool EMIS::seek() {
	std::cout << "Please enter the candidate number of the candidate you are looking for:";
	int number = 0;
	std::cin >> number;
	ListNode<student>* itor;
	for (itor = _list.begin(); itor != _list.end(); itor = itor->next()) {
		if (itor->data().number() == number) {
			//std::cout.setf(std::ios::left);
			std::cout << std::setiosflags(std::ios::left)<< std::setw(blankspace_num) << "test number" << std::setw(blankspace_num) << "name"
				<< std::setw(blankspace_num) << "sex" << std::setw(blankspace_num) << "age"
				<< std::setw(blankspace_num) << "application type" << '\n';
			std::cout << itor->data();
			return true;
		}
	}
	if (itor == _list.end()) {
		std::cout << "The candidate information system does not have the candidate information!" << '\n';
		return false;
	}
	return false;
}

bool EMIS::del() {
	std::cout << "Please enter the candidate number of the candidate to be deleted:";
	int number = -1;
	std::cin >> number;
	ListNode<student>* itor;
	for (itor = _list.begin(); itor != _list.end(); itor = itor->next()) {
		if (itor->data().number() == number) {
			student s = itor->data();
			std::cout << "The candidate information you deleted is:" << s;
			_list.erase(itor);
			return true;
		}
	}
	if (itor == _list.end()) {
		std::cout << "Failed to delete!" << '\n';
		return false;
	}
	return false;
}

void EMIS::statistics()const {
	print();
}

bool EMIS::revise() {
	std::cout << "Please enter the candidate number of the candidate to be modified:";
	int number = 0;
	std::cin >> number;
	ListNode<student>* itor;
	for (itor = _list.begin(); itor != _list.end(); itor = itor->next()) {
		if (itor->data().number() == number) {
			std::cout << "Please enter the name,gender,age and application type of the candidate to be modified!" << '\n';
			student a;
			std::cin >> a._name >> a._sex >> a._age >> a._type;
			a._number = number;
			_list.change(a, itor);
			return true;
		}
	}
	if (itor == _list.end()) {
		std::cout << "The candidate information system does not have the candidate information!" << '\n';
		return false;
	}
	return false;
}

void solve() {
	EMIS stus;
	std::cout << "First, please establish a candidate information system!" << '\n';
	int num = 0;
	std::cout << "Please enter the number of candidates:";
	std::cin >> num;
	while (num < 0) {
		std::cout << "Please enter a natural number:";
		std::cin >> num;
	}
	std::cout << "Please enter the candidate's exam number,name,gender,age and application type in turn!" << '\n';
	for (int i = 1; i <= num;) {
		student stu;
		std::cin >> stu;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		else {
			stus.push(stu); i++;
		}
	}
	std::cout << '\n';
	stus.print();
	std::cout << "Please select the operation you want to perform (1 means insert,2 means delete,3 means search,4 means modify,5 means statistics,0 means cancel operation)" << '\n' << '\n';
	while (true)
	{
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		int order = 6;
		std::cout << "Please choose what you want to do:";
		std::cin >> order;
		if (order < 0 || order>5) {
			std::cout << "Input errors, please re-enter" << '\n';
			continue;
		}
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Input errors, please re-enter" << '\n';
			continue;
		}
		if (order == 1) {
			stus.insert();
			std::cout << '\n';
			stus.print();
		}
		else if (order == 2) {
			stus.del();
			std::cout << '\n';
			stus.print();
		}
		else if (order == 3) {
			stus.seek();
			std::cout << '\n';
		}
		else if (order == 4) {
			stus.revise();
			std::cout << '\n';
			stus.print();
		}
		else if (order == 5) {
			stus.statistics();
		}
		else if (order == 0)
			break;
	}
}

int main() {
	solve();
}
