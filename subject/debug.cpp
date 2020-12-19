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
    void nextPermutation(vector<int>& nums) {
        if(nums.size()<2)
            return;
        vector<string> str;
        for(int i:nums){
            str.push_back(to_string(i));
        }
        bool flag=false;
        int i=str.size()-1;
        for(;i>0;i--){
            if(str[i]>str[i-1]){
                flag=true;
                break;
            }
        }
        if(flag){
            swap(nums[i],nums[i-1]);
            return;
        }
        sort(str.begin(),str.end());
        for(int i=0;i<str.size()-1;i++){
            nums[i]=std::stoi(str[i]);
        }
        return;
    }
};

int main(){
    vector<int> v={3,2,1};
    Solution s;
    s.nextPermutation(v);
}