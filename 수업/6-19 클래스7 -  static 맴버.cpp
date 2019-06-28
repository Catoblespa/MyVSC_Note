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
/*

##1 클래스와 this 포인터
클래스의 맴버변수는 객체마다 할당 된다.

*/

class CTest
{

private:
	int m_iValue;

	//static 맴버변수를 이렇게 써도 선언된거는 아니다! 밖에서 초기화 해주는게 진짜 선언임
	//
	static int ms_iV2;
public:
	CTest(int a)
	{
		/*this->*/m_iValue = a;
	};
	~CTest();

	void Func()
	{
		cout <<"m_iValue"<< &/*this->*/m_iValue << endl;
		cout <<"ms_iV2"<< &ms_iV2 << endl;
	}
	void PrintThis()
	{
		//this 포인터 : 현재 객체의 주소를 저장한 포인터
		cout << "this :" << this << endl;
	}

	static void StaticFunc()
	{
		//static 함수에서는 this 호출 불가능
		//cout << this << endl;
		//맴버 함수, 맴버 변수도 호출 불가능하다.
		//Func();
		//static 함수는 객체에 종속되지 않는다!
		cout << "이 함수는 누구의 소유도 아닙니다" << endl;
	}
};

//스태틱 맴버 변수 초기화 구문!
//스태틱 변수는 이니셜라이저로 초기화 불가능! 
int CTest::ms_iV2 = 0;


int main()
{
	//##2 static 맴버 함수
	//객체 생성 없이도 호출 할 수 있는 함수
	//앞으로 C++에서 전역함수를 다룰 때 static 맴버 함수로 다룰것!!
	CTest ob1(300);
	CTest ob2(300);
	CTest ob3(300);
	ob1.Func();
	ob2.Func();
	ob3.Func();

	cout << "==================" << endl;

}

CTest::~CTest()
{
}
