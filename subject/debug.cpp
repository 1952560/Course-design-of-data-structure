#include<iostream>
#include<string>
#include<algorithm>
#include"../H/Vector.h"
#include<map>

const int maxn = 1e5;

struct edge {
  std::string from;
  std::string to;
  int dist;
  bool operator < (const edge& rhs)const {
    return dist < rhs.dist;
  }
};

class System {
public:
  std::string find(std::string x) {
    return _par[x] == x ? x : _par[x] = find(_par[x]);
  }
  void mintree();
  void initializeVertex();
  void addEdge();
  void print();
private:
  Vector<std::string> _vertex;
  Vector<edge> _edge;
  std::map<std::string, std::string> _par;
  Vector<edge> _path;
};

void System::initializeVertex() {
  _vertex.clear();
  std::cout << "�����붥��ĸ��飺";
  int num;
  std::string str;
  std::cin >> num;
  std::cout << "�������������������ƣ�" << '\n';
  while (num--) {
    std::cin >> str;
    _vertex.push_back(str);
    _par[str] = str;
  }
  std::cout << '\n';
}

void System::addEdge() {
  edge e;
  while (true) {
    std::cout << "�������������㼰�ߣ�";
    std::cin >> e.from >> e.to >> e.dist;
    if (e.from == "?" && e.to == "?" && e.dist == 0)
      break;
    _edge.push_back(e);
  }
  std::cout << '\n';
}

void System::print() {
  std::cout << "��С�������Ķ��㼰��Ϊ��" << '\n' << '\n';
  for (int i = 0; i < _path.size(); i++) {
    std::cout << _path[i].from << "-<" << _path[i].dist << ">->" << _path[i].to;
    std::cout << "     ";
  }
  std::cout << '\n';
}

void System::mintree() {
  std::sort(_edge.begin(), _edge.end());
  std::map<std::string, std::string>::iterator iter;
  for (iter = _par.begin(); iter != _par.end(); iter++) {
    iter->second = iter->first;
  }
  _path.clear();
  for (int i = 0; i < _edge.size(); i++) {
    if (find(_edge[i].from) == find(_edge[i].to))
      continue;
    _par[find(_edge[i].from)] = find(_edge[i].to);
    _path.push_back(_edge[i]);
  }
}

void solve(){
  System sys;
  std::string num;
  while (true) {
    std::cout << "�����������";
    std::cin >> num;
    if (num == "A") {
      sys.initializeVertex();
    }
    else if (num == "B") {
      sys.addEdge();
    }
    else if (num == "C") {
      std::cout << "��������ʼ���㣺";
      std::string str;
      std::cin >> str;
      sys.mintree();
      std::cout << "����Prim��С��������" << '\n' << '\n';
    }
    else if (num == "D") {
      sys.print();
    }
    else if (num == "E")
      break;
  }
}

int main() {
  solve();
}