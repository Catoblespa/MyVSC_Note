
/////////////////////////////////////////////////CTest.h///////////////////////////////////////////////////////

#pragma once
#include <iostream>
using namespace std;

class CTest
{
public:

	//클래스의 const
	//이니셜라이저를 사용하면 생성자 호출 이전에 const를 초기화 할 수 있다.
	CTest()	:m_iCount(100), m_iValue(200),
		m_iArr{ 10,20,30,40 }//이니셜라이저
	{
		//m_iCount = 100;	//Error
		//사실 생성자가 호출되기 전에 m_iValue의 메모리가 할당되므로
		//m_iValue는 생성자 호출전까진 쓰래기 값을 갖고있다.
		//일반 맴버 변수또한 이니셜라이저를 사용하면 쓰래기값없이 선언과 동시에 초기화된다.
		m_iValue = 200;	
	}
	CTest(int A, int B, const char * pc) :m_iCount(A), m_iValue(B),
		m_iArr{A,B,},pC(pc)//이니셜라이저
	{
		m_iValue = A; // const객체로 선언하더라도 생성자 안에서의 값변경은 허용해준다!
	}
	~CTest();

public :
	//const 맴버 함수.
	//const 함수는 맴버 함수 안에서만 존재하는 형식의 함수이다.
	//const 맴버 함수는 해당 함수 안에서 맴버 변수에 대한 값 변경을 불가능하게 한다!
	//즉 const맴버 함수는 읽기 전용 함수이다!!!
	void constFunc() const
	{
		cout << "const 맴버 함수 입니다" << endl;
		//m_iValue = 200;  Error!!!!
		int  i = 200;//지역 변수는 값 수정가능
	}
	
	void NomalFunc()
	{
		cout << "일반 맴버 함수 입니다" << endl;
	}

	//const맴버 함수는 const여부에 따라 함수 오버로딩이 가능하다! 
	//당연히 맴버함수가 아닌함수는 오버로딩 되지 않는다는것! 애초에 const함수가 없다!
	void Func() const 
	{
		cout << "Func() const  함수 입니다" << endl;

	}	
	
	void Func()
	{
		cout << "Func() 함수 입니다" << endl;

	}

private :
	const int m_iCount;
	const int m_iArr[10];
	const char* pC;
	int m_iValue;
};


//////////////////////////////////////////////////CTest.cpp////////////////////////////////////////////////////////////


//////////////////////////////////////////////////Main/////////////////////////////////////////////////////////
#include "CTest.h"


#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

int main()
{
	//#3. const 객체.
	const CTest obj(100,200,"Hello");

	//const 객체는 const맴버 함수만 호출 가능하다!
	//즉 자신의 맴버의 값 변경을 허용하지 않는다.
	//obj.NomalFunc(); //호출 불가능
	obj.constFunc();	//호출 가능
	obj.Func();		//const인 Func가 호출된다! const맴버함수는 

}