#include<iostream>
#include<string>
#include<stack>
#include<vector>

int fastpow(int base, int n) {//快速幂
  int ans = 1;
  while (n) {
    if (n & 1) ans *= base;
    base *= base;
    n >>= 1;
  }
  return ans;
}


//中缀表达式转化成后缀表达式
struct expre {
  bool isnum;//1为数字
  char oper;
  int num;
};

class eval {
public:
  eval(std::string &str) {
    infix = str;
    change();
    calculate();
  }
private:
  void change();
  int priority(char x);
  void calculate();
  friend std::ostream& operator<<(std::ostream& os, const eval& e) {
    os << e.ans << '\n';
    return os;
  }
private:
  std::string infix;//存中缀表达式
  std::vector<expre> suffix;//存后缀表达式
  int ans;
};

void eval::calculate() {
  std::stack<int> cal;
  for (int i = 0; i < suffix.size(); i++) {
    if (suffix[i].isnum)
      cal.push(suffix[i].num);
    else {
      char oper = suffix[i].oper;
      switch (oper) {
      case '+': {
        if (cal.empty())
          exit(0);
        else if (cal.size() == 1) {
          int x = 0;
          int y = cal.top(); cal.pop();
          cal.push(x + y);
        }
        else if (cal.size() >= 2) {
          int x = cal.top(); cal.pop();
          int y = cal.top(); cal.pop();
          cal.push(x + y);
        }
        break;
      }
      case'-': {
        if (cal.size() == 1) {
          int x = cal.top(); cal.pop();
          cal.push(-x);
        }
        else if (cal.size() >= 2) {
          int x = cal.top(); cal.pop();
          int y = cal.top(); cal.pop();
          cal.push(y - x);
        }
        else
          exit(0);
        break;
      }
      case'*': {
        if (cal.size() >= 2) {
          int x = cal.top(); cal.pop();
          int y = cal.top(); cal.pop();
          cal.push(x * y);
        }
        else
          exit(0);
        break;
      }
      case'/': {
        if (cal.size() >= 2) {
          int x = cal.top(); cal.pop();
          int y = cal.top(); cal.pop();
          cal.push(y / x);
        }
        else
          exit(0);
        break;
      }
      case'%': {
        if (cal.size() >= 2) {
          int x = cal.top(); cal.pop();
          int y = cal.top(); cal.pop();
          cal.push(y % x);
        }
        else
          exit(0);
        break;
      }
      case'^': {
        if (cal.size() >= 2) {
          int x = cal.top(); cal.pop();
          int y = cal.top(); cal.pop();
          cal.push(fastpow(y, x));
        }
        else
          exit(0);
        break;
      }
      }
    }
  }
  ans = 0;
  while (!cal.empty()) {
    ans += cal.top();
    cal.pop();
  }
}

int eval::priority(char x) {
  if (x == ')' || x == '(')
    return 5;
  if (x == '+' || x == '-')
    return 1;
  if (x == '*' || x == '/')
    return 2;
  if (x == '%')
    return 3;
  if (x == '^')
    return 4;
  return -1;
}

void eval::change() {
  std::stack<char> oper;
  for (int i = 0; i < infix.size(); ) {
    if (infix[i] >= '0' && infix[i] <= '9') {
      std::string str;
      while (infix[i] >= '0' && infix[i] <= '9') {
        str.push_back(infix[i]);
        i++;
      }
      int k = 1;
      int num = 0;
      for (int i = str.size() - 1; i >= 0; i--) {
        num += k * (int)(str[i] - '0');
        k *= 10;
      }
      expre e;
      e.isnum = true; e.num = num; e.oper = '?';
      suffix.push_back(e);
    }
    else {
      if (infix[i] == ')') {//如果是‘）’
        while (oper.top() != '(') {
          expre e;
          e.isnum = false; e.num = 0; e.oper = oper.top();
          oper.pop();
          suffix.push_back(e);
        }
        oper.pop();
        i++;
      }
      else {//如果不是‘）’
        if ((infix[i] == '+' || infix[i] == '-') && !oper.empty() && oper.top() == '(') {
          expre e;
          e.isnum = true; e.num = 0;
          suffix.push_back(e);
        }

        while ((!oper.empty()) && (oper.top() != '(') && (priority(infix[i]) <= priority(oper.top()))) {
          expre e;
          e.isnum = false; e.num = 0, e.oper = oper.top();
          oper.pop();
          suffix.push_back(e);
        }
        oper.push(infix[i]);
        i++;
      }
    }
  }
  while (!oper.empty()) {
    expre e;
    e.isnum = false; e.num = 0, e.oper = oper.top();
    oper.pop();
    suffix.push_back(e);
  }
}

int main() {
  std::string str;
  char ch;
  while (true) {
    std::cout << "输入表达式：" << '\n';
    std::cin >> str;
    std::cout << eval(str);
    std::cout << "是否继续（y,n）？";
    std::cin >> ch;
    if (ch == 'n')
      break;
  }
}