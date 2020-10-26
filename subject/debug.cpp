#include<iostream>
#include<string>
#include<algorithm>
#include"../H/Vector.h"
#include<vector>
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

class system {
public:
  std::string find(std::string x) {
    return _par[x] == x ? x : _par[x] = find(_par[x]);
  }
  void mintree(){
    std::sort(_edge.begin() ,_edge.end());
    std::map<std::string, std::string>::iterator iter;
    for (iter = _par.begin(); iter != _par.end(); iter++) {
      iter->second = iter->first;
    }
    for (int i = 0; i < _edge.size(); i++) {
      if(find(_edge[i].from)==find(_edge[i].to))
        continue;
      _par[find(_edge[i].from)] = find(_edge[i].to);
      _path.push_back(_edge[i]);
    }
  }
private:
  Vector<std::string> _vertex;
  Vector<edge> _edge;
  std::map<std::string, std::string> _par;
  Vector<edge> _path;
};