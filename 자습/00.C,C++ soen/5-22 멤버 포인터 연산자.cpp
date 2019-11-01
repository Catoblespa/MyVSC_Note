#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;
void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
멤버 포인터 변수
멤버 포인터 변수란 특정 클래스(구조체도 물론 포함된다.)에 속한 멤버만을 가리키는 포인터이다. 
일반 포인터가 메모리상의 임의 지점을 가리킬 수 있는데 비해 객체 내의 한 지점만을 가리킨다는 점에서 독특하다. 
선언 형식은 다음과 같다.
		타입 클래스::*이름;

포인터 변수이므로 당연히 대상체의 타입이 필요하다. 
그리고 특정 클래스 소속의 변수만을 가리킬 수 있으므로 어떤 클래스의 멤버들을 가리킬 것인지도 밝혀야 하며
클래스 소속 뒤에 포인터임을 나타내는 구두점 *와 변수의 이름을 적는다. 선언 형식이 다소 생소하므로 간단한 예제를 보고 사용예를 익혀 보자.
*/


class MyClass
{
public:
	int i, j;
	double d;

};

class Position
{
public:
	int x, y;
	char ch;

	Position() { x = 0; y = 0; ch = 'A'; }
	void OutPosition() 
	{
		gotoxy(x, y); _putch(ch);
	}

};

// 멤버 포인터 변수로 객체의 실제 멤버를 액세스할 때는 멤버 포인터 연산자라는 특수한 연산자가 필요하다.
			//Obj.*mp
			//pObj->*mp
// .* 연산자는 좌변의 객체에서 멤버 포인터 변수 mp가 가리키는 멤버를 읽는다.
// Obj가 상수 객체가 아니고 mp가 상수가 아닌 데이터 멤버를 가리킨다면 Obj.*mp 자체는 좌변값이므로 이 식을 좌변에 놓아 멤버 값을 변경하는 것도 물론 가능하다.
// ->*연산자는 좌변의 포인터가 가리키는 객체에서 mp가 가리키는 멤버를 읽는다.

void main()
{
	//MyClass C;
	//int MyClass::* pi;			//int 타입 pi 맴버포인터 선언
	//double MyClass::* pd;		//double 타입 pd 맴버포인터 선언.
	//int num;

	//pi = &MyClass::i;		//pi가 가리킬 수 있는 변수는 반드시 MyClass에 속한 멤버여야 하며 또한 정수형이어야 한다.
	//pi = &MyClass::j;
	//pd = &MyClass::d;

	Position Here;
	Position* pPos = &Here;
	int Position::* pi;

	pi = &Position::x;		//pi가 Position::x를 가르키고 잇을때 Here.*pi와 Here.x는 똑같은 뜻이다.
	Here.*pi = 30;			//*pi는 곧 x 이므로 치환해보면 똑같다는 걸 알 수 있다.
	pi = &Position::y;
	pPos->*pi = 5;
	Here.OutPosition();
}

