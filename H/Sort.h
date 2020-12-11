#pragma once
#include"Vector.h"
#include<random>
#include<ctime>
#include<vector>

/*
1.冒泡 2.选择 3.直接插入 4.希尔排序 5.快速排序
6.堆排序 7.归并 8 基数 9 退出程序
*/

template<typename T>
void swap(T& a, T& b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

Vector<int> get_random(int size) {
	std::default_random_engine e;
	std::uniform_int_distribution<int> u(-1000000000, 1e9+7);
	e.seed(time(0));
	Vector<int> v;
	for (int i = 0; i < size; i++)
		v.push_back(u(e));
	return v;
}

//bubble_sort(1)
template<typename T>
void bubble_sort(Vector<T>& v) {
	if (v.size() <= 1)
		return;
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = 0; j < v.size() - i - 1; j++) {
			if (v[j] > v[j + 1]) {
				swap<T>(v[j], v[j + 1]);
			}
		}
	}
}

//select_sort(2)
template<typename T>
void select_sort(Vector<T>& v) {
	if (v.size() <= 1)
		return;
	for (int i = 0; i < v.size() - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < v.size(); j++) {
			if (v[j] < v[min_index])
				min_index = j;
		}
		if (min_index != i)
			swap<T>(v[i], v[min_index]);
	}
}

//insert_sort(3)
template<typename T>
void insert_sort(Vector<T>& v) {
	if (v.size() <= 1)
		return;
	for (int i = 1; i < v.size(); i++) {
		int key = v[i];
		int j = i - 1;
		while (j >= 0 && key < v[j]) {
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = key;
	}
}

//shell_sort(4)
template<typename T>
void shell_sort(Vector<T>& v) {
	for (int gap = v.size() >> 1; gap > 0; gap >>= 1) {
		for (int i = gap; i < v.size(); i++) {
			int j = i;
			while (j - gap >= 0 && v[j] < v[j - gap]) {
				swap<T>(v[j], v[j - gap]);
				j -= gap;
			}
		}
	}
}

//quick_sort(5)
template<typename T>
void quick_sort(Vector<T>& v, int start, int end) {
	if (start >= end)
		return;
	int i = start, j = end, base = v[i];
	while (i < j) {
		while (v[j] >= base && i < j)
			j--;
		v[i] = v[j];
		while (v[i] <= base && i < j)
			i++;
		v[j] = v[i];
	}
	v[i] = base;
	quick_sort(v, start, i - 1);
	quick_sort(v, i + 1, end);
}

//heap_sort(6)
template<typename T>
void fitdown(int ind, Vector<T>& v, int end) {
	if ((ind << 1) + 1 >= end)
		return;
	T val1 = v[(ind << 1) + 1];
	if ((ind << 1) + 2 >= end) {
		if (v[ind] < val1) {
			v[(ind << 1) + 1] = v[ind];
			v[ind] = val1;
		}
	}
	else {
		T val2 = v[(ind << 1) + 2];
		if ((val2 < val1 || val2 == val1) && v[ind] < val1) {
			v[(ind << 1) + 1] = v[ind];
			v[ind] = val1;
			fitdown((ind << 1) + 1, v, end);
		}
		else if (val1 < val2 && v[ind] < val2) {
			v[(ind << 1) + 2] = v[ind];
			v[ind] = val2;
			fitdown((ind << 1) + 2, v, end);
		}
	}
}

template<typename T>
void heap_sort(Vector<T>& v) {
	for (int i = (v.size() >> 1) - 1; i >= 0; i--) {
		fitdown(i, v, v.size());
	}
	for (int i = v.size() - 1; i > 0; i--) {
		swap<T>(v[0], v[i]);
		fitdown(0, v, i);
	}
}

//merge_sort(7)
template<typename T>
void merge_sort(Vector<T>& v, int start, int end) {
	if (start >= end)
		return;
	int len = end - start, mid = (len >> 1) + start;
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	merge_sort(v, start1, end1);
	merge_sort(v, start2, end2);
	Vector<T> reg;
	while (start1 <= end1 && start2 <= end2)
		reg.push_back(v[start1] < v[start2] ? v[start1++] : v[start2++]);
	while (start1 <= end1)
		reg.push_back(v[start1++]);
	while (start2 <= end2)
		reg.push_back(v[start2++]);
	for (int i = 0; i < reg.size(); i++)
		v[start + i] = reg[i];
}

//radix_sort(8)
void radix_sort(Vector<int> &v){
    int len = v.size();
    if(len <= 1) return;
    int res = 10, div = 1;
    bool is_not_max_digit = true;
    Vector<int> counter[20];
    while(is_not_max_digit){
        is_not_max_digit = false;
        for(int i = 0; i < len; i++){
            if(abs(v[i]) / res) is_not_max_digit = true;
            int index = v[i] % res / div+10;
			if(v[i]<0)
				index=9-abs(v[i])%res/div;
            counter[index].push_back(v[i]);
        }
        int radix = 0, index = 0;
        for(int i = 0; i < len;){
			for(;index<counter[radix].size();index++){
				v[i+index]=counter[radix][index];
			}
			i+=index;
			index=0;
			radix++;
        }
        for(int i = 0; i < 20; i++){
            counter[i].clear();
        }
        res *= 10; div *= 10;
    }
}
