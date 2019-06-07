#include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <deque>		//STL deque 정의 헤더
#include <set>			//STL 연관컨테이너 set
#include <map>			//STL 연관컨테이너 map
#include <stack>		//STL 컨테이너 어댑터 stack
#include <queue>		////STL 컨테이너 어댑터 queue
#include <array>
#include <numeric>		//수치 관련 알고리즘 . STL이 아닌 C+라이브러리에 포함되어 있다.
#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;

char* InputString()
{
	char* ptr = new char[32]; // (char*)calloc(32, sizeof(char));
	cout << "문자열 입력 : ";
	cin >> ptr;

	return ptr;
}






//##1. C++에서의 동적할당 연산자
int main()
{
	// new 와 delete
	int* ptr_1 = (int*)malloc(4);		//C기반
	int* ptr_2 = new int;				//C++기반
	float* ptr_3 = new float(3.14f);	//할당과 동시에 초기화

	cout << *ptr_1 << endl;	//쓰뤡이값
	cout << *ptr_2 << endl;
	cout << *ptr_3 << endl; //초기화 되어있음 ㅋ


	free(ptr_1);		//C기반
	delete ptr_2;		//C++기반
	delete ptr_3;

	cout << "=============================================" << endl;
	//#3 동적 배열

	int* ptr = new int[3];
	cout << ptr[1] << endl; //자동 0 초기화 안됨.

	int* ptr2 = new int[3]{}; //{10,20}   10, 20 ,0 으로 초기화
	for (int i = 0; i < 3; i++)
	{
		cout <<"ptr2["<<i<<"]"<< ptr2[i] << endl; //자동 0 초기화 됨
	}



	delete[] ptr; //동적 배열 해제 
	delete[] ptr2; //동적 배열 해제 


	char* pName = InputString();
	cout << "출력 : " << pName << endl;	

	delete[] pName;

	return 0;
}

/*
 	//메모리 할당 
 	int **arr = new int*[sizeY];
  	
	  
	for(int i = 0; i < sizeY; ++i) 
  	{ 
	  	arr[i] = new int[sizeX];
  		memset(arr[i], 0, sizeof(int)*sizeX);  // 메모리 공간을 0으로 초기화 
   	} 
   
  	// 메모리 해제 
   	for(int i = 0; i < sizeY; ++i) 
   	{ 
	   delete [] arr[i]; 
	} 
	   
	   delete [] arr;

*/
