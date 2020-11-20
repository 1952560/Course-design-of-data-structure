#include<iostream>
#include<vector>
#include<stack>

struct node {
  node() {
    parent = son = brother = nullptr;
  }
  std::string name;
  node* parent;
  node* son;
  node* brother;
};

class tree {
public:
  tree():root(new node()){}
  tree(node* r):root(r){}
  ~tree() { clear(this->root); }

  node* get_root()const { return this->root; }
  void init();
  void complete();
  void add();
  void change();
  void clear(node* r);
  void erase();
  void print(node* r);
  void new_print(node* r,int deep=0);

private:
  void insert(node* r, std::string str);
  node* find(node* r, std::string str);

private:
  node* root;
  std::vector<int> width;
};

void tree::new_print(node* r,int deep=0){
  if (r == this->root) {
    std::cout << r->name;
    this->width.push_back(r->name.size()/2+1);
    if (r->son) {
      for (int i : width) {
        while (i--)
          std::cout << " ";
        std::cout << "|";
      }
    }
  }
  else {

  }
  r = r->son;
  while (r) {

  }
}

void tree::print(node* r) {
  if (!r)
    return;
  std::cout << r->name << "  ";
  r = r->son;
  while (r) {
    print(r);
    r = r->brother;
  }
}

void tree::change(){
  std::cout << "请输入要更改姓名的人的目前姓名:";
  std::string str,name;
  std::cin >> str;
  node* r = find(root, str);
  std::cout << "请输入更改后的姓名:";
  std::cin >> name;
  r->name = name;
  std::cout << str << "已更名为" << name;
  std::cout << '\n'<<'\n';
}

void tree::erase() {
  std::cout << "请输入要解散的家庭的人的姓名：";
  std::string str;
  std::cin >> str;
  node* r = new node();
  r = this->find(root, str);
  node *p, *q;
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
  std::cout << "请输入" << str << "新添加的儿子（或女儿）的姓名:";
  std::string name;
  std::cin >> name;
  node* r = new node();
  r = find(root, str);
  this->insert(r, name);
  std::cout << str << "的第一代子孙是:";
  r = r->son;
  while (r) {
    std::cout << r->name << "  ";
    r = r->brother;
  }
  std::cout << '\n'<<'\n';
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

node* tree::find(node* r,std::string str) {
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
  this->root->name = str;
  std::cout << "此家谱的祖先是:" << str << '\n' << '\n';
}

void tree::complete() {
  std::cout << "请输入要建立家庭的人的名字:";
  std::string str;
  std::cin >> str;
  node* r = new node();
  r = this->find(this->root,str);
  int num = 0;
  std::vector<std::string> vec;
  std::cout << "请输入" << str << "的儿女人数:";
  std::cin >> num;
  std::cout << "请依次输入" << str << "的儿女的名字:";
  while (num--) {
    std::string name;
    std::cin >> name;
    vec.push_back(name);
  }
  for (int i = 0; i < vec.size(); i++) {
    this->insert(r, vec[i]);
  }
  std::cout << str << "的第一代子孙是:";
  for (int i = 0; i < vec.size(); i++)
    std::cout << vec[i] << "  ";
  std::cout << '\n'<<'\n';
}

void solve() {
  tree genealogy;
  genealogy.init();
  char ch;
  while (true) {
    std::cout << "请选择要执行的操作:";
    std::cin >> ch;
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
    case'F': {
      genealogy.print(genealogy.get_root());
      std::cout << '\n' << '\n';
    }
    }
  }
}

int main() {
 // solve();
  int a = 1, b = 2;
  std::cout << (a ^ b) << (a & b);
}