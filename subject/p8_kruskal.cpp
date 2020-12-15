
#include<iostream>
#include<string>
#include<algorithm>
#include"../H/Vector.h"
#include<map>
#include<limits.h>

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
	bool exist(std::string str);
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

bool System::exist(std::string str){
	auto i=_vertex.begin();
	while(i!=_vertex.end()){
		if(*i==str)
			return true;
		i++;
	}
	return false;
}

bool cinClear(){
	if(std::cin.good()){
		return true;
	}
	std::cout<<"Input errors, please re-enter:";
	std::cin.clear();
	std::cin.ignore(INT_MAX,'\n');
	return false;
}

void System::initializeVertex() {
	_flag=false;
	_vertex.clear();
	_edge.clear();
	_par.clear();
	std::cout << "Please enter the number of vertices：";
	int num;
	std::string str;
	std::cin >> num;
	while(!cinClear())
	    std::cin>>num;
	std::cout << "Please enter the name of each vertex in turn：" << '\n';
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
		std::cout << "Please enter two vertices and edges：";
		std::cin >> e.from >> e.to >> e.dist;
		if (e.from == "?" && e.to == "?" && e.dist == 0)
			break;
		_edge.push_back(e);
	}
	std::cout << '\n';
}

void System::print() {
	if(!_flag){
		std::cout<<"Please run operation C to generate a minimum spanning tree！"<<'\n';
		return;
	}
	for(int i=0;i<_vertex.size()-1;i++){
		if(find(_vertex[i])!=find(_vertex[i+1])){
			std::cout<<"No minimum spanning tree!"<<'\n';
			return;
		}
	}
	std::cout << "The vertices and edges of the minimum spanning tree are：" << '\n' << '\n';
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
	std::string str[7];
	str[0]="**         Power grid cost simulation system        **";
	str[1]="======================================================";
	str[2]="**          A---Create grid vertex                  **";
	str[3]="**          B---Add the edge of the grid            **";
	str[4]="**          C---Build a minimum spanning tree       **";
	str[5]="**          D---Show minimum spanning tree          **";
	str[6]="**          E---exit the program                    **";
	for(int i=0;i<7;i++)
		std::cout<<str[i]<<'\n';
	System sys;
	std::string num;
	while (true) {
		std::cout << "Please enter operation：";
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
			std::cout << "Please enter the starting vertex：";
			std::string str;
			std::cin >> str;
			while(!sys.exist(str)){
				std::cout<<"The grid vertex set does not exist"<<str<<",please enter again:";
				std::cin>>str;
			}
			sys.mintree();
			std::cout << "Generate Prim minimum spanning tree！" << '\n' << '\n';
		}
		else if (num == "D") {
			sys.print();
		}
		else if (num == "E")
			break;
		else{
			std::cout<<"Input error"<<'\n';
		}
	}
}

int main() {
	solve();
}
