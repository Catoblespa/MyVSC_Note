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


//##1. 동적할당 (Dynamic Allocation)

//char* InputString()
//{
//	char szInput[32] = "12";
//	cout << "문자열 입력 : ";
//	cin >> szInput;
//
//	return szInput;
//}

//위에걸 고치면 이렇게 쓴다.
char* InputString()
{
	char* ptr = (char*)calloc(32, sizeof(char));
	cout << "문자열 입력 : ";
	cin >> ptr;

	return ptr;
}

int main()
{
	//pName은 InputString이 갖고 있는 지역변수 szInput의 주소를 반환받고있다.
	//InputString 함수가 끝나면 szInput의 메모리가 해제된다.
	//이때 이미 소멸된 공간의 주소를 갖고 있는 포인터를 dangling 포인터라 부른다.
			//char* pName = InputString();
			//cout << "출력 : " << pName << endl;	


	//1 malloc함수
	//int타입 4바이트 메모리를 Heap에 할당.

	int * ptr = (int*)malloc(4);	//malloc(4) = 4바이트 메모리를 힙에 할당
									//(int*)malloc(4) int*타입으로 캐스팅		== (int*)malloc(sizeof(int))
									//int * ptr에 주소 대입하여 사용!
	cout << *ptr << endl;		//쓰래기값
	*ptr = 100;					//힙영역에 100씀
	//힙영역에 할당시켰으므로, 함수가 끝나도 해당 메모리는 해제 되지 않는다.   이것을 메모리 릭이라고 한다.
	free(ptr);		//메모리 해제
	ptr = nullptr;		//dangling 포인터 방지.

	if (nullptr != ptr)		//포인터 쓸때는 무조건 체크!!!
		* ptr = 200; 


	//2 calloc함수
	//동적 배열 할당하는 함수.
	//연속된 힙공간에 연속적으로 할당한다! calloc(size_t _Count , size_t Size);
	int * ptr2 = (int*)calloc(3, sizeof(int));		//int공간을 3개 연속으로 할당한다.
		//==malloc(4 * sizeof(int)) 와 똑같이 작동한다/


	ptr2[0] = 100;
	ptr2[1] = 200;
	ptr2[2] = 300;
	cout <<	"ptr2[0] : " << ptr2[0] << endl;
	cout << "ptr2[1] : " << ptr2[1] << endl;
	cout << "ptr2[2] : " << ptr2[2] <<endl;


	//3 동적 배열
	// f런타임 도중에 배열의 길이를 정할 수 있는 배열이다!!!!
	int iCount = 0;
	cout << "배열의 길이 :";
	cin >> iCount;

	int* ptr3 = (int*)calloc(iCount, sizeof(int));
	// int* ptr3 = (int*)malloc(iCount * sizeof(int)); //같은 결과

	for (int i = 0; i < iCount; i++)
	{
		cout << (ptr3[i] = i + 1) << endl;
	}

// malloc 과 calloc의 차이
    cout << "malloc 과 calloc의 차이"<<endl;
	int* ptr_1 = (int*)malloc(3 * sizeof(int));

	for (int i = 0; i < 3; i++)
	{
		cout << ptr_1[i] << endl;	//쓰래기 값
	}
	//메모리 초기화 함수
	memset(ptr_1, 0, 3 * sizeof(int));
	// ptr을 0으로 초기화 한다 3 * sizeof(int) 메모리 만큼!
    //memset은 1바이트 단위로 초기화한다.  memset(,1,)로 초기화한 4바이트 int는 0000 0001 0000 0001 0000 0001 0000 0001로 초기화된다..!
    //memset은 0초기화 용으로 사용 많이 한다..

	cout << "----------------------" << endl;
	int* ptr_2 = (int*)calloc(3 , sizeof(int));

	for (int i = 0; i < 3; i++)
	{
		cout << ptr_2[i] << endl;  // 0초기화 된다.
	}

	cout << "----------------------" << endl;
	cout << "-----------------------------------------------" << endl;

	//4 realloc   :  동적배열의 크기를 런타임 사이에 수정하는 함수이다.
					//새로운 주소에 필요한 만큼 할당후, 복사.   이전에 쓰던 메모리는 해제 된다.
	cout << "배열의 길이:";
	cin >> iCount;

	int * ptr_ = (int*)realloc(ptr3,iCount * sizeof(int));
							//ptr3안에 있던내용이 다른 메모리에 복사 된 이후에  free된다.
	for (int i = 0; i < iCount; i++)
	{
		cout << ptr_[i] << endl;
	}



	//free(ptr3); 해제된 메모리에 대해 또 free걸면 터져버림
	free(ptr2);
	free(ptr_);
	ptr = nullptr;

	return 0;
}