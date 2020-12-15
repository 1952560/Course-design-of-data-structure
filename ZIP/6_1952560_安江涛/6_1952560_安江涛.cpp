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
		std::cout << "Input error,please re-inter!" << '\n';
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
	std::cout << "Please enter the current name of the person whose name is to be changed:";
	std::string str, name;
	std::cin >> str;
	while (!cin_check())
		std::cin >> str;
	node* r = find(root, str);
	if (!r) {
		std::cout << "No such person in the family tree！" << '\n' << '\n';
		return;
	}
	std::cout << "Please enter the changed name:";
	std::cin >> name;
	while (!cin_check())
		std::cin >> name;
	r->name = name;
	std::cout << str << "has been renamed" << name;
	std::cout << '\n' << '\n';
}

void tree::erase() {
	std::cout << "Please enter the name of the person in the family to be dissolved：";
	std::string str;
	std::cin >> str;
	while (!cin_check()) {
		std::cin >> str;
	}
	node* r = this->find(root, str);
	if (!r) {
		std::cout << "No such person in the family tree！" << '\n' << '\n';
		return;
	}
	node* p, * q;
	p = r->son;
	std::cout << "The person who wants to dissolve the family is:" << str << '\n';
	std::cout <<"The first generation of "<< str << " descendants are:";
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
	std::cout << "Please enter the name of the person to add a son (or daughter):";
	std::string str;
	std::cin >> str;
	while (!cin_check())
		std::cin >> str;
	node* r = find(root, str);
	if (!r) {
		std::cout << "No such person in the family tree！" << '\n' << '\n';
		return;
	}
	std::cout << "Please enter the name of" << str << " the newly added son (or daughter):";
	std::string name;
	std::cin >> name;
	while (!cin_check())
		std::cin >> name;
	this->insert(r, name);
	std::cout <<"The first generation of "<< str << " descendants are:";
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
	std::cout << "First build a family tree！" << '\n';
	std::cout << "Please enter the name of the ancestor:";
	std::string str;
	std::cin >> str;
	while (!cin_check())
		std::cin >> str;
	this->root->name = str;
	std::cout << "The ancestors of this family tree are:" << str << '\n' << '\n';
}

void tree::complete() {
	std::cout << "Please enter the name of the person who wants to start a family:";
	std::string str;
	std::cin >> str;
	while (!cin_check())
		std::cin >> str;
	node* r = this->find(this->root, str);
	if (!r) {
		std::cout << "The person's name is not in the family tree！" << '\n' << '\n';
		return;
	}
	int num = 0;
	std::vector<std::string> vec;
	std::cout << "Please enter the number of " << str << "'s children:";
	std::cin >> num;
	while (!cin_check())
		std::cin >> num;
	std::cout << "Please enter the names of " << str << "'s children:";
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
	std::cout << "The first generation of "<<str << "'s descendants are:";
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << "  ";
	std::cout << '\n' << '\n';
}

void solve() {
	tree genealogy;
	std::string str[8];
	str[0]="**         Family Tree Management System                **";
	str[1]="==========================================================";
	str[2]="**         Please select the action to be performed     **";
	str[3]="**          A-perfect family                            **";
	str[4]="**          B---Add family members                      **";
	str[5]="**          C---Dissolve local families                 **";
	str[6]="**          D---Change the names of family members      **";
	str[7]="**          E---Exit the program                        **";
	for(int i=0;i<8;i++)
		std::cout<<str[i]<<'\n';
	genealogy.init();
	char ch;
	while (true) {
		std::cout << "Please select the action to be performed:";
		std::cin >> ch;
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Input error,please re-input!" << '\n';
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
			std::cout << "Input error,please re-input!" << '\n' << '\n';
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
