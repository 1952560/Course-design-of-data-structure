#include<unordered_map>
#include<iostream>
#include<string>
#include<algorithm>
#include"../H/Vector.h"
#include<map>
#include<cstring>

const int maxn = 1e3;
const int INF = 1e9 + 7;

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
	void prim(int cur);
	void initializeVertex();
	void addEdge();
	void print();
private:
	Vector<std::string> _vertex;//顶点集
	Vector<edge> _path;//存
	std::unordered_map<std::string, int> _map;
	int _dist[maxn][maxn];
	bool _visit[maxn];
};

void System::initializeVertex() {
	_vertex.clear();
	_map.clear();
	std::cout << "请输入顶点的个数：";
	int num;
	std::string str;
	std::cin >> num;
	std::cout << "请依次输入各顶点的名称：" << '\n';
	for (int i = 0; i < num; i++) {
		std::cin >> str;
		_vertex.push_back(str);
		_map[str] = i;
	}
	for (int i = 0; i < num; i++)
		for (int j = 0; j < num; j++)
			_dist[i][j] = INF;
	std::cout << '\n';
}

void System::addEdge() {
	edge e;
	while (true) {
		std::cout << "请输入两个顶点及边：";
		std::cin >> e.from >> e.to >> e.dist;
		if (e.from == "?" && e.to == "?" && e.dist == 0)
			break;
		_dist[_map[e.from]][_map[e.to]] = e.dist;
		_dist[_map[e.to]][_map[e.from]] = e.dist;
	}
	std::cout << '\n';
}

void System::prim(int cur) {
	int index = cur;
	memset(_visit, false, sizeof(_visit));
	_visit[cur] = true;

}

void System::print() {
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
			//sys.mintree();
			std::cout << "生成Prim最小生成树！" << '\n' << '\n';
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
