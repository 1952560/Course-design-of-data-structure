#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include"../H/Vector.h"
#include"../H/Stack.h"
#include<limits.h>
#include<math.h>
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
	eval(std::string& str) {
		flag = false;
		infix = str;
		change();
		calculate();
	}
private:
	void change();
	int priority(char x);
	void calculate();
	friend std::ostream& operator<<(std::ostream& os, const eval& e) {
		if (e.flag) {
			os << '\n' << '\n';
			return os;
		}
		os << e.ans << '\n' << '\n';
		return os;
	}
private:
	std::string infix;//存中缀表达式
	Vector<expre> suffix;//存后缀表达式
	int ans;
	bool flag;
};

void eval::calculate() {
	Stack<int> cal;
	try {
		for (int i = 0; i < suffix.size(); i++) {
			if (suffix[i].isnum)
				cal.push(suffix[i].num);
			else {
				char oper = suffix[i].oper;
				switch (oper) {
				case '+': {
					if (cal.size() >= 2) {
						int x = cal.top(); cal.pop();
						int y = cal.top(); cal.pop();
						cal.push(x + y);
					}
					else {
						this->flag = true;
						throw std::string("表达式有误");
					}
					break;
				}
				case'-': {
					if (cal.size() >= 2) {
						int x = cal.top(); cal.pop();
						int y = cal.top(); cal.pop();
						cal.push(y - x);
					}
					else {
						this->flag = true;
						throw std::string("表达式有误");
					}
					break;
				}
				case'*': {
					if (cal.size() >= 2) {
						int x = cal.top(); cal.pop();
						int y = cal.top(); cal.pop();
						cal.push(x * y);
					}
					else {
						this->flag = true;
						throw std::string("表达式有误");
					}
					break;
				}
				case'/': {
					if (cal.size() >= 2) {
						int x = cal.top(); cal.pop();
						int y = cal.top(); cal.pop();
						cal.push(y / x);
					}
					else {
						this->flag = true;
						throw std::string("表达式有误");
					}
					break;
				}
				case'%': {
					if (cal.size() >= 2) {
						int x = cal.top(); cal.pop();
						int y = cal.top(); cal.pop();{
							if(x==0){
								this->flag=true;
								throw std::string("0不能作为被除数");
							}
						}
						cal.push(y % x);
					}
					else {
						this->flag = true;
						throw std::string("表达式有误");
					}
					break;
				}
				case'^': {
					if (cal.size() >= 2) {
						int x = cal.top(); cal.pop();
						int y = cal.top(); cal.pop();
						if(y==0&&x<0){
							this->flag==true;
							throw std::string("表达式有误");
						}
						cal.push(pow(y, x));
					}
					else {
						this->flag = true;
						throw std::string("表达式有误");
					}
					break;
				}
				}
			}
		}
		ans = 0;
		if (cal.size() == 1) {
			ans += cal.top();
			cal.pop();
		}
		else {
			throw"表达式有误";
		}
	}
	catch (std::string str) {
		std::cout << str;
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
	Stack<char> oper;
	bool flag = false;
	if (infix[0] == '+' || infix[0] == '-')
		flag = true;
	for (int i = 0; i < infix.size(); ) {
		if (infix[i] >= '0' && infix[i] <= '9') {
			flag = false;
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
				if ((infix[i] == '+' || infix[i] == '-') && flag) {
					flag = false;
					expre e;
					e.isnum = true; e.num = 0;
					suffix.push_back(e);
				}
				if (infix[i] == '('||infix[i]=='*')
					flag = true;
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
	std::string ch;
	while (true) {
		std::cout << "输入表达式：" << '\n';
		std::cin >> str;
		if (str[str.size() - 1] != '=') {
			std::cout << "表达式缺少‘=’,请重新输入！" << '\n' << '\n';
			continue;
		}
		std::string str_copy;
		for(int i=0;i<str.size();){
			if((str[i]=='-'||str[i]=='+')&&i>0&&(str[i-1]=='*'||str[i-1]=='^'||str[i-1]=='/'||str[i-1]=='%')){
				int num=1;
				str_copy.push_back('(');
				str_copy.push_back('0');
				str_copy.push_back(str[i]);
				while(i+num<str.size()&&str[i+num]>='0'&&str[i+num]<='9'){
					str_copy.push_back(str[i+num]);
					num++;
				}
				if(num==1)
					str_copy.push_back('0');
				str_copy.push_back(')');
				i+=num;
			}
			else{
				str_copy.push_back(str[i]);
				i++;
			}
		}
		str=str_copy;
		//std::cout<<str<<'\n';
		str.pop_back();
		std::cout << eval(str);
		std::cout << "是否继续（y,n）？";
		std::cin >> ch;
		while (std::cin.fail() || (ch != "n" && ch != "y")) {
			if (std::cin.fail()) {
				std::cin.ignore(INT_MAX, '\n');
				std::cin.clear();
			}
			std::cout << "输入错误，请重新输入:";
			std::cin >> ch;
		}
		if (ch == "n")
			break;
	}
}
