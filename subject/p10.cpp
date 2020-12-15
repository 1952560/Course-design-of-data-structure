#include"../H/Sort.h"
#include<vector>
#include<limits.h>
#include<iomanip>

bool checkCin(){
	if(std::cin.fail()){
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		std::cout<<"input error!please re-enter!"<<'\n';
		return false;
	}
	return true;
}

bool checkSort(const Vector<int> &v){
	for(int i=0;i<v.size()-1;i++){
		if(v[i]>v[i+1])
			return false;
	}
	std::cout<<"the vector has sorted!"<<'\n';
	return true;
}

void instructions(){
	std::string str[12];
	str[0]="**         sorting algorithm comparison     **";
	str[1]="==============================================";
	str[2]="**          1---bubblesort                  **";
	str[3]="**          2---selectionsort               **";
	str[4]="**          3---insertionsort               **";
	str[5]="**          4---shellsort                   **";
	str[6]="**          5---quicksort                   **";
	str[7]="**          6---heapsort                    **";
	str[8]="**          7---mergesort                    **";
	str[9]="**          8---radixsort                   **";
	str[10]="**          9---quiting the system          **";
	str[11]="==============================================";
	for(int i=0;i<12;i++)
		std::cout<<str[i]<<'\n';
}

int main() {
	instructions();
	std::cout<<"please enter the number of random numbers to be generated:";
	int random_num=0;
	std::cin>>random_num;
	while(!checkCin()){
		std::cin>>random_num;
	}
	Vector<int> v = get_random(random_num);
	int order=0;
	while(true){
		Vector<int> v_copy=v;
		clock_t start,end;
		double cost;
		// for(int i=0;i<v_copy.size();i++){
		// 	if(v_copy[i]>v_copy[i+1]){
		// 		std::cout<<'\n'<<"the vector has not sorted!"<<'\n';
		// 		break;
		// 	}
		// }
		std::cout<<std::setw(15)<<"please select the sorting algorithm:";
		std::cin>>order;
		while(!checkCin()||order<1||order>9){
			std::cin>>order;
		}
		switch (order)
		{
		case 1:
			start=clock();
			bubbleSort(v_copy);
			end=clock();
			cost=end-start;
			//checkSort(v_copy);
			std::cout<<std::setw(15)<<"bubblesort takes time:"<<cost<<" ms"<<'\n'<<'\n';
			break;
		case 2:
			start=clock();
			selectionSort(v_copy);
			end=clock();
			cost=end-start;
			//checkSort(v_copy);
			std::cout<<std::setw(15)<<"selectionsort takes time:"<<cost<<" ms"<<'\n'<<'\n';
			break;		
		case 3:
			start=clock();
			insertionSort(v_copy);
			end=clock();
			cost=end-start;
			//checkSort(v_copy);
			std::cout<<std::setw(15)<<"insertionsort takes time:"<<cost<<" ms"<<'\n'<<'\n';
			break;
		case 4:
			start=clock();
			shellSort(v_copy);
			end=clock();
			cost=end-start;     
			//checkSort(v_copy);                                                                                                                                                                                                                          
			std::cout<<std::setw(15)<<"shellsort takes time:"<<cost<<" ms"<<'\n'<<'\n';                                                                                                                                                                                                                                                                                                                                                                                       
			break;
		case 5:
			start=clock();
			quickSort(v_copy,0,v_copy.size()-1);
			end=clock();
			cost=end-start;
			//checkSort(v_copy);
			std::cout<<std::setw(15)<<"quicksort takes time:"<<cost<<" ms"<<'\n'<<'\n';
			break;         
		case 6:
			start=clock();
			heapSort(v_copy);
			end=clock();
			cost=end-start;
			//checkSort(v_copy);
			std::cout<<std::setw(15)<<"heapsort takes time:"<<cost<<" ms"<<'\n'<<'\n';
			break;
		case 7:
			start=clock();
			mergeSort(v_copy,0,v_copy.size()-1);
			end=clock();
			cost=end-start;
			//checkSort(v_copy);
			std::cout<<std::setw(15)<<"mergesort takes time:"<<cost<<" ms"<<'\n'<<'\n';
			break;
		case 8:
			start=clock();
			radixSort(v_copy);
			end=clock();
			cost=end-start;
			//checkSort(v_copy);
			std::cout<<std::setw(15)<<"radixsort takes time:"<<cost<<" ms"<<'\n'<<'\n';
			break;
		case 9:
			exit(0);
		default:
			break;
		}
	}
}
