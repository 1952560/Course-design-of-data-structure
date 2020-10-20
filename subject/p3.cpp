#include<string>
#include<iomanip>
#include"../H/Vector.h"


const int maxn = 1e3;

int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };

class maze
{
public:
  maze() :_row(0), _col(0) {
    _entrancex = _entrancey = -1;
    _exitx = _exity = -1;
    _pathnum = 0;
  }
  void set();
  void setMaze();
  bool setEntrance();
  bool setExit();
  void mapPrintf();//输出迷宫地图
  void pathPrint();//输出路径
  void dfs(int x, int y);
  void init() {
    for (int i = 0; i < _row; i++) {
      for (int j = 0; j < _col; j++) {
        done[i].push_back(false);
      }
    }
  }

private:
  int _row, _col;//行和列,从0开始
  int _entrancex, _entrancey;
  int _exitx, _exity;
  std::string _maze[maxn];
  Vector<bool> done[maxn];
  Vector<std::pair<int, int> > path[10];
  Vector<std::pair<int, int> > tpath;
  int _pathnum;
};

bool maze::setEntrance() {
  int row = -1, col = -1;
  std::cout << "请输入迷宫的入口:";
  std::cin >> row >> col;
  std::cout << '\n';
  if (row < 0 || row >= _row || col < 0 || col >= _col)
    return false;
  _entrancex = row; _entrancey = col;
  return true;
}

bool maze::setExit() {
  int row = -1, col = -1;
  std::cout << "请输入迷宫的出口：";
  std::cin >> row >> col;
  std::cout << '\n';
  if (row < 0 || row >= _row || col < 0 || col >= _col)
    return false;
  _exitx = row; _exity = col;
  return true;
}

void maze::setMaze() {
  if (_row == 0 || _col == 0) {
    std::cout << "请输入迷宫的行和列：";
    std::cin >> _row >> _col;
  }
  std::cout << '\n';
  std::cout << "请输入迷宫的构造：" << '\n';
  for (int i = 0; i < _row; i++)
    for (int j = 0; j < _col; j++) {
      char ch;
      std::cin >> ch;
      _maze[i].push_back(ch);
    }
  std::cout << '\n';
}

void maze::set() {
  this->setMaze();
  this->setEntrance();
  this->setExit();
  this->tpath.push_back(std::make_pair(_entrancex, _entrancey));
  this->init();
  this->dfs(_entrancex, _entrancey);
}

void maze::dfs(int x, int y) {
  if (x == _exitx && y == _exity) {
    for (int i = 0; i < tpath.len(); i++) {
      path[_pathnum].push_back(tpath[i]);
    }
    _pathnum++;
  }
  if (x >= _row || x < 0)
    return;
  if (y >= _col || y < 0)
    return;
  if (_maze[x][y] == '#')
    return;
  if (done[x][y])
    return;
  done[x][y] = true;
  for (int i = 0; i <= 3; i++) {
    int newx = x + dir[i][0];
    int newy = y + dir[i][1];
    tpath.push_back(std::make_pair(newx, newy));
    dfs(newx, newy);
    tpath.pop_back();
  }
}

void maze::mapPrintf() {
  std::cout << "迷宫地图：" << '\n' << '\n';
  std::cout << "    ";
  for (int i = 0; i < _col; i++) {
    std::cout << i << "列" << "  ";
  }
  std::cout << '\n';
  for (int i = 0; i < _row; i++) {
    std::cout << i << "行";
    std::cout << " ";
    for (int j = 0; j <= _col; j++) {
      std::cout << _maze[i][j] << "    ";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

void maze::pathPrint() {
  if (_pathnum == 0)
    return;
  std::cout << "迷宫路径：" << '\n' << '\n';
  for (int i = 0; i < _pathnum; i++) {
    std::cout << "第" << i + 1 << "条路径：" << '\n';
    for (int j = 0; j < path[i].len() - 1; j++) {
      std::cout << '<' << path[i][j].first << ',' << path[i][j].second << '>' << "-->";
    }
    std::cout << '<' << path[i][path[i].len() - 1].first << ',' << path[i][path[i].len() - 1].second << '>';
    std::cout << '\n';
  }
}

int main()
{
  maze mymaze;
  mymaze.set();
  mymaze.mapPrintf();
  mymaze.pathPrint();
}