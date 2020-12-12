#pragma once
#include"Vector.h"
#include<random>
#include<ctime>
#include<time.h>
#include<vector>

/*
1.bubblesoty 2.selsetionsort 3.insertionsort 
4.shellsort 5.quicksort
6.heapsort 7.mergesort 8 radixsort 9 exit
*/

int times;

template<typename T>
void swap(T& a, T& b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

Vector<int> get_random(int size) {
	std::default_random_engine e;
	std::uniform_int_distribution<int> u(-1e9-7, 1e9+7);
	e.seed(time(0));
	Vector<int> v;
	for (int i = 0; i < size; i++)
		v.push_back(u(e));
	return v;
}

//bubble_sort(1)
//data structure-------------Vector<int>
//worst time complexity------O(n^2)
//optimal time complexity----O(n)
//average time complexity----O(n^2)
//required auxiliary space---O(1)
//stability------------------stable
template<typename T>
void bubbleSort(Vector<T>& v) {
	if (v.size() <= 1)
		return;
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = 0; j < v.size() - i - 1; j++) {
			if (v[j] > v[j + 1]) {
				swap<T>(v[j], v[j + 1]);
				times++;
			}
		}
	}
	std::cout<<"The number of comparison for selection sorting is:"<<times<<'\n';
	times=0;
}

//select_sort(2)
//data structure-------------Vector<int>
//worst time complexity------O(n^2)
//optimal time complexity----O(n)
//average time complexity----O(n^2)
//required auxiliary space---O(1)
//stability------------------unstable
template<typename T>
void selectionSort(Vector<T>& v) {
	if (v.size() <= 1)
		return;
	for (int i = 0; i < v.size() - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < v.size(); j++) {
			if (v[j] < v[min_index])
				min_index = j;
		}
		if (min_index != i){
			swap<T>(v[i], v[min_index]);
			times++;
		}
	}
	std::cout<<"The number of comparison for selection sorting is:"<<times<<'\n';
	times=0;
}

//insert_sort(3)
//data structure-------------Vector<int>
//worst time complexity------O(n^2)
//optimal time complexity----O(n)
//average time complexity----O(n^2)
//required auxiliary space---O(1)
//stability------------------stable
template<typename T>
void insertionSort(Vector<T>& v) {
	if (v.size() <= 1)
		return;
	for (int i = 1; i < v.size(); i++) {
		int key = v[i];
		int j = i - 1;
		while (j >= 0 && key < v[j]) {
			v[j + 1] = v[j];
			j--;
			times++;
		}
		times++;
		v[j + 1] = key;
	}
	std::cout<<"The number of comparison for selection sorting is:"<<times<<'\n';
	times=0;
}

//shell_sort(4)
//data structure-------------Vector<int>
//worst time complexity------O(ns)
//optimal time complexity----O(n)
//average time complexity----O(nlogn)
//required auxiliary space---O(1)
//stability------------------unstable
template<typename T>
void shellSort(Vector<T>& v) {
	for (int gap = v.size() >> 1; gap > 0; gap >>= 1) {
		for (int i = gap; i < v.size(); i++) {
			int j = i;
			while (j - gap >= 0 && v[j] < v[j - gap]) {
				times++;
				swap<T>(v[j], v[j - gap]);
				j -= gap;
			}
		}
	}
	std::cout<<"The number of comparison for selection sorting is:"<<times<<'\n';
	times=0;
}

//quick_sort(5)
//data structure-------------Vector<int>
//worst time complexity------O(n^2)
//optimal time complexity----O(nlogn)
//average time complexity----O(nlogn)
//required auxiliary space---O(nlogn)
//stability------------------unstable
template<typename T>
void quickSort(Vector<T>& v, int start, int end) {
	if (start >= end)
		return;
	int i = start, j = end, base = v[i];
	while (i < j) {
		while (v[j] >= base && i < j)
			j--;
		v[i] = v[j];
		times++;
		while (v[i] <= base && i < j)
			i++;
		v[j] = v[i];
		times++;
	}
	v[i] = base;
	times++;
	quickSort(v, start, i - 1);
	quickSort(v, i + 1, end);
	if(start==0&&end==v.size()-1){
		std::cout<<"The number of comparison for selection sorting is:"<<times<<'\n';
		times=0;
	}
}

//heap_sort(6)
template<typename T>
void fitdown(int ind, Vector<T>& v, int end) {
	if ((ind << 1) + 1 >= end)
		return;
	T val1 = v[(ind << 1) + 1];
	times++;
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
//data structure-------------Vector<int>
//worst time complexity------O(nlogn)
//optimal time complexity----O(nlogn)
//average time complexity----O(nlogn)
//required auxiliary space---O(1)
//stability------------------unstable
template<typename T>
void heapSort(Vector<T>& v) {
	for (int i = (v.size() >> 1) - 1; i >= 0; i--) {
		fitdown(i, v, v.size());
	}
	for (int i = v.size() - 1; i > 0; i--) {
		swap<T>(v[0], v[i]);
		times++;
		fitdown(0, v, i);
	}
	std::cout<<"The number of comparison for selection sorting is:"<<times<<'\n';
	times=0;
}

//merge_sort(7)
//data structure-------------Vector<int>
//worst time complexity------O(nlogn)
//optimal time complexity----O(nlogn)
//average time complexity----O(nlogn)
//required auxiliary space---O(n)
//stability------------------stable
template<typename T>
void mergeSort(Vector<T>& v, int start, int end) {
	if (start >= end)
		return;
	int len = end - start, mid = (len >> 1) + start;
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	mergeSort(v, start1, end1);
	mergeSort(v, start2, end2);
	Vector<T> reg;
	while (start1 <= end1 && start2 <= end2){
		times++;
		reg.push_back(v[start1] < v[start2] ? v[start1++] : v[start2++]);
	}
	while (start1 <= end1){
		times++;
		reg.push_back(v[start1++]);
	}
	while (start2 <= end2){
		times++;
		reg.push_back(v[start2++]);
	}
	for(int i=0;i<reg.size();i++)
	v[start + i] = reg[i];
	if(start==0&&end==v.size()-1){
		std::cout<<"The number of comparison for selection sorting is:"<<times<<'\n';
		times=0;
	}
}

//radix_sort(8)
//data structure-------------Vector<int>
//worst time complexity------O(n*d)
//optimal time complexity----O(n*d)
//average time complexity----O(n*d)
//required auxiliary space---O(d)              
//stability------------------stable
void radixSort(Vector<int> &v){
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
			times++;
        }
        int radix = 0, index = 0;
        for(int i = 0; i < len;){
			times++;
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
	std::cout<<"The number of comparison for selection sorting is:"<<times<<'\n';
	times=0;
}
