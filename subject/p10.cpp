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

void instructions(){
	std::string str[12];
	str[0]="**			sorting algorithm comparison					**";
	str[1]="=============================================";
	str[2]="**		    1---bubblesort			        **";
	str[3]="**			2---selectionsort		        **";
	str[4]="**			3---insertionsort		        **";
	str[5]="**			4---shellsort	           	    **";
	str[6]="**			5---quicksort	             	**";
	str[7]="**			6---heapsort				    **";
	str[8]="**			7---heapsort					**";
	str[9]="**			8---radixsort	 				**";
	str[10]="**			9---quiting the system			**";
	str[11]="=============================================";
	for(int i=0;i<12;i++)
		std::cout<<str[i]<<'\n';
}

int main() {
	instructions();
	std::cout<<"请输入要产生的随机数的个数";
	int random_num=0;
	std::cin>>random_num;
	while(!checkCin()){
		std::cin>>random_num;
	}
	Vector<int> vec = get_random(random_num);
	int order=0;
	while(true){
		std::cout<<std::setw(15)<<"请选择排序算法";
		std::cin>>order;
		while(!checkCin()||order<1||order>9){
			std::cin>>order;
		}
		switch (order)
		{
		case 1:
			time(&start);
			std::cout<<std::setw(15)<<"冒泡排序所用时间";
			break;
		
		default:
			break;
		}
	}
}
