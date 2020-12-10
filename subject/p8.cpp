#include<unordered_map>
#include<iostream>
#include<string>
#include<algorithm>
#include"../H/Vector.h"
#include<map>
#include<cstring>
#include<vector>

const int maxn = 1e2;
const int INF = 1e9 + 7;

struct edge {
	edge(std::string f,std::string t,int d){
		from=f;to=t;dist=d;
	}
	edge(){from=to=" ";dist=INF;}
	std::string from;
	std::string to;
	int dist = 0;
	bool operator < (const edge& rhs)const {
		return dist < rhs.dist;
	}
};

bool cinClear(){
	if(std::cin.good())
		return true;
	std::cout<<"输入错误，请重新输入:";
	std::cin.clear();
	std::cin.ignore();
	return false;
}

class System {
public:
	std::string find(std::string x) {
		return _par[x] == x ? x : _par[x] = find(_par[x]);
	}
	void prim(std::string str);
	void initializeVertex();
	void addEdge();
	void print();
private:
    int _size=0;
	bool _flag;//是否进行了操作C
	bool _exist;//是否存在最小生成树
	std::vector<std::string> _vertex;//顶点集
	std::vector<edge> _path;//存路径
	std::unordered_map<std::string, int> _map;//映射
	int _graph[maxn][maxn];
	bool _visit[maxn];//判断顶点有没有访问过
	std::map<std::string, std::string> _par;
};

void System::initializeVertex() {
	_par.clear();
	_flag=false;
	_exist=false;
	_vertex.clear();//清空顶点
	_map.clear();//清空映射
	std::cout << "请输入顶点的个数：";
	int num;
	std::string str;
	std::cin >> num;
	while(!cinClear()||num<2){
		if(num<2)
			std::cout<<"输入错误，请重新输入:";
		std::cin>>num;
	}
	_size=num;
	std::cout << "请依次输入各顶点的名称：" << '\n';
	for (int i = 0; i < num; i++) {
		std::cin >> str;
		while(!cinClear())
			std::cin>>str;
		_vertex.push_back(str);
		_map[str] = i;
		_par[str]=str;
	}
	for(int i=0;i<_size;i++)
	    for(int j=0;j<_size;j++)
		    _graph[i][j]=INF;
	std::cout << '\n';
}

void System::addEdge() {
	edge e;
	while (true) {
		std::cout << "请输入两个顶点及边：";
		std::cin >> e.from >> e.to >> e.dist;
		if (e.from == "?" && e.to == "?" && e.dist == 0)
			break;
		_graph[_map[e.from]][_map[e.to]]=e.dist;
		_graph[_map[e.to]][_map[e.from]]=e.dist;
		_par[find(e.from)]=find(e.to);
	}
	std::cout << '\n';
}

void System::prim(std::string str) {
	_flag=true;
	for(int i=0;i<_size-1;i++){
		if(find(_vertex[i])!=find(_vertex[i+1])){
			_exist=false;
			return;
		}
	}
	int cur=_map[str];
	_path.clear();
	_flag=true;
	for(int i=0;i<_size;i++)
		_visit[i]=false;
	_visit[cur]=false;
	int index=cur;
	int dist[maxn]={0};
	for(int i=0;i<_size;i++)
	    dist[i]=_graph[cur][i];
	for(int i=1;i<_size;i++){
		int minor=INF;
		for(int j=0;j<_size;j++){
			if(!_visit[j]&&dist[j]<minor){
				minor=dist[j];
				index=j;
			}
		}
	    _visit[index]=true;
     	_path.push_back(edge(_vertex[cur],_vertex[index],minor));
    	for(int j=0;j<_size;j++){
	    	if(!_visit[j]&&dist[j]>_graph[index][j])
		        dist[j]=_graph[index][j];
		}
		cur=index;
	}
	_exist=true;
}

void System::print() {
	if(!_flag){
		std::cout<<"请输入操作C生成最小生成树!"<<'\n';
		return;
	}
	if(!_exist){
		std::cout<<"不存在最小生成树!"<<'\n';
		return;
	}
	std::cout << "最小生成树的顶点及边为：" << '\n' << '\n';
	for (int i = 0; i < _path.size(); i++) {
		std::cout << _path[i].from << "-<" << _path[i].dist << ">->" << _path[i].to;
		std::cout << "     ";
	}
	std::cout << '\n';
}

void solve() {
	System sys;
	std::string num;
	while (true) {
		std::cout << "请输入操作：";
		std::cin >> num;
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
			sys.prim(str);
			std::cout << "生成Prim最小生成树！" << '\n' << '\n';
		}
		else if (num == "D") {
			sys.print();
		}
		else if (num == "E")
			break;
		else
			std::cout<<"输入错误!"<<'\n';
	}
}

int main() {
	solve();
}
