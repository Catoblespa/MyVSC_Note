
/////////////////////////////////////////////////CPlayer.h///////////////////////////////////////////////////////
#pragma once
#include <iostream>
using namespace std;
class CPlayer
{
public:
	//클래스 생성자 (constructor)
	//객체 생성 시 자동으로 무조건 호출되는 함수의 일종 = 객체 생성에 필수요소
	//사용자가 정의하지 않았을경우 컴파일러가 디폴트 생성자를 만들어 사용한다.
	//클래스 맴버 초기화에 유용하게 쓰인다.
	//사용자가 디폴트 생성자 이외의 생성자를 만들었을경우, 컴파일러는 디폴트 생성자를 만들지 않는다.
	//객체 생성 과정
	//	1.메모리 할당
	//	2.생성자 호출
	CPlayer()
	{
		cout << "인자 없는 디폴트 생성자 호출" << endl;
		m_iValue = 0;
		ptr = new int[3];
	}	
	CPlayer(int _iValue)
	{
		m_iValue = _iValue;
		cout << "인자 있는 생성자 호출" << endl;
		ptr = new int[3];
	}
	//클래스 소멸자 (destructor)
	//객체 소멸시 소멸자가 호출 된다.
	//객체 소멸 과정 
	//	1. 소멸자 호출
	//	2. 메모리 반납.
	//소멸자는 오버로딩 할 수 없다!!!
	//사용자가 소멸자를 명시하지 않으면 컴파일러가 디폴트 소멸자를 만들어준다.
	//현재 클래스의 맴버 해제 시 소멸자가 유용하게 사용된다.
	~CPlayer()
	{
		delete ptr;		//맴버 변수중 동적할당된 변수들은
						//소멸자에서 delete하자!!
		cout << "소멸자 입니다 " << endl;
	}


	//멤버 함수
	void Func();

private :
	int m_iValue;
	int* ptr;
};

//전역 함수
void Func();

//////////////////////////////////////////////////CPlayer.cpp////////////////////////////////////////////////////////////
#include "CPlayer.h"
CPlayer::CPlayer()
{
}
CPlayer::~CPlayer()
{
}
//맴버함수의 정의부
void CPlayer::Func()
{
}
//전역 함수의 정의부
void Func()
{
}
//////////////////////////////////////////////////Main/////////////////////////////////////////////////////////

#include "CPlayer.h"

using namespace std;

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.
int main()
{

	//정적할당시 생성자 호출
	CPlayer cp1;	//인자없는 (디폴트) 생성자 호출
	CPlayer cp2(200);	//인자가 있는 생성자 호출
	CPlayer cp3 = 200;	//윗줄과 동일한 문법


	//이때 포인터는 객체가 아니므로, 생성자가 호출되지 않는다!!!
	CPlayer* ptr = nullptr;
	ptr = new CPlayer;  //힙 영역에 객체 생성 , 디폴트 생성자 호출

	//클래스 동적할당!
	CPlayer* ptr2 = nullptr;
	ptr2 = new CPlayer(200);  //인자가 있는 생성자 호출
	//malloc으로 동적생성 할 경우 클래스는 생성자를 불러오지 못한다!!!
	CPlayer* ptr3 = (CPlayer*)malloc(sizeof(CPlayer));

	//동적생성한 클래스의 소멸자는 사용자가 반드시 할당해제 해줘야함.
	free( ptr3); // free는 소멸자가 호출 안된다.
	delete ptr2; // delete하면 소멸자가 호출된다!!!!

	// CPlayer 소멸자가 총 5회 호출된다.  free은 호출되지 않는다.

	//객체정적배열
	CPlayer Arr[3] = {  };			//생성자 3회 호출!
	//객체동적배열
	CPlayer* ptr4 = new CPlayer[3];	//생성자 3회 호출!

	//객체 포인터 배열
	//객체에 대한 포인터를 만든 것이므로 생성자 호출x
	CPlayer* Arr2[3] = {};			
	//객체 포인터 배열에 CPlayer를 3번 할 당 했으므로   생성자 3회 호출!
	CPlayer* Arr3[3] = {new CPlayer,new CPlayer ,new CPlayer };

	/*

	!!!!!!!!!!!!!주우우웅요!!!!!!!!!!!!!
	CPlayer *ptr = new CPlayer[3];
	CTest *Arr[3] = {new CPlayer,new CPlayer ,new CPlayer };
	둘의 차이!!


	CPlayer *ptr = new CPlayer[3];

	ptr포인터는 Stack 메모리에 잡히고
	각각의 CPlayer 3개가 연속된 힙 메모리에 잡힌다!!	//객체메모리가 연속적임

	Arr[3]
	Arr배열에 3개의 포인터가 Stack에 할당되고.		//포인터는 배열이니까 연속적임
	각각의 CPlayer가 임의의 힙공간에 할당된다!!!	//객체는 힙 어딘가에 흩어짐

	*/

	delete[] ptr4;
	delete[] Arr3[0];		//객체 포인터 배열의 경우 각각 따로따로 해제 해줘야한다.
	delete[] Arr3[1];		//for문 돌리면 될듯 ㅎ
	delete[] Arr3[2];
	return 0;
}