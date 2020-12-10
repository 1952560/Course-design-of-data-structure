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

int preNUm(unsigned char byte) {
    unsigned char mask = 0x80;
    int num = 0;
    for (int i = 0; i < 8; i++) {
        if ((byte & mask) == mask) {
            mask = mask >> 1;
            num++;
        } else {
            break;
        }
    }
    return num;
}


bool isUtf8(unsigned char* data, int len) {
    int num = 0;
    int i = 0;
    while (i < len) {
        if ((data[i] & 0x80) == 0x00) {
            // 0XXX_XXXX
            i++;
            continue;
        }
        else if ((num = preNUm(data[i])) > 2) {
        // 110X_XXXX 10XX_XXXX
        // 1110_XXXX 10XX_XXXX 10XX_XXXX
        // 1111_0XXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
        // 1111_10XX 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
        // 1111_110X 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
        // preNUm() 返回首个字节8个bits中首�?0bit前面1bit的个数，该数量也是该字符所使用的字节数        
        i++;
        for(int j = 0; j < num - 1; j++) {
            //判断后面num - 1 个字节是不是都是10开
            if ((data[i] & 0xc0) != 0x80) {
                    return false;
                }
                i++;
        }
    } else {
        //其他情况说明不是utf-8
        return false;
    }
    } 
    return true;
}

int main(){
    string str;
    cin>>str;
    cout<<int(str[1]);
}