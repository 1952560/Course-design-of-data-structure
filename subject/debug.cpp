#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<stack>
#include<vector>

//中缀表达式转化成后缀表达式
struct expre {
  bool isnum;//1为数字
  char oper;
  int num;
};

class eval {
public:
  eval(std::string str) {
    infix = str;
    change();
  }
//private:
  void change() {
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
        if (oper.empty()) {//如果栈空
          oper.push(infix[i]);
          i++;
        }
        else {//如果栈非空
          if (infix[i] == ')') {//如果是‘）’
            while (oper.top()!= '(') {
              expre e;
              e.isnum = false; e.num = 0; e.oper = oper.top();
              oper.pop();
              suffix.push_back(e);
            }
            oper.pop();
            i++;
          }
          else {//如果不是‘）’
            while ((!oper.empty())&&(oper.top()!='(')&&(priority(infix[i]) <= priority(oper.top()))) {
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
    }
    while (!oper.empty()) {
      expre e;
      e.isnum = false; e.num = 0, e.oper = oper.top();
      oper.pop();
      suffix.push_back(e);
    }
  }
  int priority(char x) {
    if (x == '+' || x == '-')
      return 0;
    if (x == '*' || x == '/')
      return 1;
    if (x == '%')
      return 2;
    if (x == '^')
      return 3;
    if (x == ')' || x == '(')
      return 4;
    return -1;
  }

//private:
  std::string infix;
  std::stack<char> oper;
  std::vector<expre> suffix;
};

int main() {
  std::string str;
  std::cin >> str;
  eval e(str);
  for (int i = 0; i < e.suffix.size(); i++) {
    if (e.suffix[i].isnum)
      std::cout << e.suffix[i].num << ' ';
    else
      std::cout << e.suffix[i].oper << ' ';
  }
}