#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>


using namespace std;

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.



typedef struct MY_POINT {
	int x;
	int y;
};



//콜 바이 레퍼런스
void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
	
}

int main()
{

	//#2 레퍼런스
	//int a = 10;
	//int& r = a; // 레퍼런스 선언 a변수에 r이라는 또다른 별칭을 부여'

	//r = 200;
	//cout << a << endl;
	//cout << "----------------" << endl;

	//cout << &a << endl;			//래퍼런스 변수는 별도의 주소를 할당받지 않으므로 , 포인터보다 메모리적으로 경제적이다.
	//cout << &r << endl;			//복사가 필요없다 a는 곧 r이고 r은 곧 a다



	//#3 래퍼런스의 특징
	//포인터와 달리별도의 메모리가 없다.					//메모리 비용 절약
	//값복사도 없다.										//복사 비용 절약

				
	//	int& r = nullptr;	포인터처럼  null초기화 불가능. Error
	//  int& r;	//레퍼런스는 참조와 동시에 선언이 필요하다. Error

	//int a = 100, b = 200;
	//int& r = a;
	//r = b;				//참조 대상이 바뀌는게 아니라, a에 b값을 대입하는 것과 같은 결과가 나온다.
	//cout << a << endl;	//Output : 200
	//					//즉 레퍼런스는 참조 대상을 바꿀 수 없다.
	//int c = 10, d = 20;
	//Swap(c, d);
	//cout << c << " , " << d << endl;

	////////////////////////////////////////////////////동적할당 이외의 상황에선 앵간하면 레퍼런스를 사용하자!



	//#5 레퍼런스와 const

	//const int a = 300;
	////int& r = a;			//Error
	//const int& r = a;		//OK!


	//int& r = 100			//Error   리터럴 상수를 참조 하려면 const int & 에서 참조해야한다!
							//리터럴 상수는 임시공간에 있지만 , 100의 임시공간을 r이라는 const변수가 되었다!


    int * ptr = new int[5];

    cout <<_msize(ptr) <<endl;      //동적배열의 사이즈를 젤수 있다!!
    //_msize() 함수를 이용하여 동적배열의 메모리 크기계싼 가능
    cout <<
	

    int Array[10] = {};

    Func(Array)

	return 0;
}

void Func(int(&arr)[10])
{
    cout << sizeof(arr)<<endl;
}