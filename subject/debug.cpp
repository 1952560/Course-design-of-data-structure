#include<iostream>
#include<string>
#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<algorithm>
#include<map>
#include<set>
#include<stack>
#include<vector>
#include<queue>
#include<unordered_set>
#include<unordered_map>
#include<thread>
#include<mutex>
#include<chrono>

#define ll long long
#define lld long long double
#define ull unsigned long long
using namespace std;

const ll maxn = 1e2 + 10;
class Solution {
public:
	string str;
	string longestPalindrome(string s) {
		string ans;
		int len = 0;
		for (int i = 0; i < s.size(); i++) {
			for (int j = i; j < s.size(); j++) {
				if (is(s, i, j)) {
					if (len < j - i + 1) {
						ans = this->str;
						len = j - i + 1;
					}
				}
			}
		}
		return ans;
	}
	bool is(string& s, int i, int j) {
		string st;
		while (i < j) {
			if (s[i] != s[j]) {
				return false;
			}
			i++; j--;
		}
		for (int k = i; k <= j; k++) {
			st.push_back(s[k]);
		}
		this->str = st;
		return true;
	}
};

int main()
{
	string s = "babad";
	Solution sol;
	cout << sol.longestPalindrome(s);
}
