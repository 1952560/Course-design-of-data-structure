
#include<iostream>
#include<string>
#include<algorithm>
#include"../H/Vector.h"
#include<map>

const int maxn = 1e5;

struct edge {
	std::string from;
	std::string to;
	int dist = 0;
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
	bool _flag;
};

bool cinClear(){
	if(std::cin.good()){
		return true;
	}
	std::cout<<"输入错误，请重新输入:";
	std::cin.clear();
	std::cin.ignore(INT_MAX,'\n');
	return false;
}

void System::initializeVertex() {
	_flag=false;
	_vertex.clear();
	_edge.clear();
	_par.clear();
	std::cout << "请输入顶点的个数：";
	int num;
	std::string str;
	std::cin >> num;
	while(!cinClear())
	    std::cin>>num;
	std::cout << "请依次输入各顶点的名称：" << '\n';
	while (num--) {
		std::cin >> str;
		while(!cinClear())
		    std::cin>>str;
		_vertex.push_back(str);
		_par[str] = str;
	}
	std::cout << '\n';
}

void System::addEdge() {
	edge e;
	while (true) {
		std::cout << "请输入两个顶点及边：";
		std::cin >> e.from >> e.to >> e.dist;
		if (e.from == "?" && e.to == "?" && e.dist == 0)
			break;
		_edge.push_back(e);
	}
	std::cout << '\n';
}

void System::print() {
	if(!_flag){
		std::cout<<"请运行操作C生成最小生成树！"<<'\n';
		return;
	}
	for(int i=0;i<_vertex.size()-1;i++){
		if(find(_vertex[i])!=find(_vertex[i+1])){
			std::cout<<"没有最小生成树!"<<'\n';
			return;
		}
	}
	std::cout << "最小生成树的顶点及边为：" << '\n' << '\n';
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
	_flag=true;
	_path.clear();
	for (int i = 0; i < _edge.size(); i++) {
		if (find(_edge[i].from) == find(_edge[i].to))
			continue;
		_par[find(_edge[i].from)] = find(_edge[i].to);
		_path.push_back(_edge[i]);
	}
}

void solve() {
	System sys;
	std::string num;
	while (true) {
		std::cout << "请输入操作：";
		std::cin >> num;
		while(!cinClear()){
			std::cin>>num;
		}
		while(!cinClear())
			std::cin>>num;
		if (num == "A") {
			sys.initializeVertex();
		}
		else if (num == "B") {
			sys.addEdge();
		}
		else if (num == "C") {
			std::cout << "请输入起始顶点：";
			std::string str;
			std::cin >> str;
			sys.mintree();
			std::cout << "生成Prim最小生成树！" << '\n' << '\n';
		}
		else if (num == "D") {
			sys.print();
		}
		else if (num == "E")
			break;
		else{
			std::cout<<"输入错误"<<'\n';
		}
	}
}

int main() {
	solve();
}
