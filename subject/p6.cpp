#include<iostream>
#include<vector>
#include<stack>
#include<cmath>
#include<limits.h>
struct node {
	node() {
		parent = son = brother = nullptr;
	}
	std::string name;//存名字
	node* parent;//存父节点
	node* son;//存儿子
	node* brother;//存兄弟
};

class tree {
public:
	tree() :root(new node()) {}
	tree(node* r) :root(r) {}
	~tree() { clear(this->root); }

	node* get_root()const { return this->root; }
	void init();
	void complete();
	void add();
	void change();
	void clear(node* r);
	void erase();
	void print(node* r, int deep, std::vector<int> width);

private:
	bool cin_check();//恢复cin
	void insert(node* r, std::string str);
	node* find(node* r, std::string str);

private:
	node* root;
	std::vector<int> width;
};

bool tree::cin_check() {
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "input error,please re-inter!" << '\n';
		return false;
	}
	return true;
}


void tree::print(node* r, int deep, std::vector<int> width) {
	if (!r)
		return;
	int d = deep;

	while (d--)
		std::cout << ' ';
	if (r != this->root) {
		if (r->brother)
			std::cout << "┣" << "  ";
		else
			std::cout << "┗" << "  ";
	}
	std::cout << r->name << '\n';
	r = r->son;
	while (r) {
		int new_deep = deep;
		if (deep == 0)
			new_deep += std::ceil(r->name.size() / 2);
		else
			new_deep += std::ceil(r->name.size() / 2) + 2;
		width.push_back(new_deep);
		print(r, new_deep, width);
		if (!width.empty())
			width.pop_back();
		r = r->brother;
	}
}

void tree::change() {
	std::cout << "请输入要更改姓名的人的目前姓名:";
	std::string str, name;
	std::cin >> str;
	while (!cin_check())
		std::cin >> str;
	node* r = find(root, str);
	if (!r) {
		std::cout << "家谱中没有此人！" << '\n' << '\n';
		return;
	}
	std::cout << "请输入更改后的姓名:";
	std::cin >> name;
	while (!cin_check())
		std::cin >> name;
	r->name = name;
	std::cout << str << "已更名为" << name;
	std::cout << '\n' << '\n';
}

void tree::erase() {
	std::cout << "请输入要解散的家庭的人的姓名：";
	std::string str;
	std::cin >> str;
	while (!cin_check()) {
		std::cin >> str;
	}
	node* r = this->find(root, str);
	if (!r) {
		std::cout << "家谱中没有此人！" << '\n' << '\n';
		return;
	}
	node* p, * q;
	p = r->son;
	std::cout << "要解散家庭的人是:" << str << '\n';
	std::cout << str << "的第一代子孙是:";
	while (p) {
		std::cout << p->name << "  ";
		q = p->brother;
		delete p;
		p = q;
	}
	r->son = nullptr;
	std::cout << '\n' << '\n';
}

void tree::add() {
	std::cout << "请输入要添加儿子（或女儿）的人的姓名:";
	std::string str;
	std::cin >> str;
	while (!cin_check())
		std::cin >> str;
	node* r = find(root, str);
	if (!r) {
		std::cout << "家谱中没有此人！" << '\n' << '\n';
		return;
	}
	std::cout << "请输入" << str << "新添加的儿子（或女儿）的姓名:";
	std::string name;
	std::cin >> name;
	while (!cin_check())
		std::cin >> name;
	this->insert(r, name);
	std::cout << str << "的第一代子孙是:";
	r = r->son;
	while (r) {
		std::cout << r->name << "  ";
		r = r->brother;
	}
	std::cout << '\n' << '\n';
}

void tree::insert(node* r, std::string str) {
	if (!r)
		return;
	if (!r->son) {
		r->son = new node();
		r->son->name = str;
		r->son->parent = r;
	}
	else {
		r = r->son;
		while (r->brother)
			r = r->brother;
		r->brother = new node();
		r->brother->name = str;
	}
}

void tree::clear(node* r) {
	if (!r)
		return;
	node* q = r->son;
	delete r;
	while (q) {
		node* p = q->brother;
		clear(q);
		q = p;
	}
}

node* tree::find(node* r, std::string str) {
	node* ans = new node();
	ans = nullptr;
	if (!r)
		return ans;
	if (r->name == str)
		return r;
	else {
		node* q = r->son;
		while (q && !(ans = find(q, str)))
			q = q->brother;
	}
	return ans;
}

void tree::init() {
	std::cout << "首先建立一个家谱！" << '\n';
	std::cout << "请输入祖先的名字:";
	std::string str;
	std::cin >> str;
	while (!cin_check())
		std::cin >> str;
	this->root->name = str;
	std::cout << "此家谱的祖先是:" << str << '\n' << '\n';
}

void tree::complete() {
	std::cout << "请输入要建立家庭的人的名字:";
	std::string str;
	std::cin >> str;
	while (!cin_check())
		std::cin >> str;
	node* r = this->find(this->root, str);
	if (!r) {
		std::cout << "家谱中没有此人的名字！" << '\n' << '\n';
		return;
	}
	int num = 0;
	std::vector<std::string> vec;
	std::cout << "请输入" << str << "的儿女人数:";
	std::cin >> num;
	while (!cin_check())
		std::cin >> num;
	std::cout << "请依次输入" << str << "的儿女的名字:";
	while (num--) {
		std::string name;
		std::cin >> name;
		while (!cin_check())
			std::cin >> name;
		vec.push_back(name);
	}
	for (int i = 0; i < vec.size(); i++) {
		this->insert(r, vec[i]);
	}
	std::cout << str << "的第一代子孙是:";
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << "  ";
	std::cout << '\n' << '\n';
}

void solve() {
	tree genealogy;
	std::string str[8];
	str[0]="**			家谱管理系统			**";
	str[1]="===============================================";
	str[2]="**		请选择要执行的操作：			 **";
	str[3]="**			A---完善家谱			**";
	str[4]="**			B---添加家庭成员		**";
	str[5]="**			C---解散局部家庭		**";
	str[6]="**			D---更改家庭成员姓名	 	**";
	str[7]="**			E---退出程序			**";
	for(int i=0;i<8;i++)
		std::cout<<str[i]<<'\n';
	genealogy.init();
	char ch;
	while (true) {
		std::cout << "请选择要执行的操作:";
		std::cin >> ch;
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "input error,please re-input!" << '\n';
		}
		if (ch == 'E')
			break;
		switch (ch) {
		case 'A': {
			genealogy.complete();
			break;
		}
		case 'B': {
			genealogy.add();
			break;
		}
		case 'C': {
			genealogy.erase();
			break;
		}
		case 'D': {
			genealogy.change();
			break;
		}
		case 'F': {
			std::vector<int> v;
			// v.push_back(0);
			genealogy.print(genealogy.get_root(), 0, v);
			std::cout << '\n' << '\n';
			break;
		}
		default: {
			std::cout << "input error,please re-input!" << '\n' << '\n';
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		}
	}
}

int main() {
	solve();
	//std::cout << "┃" << '\n';
	//std::cout << "┗";
}
