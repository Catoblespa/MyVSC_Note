#include<iostream>
#include <Windows.h>
#include <conio.h>

using namespace std; 

// 예제를 위해 추가!
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//mutable은 C++에 새로 추가된 키워드인데 영어 뜻 그대로 번역하면 변덕스럽다는 뜻이다.
//상수의 반대 의미로 사용되며 "수정 가능" 정도로 이해하면 된다.
//mutable로 지정된 멤버는 상수 함수나 상수 객체에 대해서도 값을 변경할 수 있다.
//객체의 상태를 표현하는 중요한 멤버가 아닐 때 이 속성을 사용한다.잘 쓰이

class Some

{

private:
	mutable int v;

public:
	Some() { }
	void func() const { v = 0; }	// mutable을 지정해 줄 경우 맴버 함수에서도 v를 접근하여 값을 수정할 수있다.
									//func이 const함수이기 때문에 mutable을 지울경우 당연히 애러가 나게 된다.
	//근데 왜 이딴게 필요한걸까 ?
	//객체에 상수성을 주는 이유는 객체의 상태가 우발적으로 변경되는 것을 금지하여 안정성을 높이자는 취지이다. 
	//그런데 때로는 객체의 멤버이면서도 객체의 상태에 포함되지 않는 멤버가 존재하기도 하는데 예를 들어 값 교환을 위한 임시 변수가 이에 해당한다. 
	//또는 i, j같은 통상적인 루프 제어 변수도 객체의 상태라고 볼 수 없으며 디버깅을 위해 임시적으로 추가된 멤버도 mutable이어야 한다. 
	//예를 들어 객체 상태를 출력해 보기 위한 문자열 버퍼를 멤버로 잠시 선언했다면 이 버퍼는 객체의 주요 멤버 변수에 포함되지 않는다. 다음 예제를 보자.

};


class Position
{
private:
	int x, y;
	char ch;
	mutable char info[256];

public:
	Position(int ax, int ay, char ach) { x = ax; y = ay; ch = ach; }
	void OutPosition() const { gotoxy(x, y); putch(ch); }
	void MoveTo(int ax, int ay) { x = ax; y = ay; }
	void MakeInfo() const { sprintf(info, "x=%d, y=%d, ch=%c", x, y, ch); }	//단순 출력이긴 하지만, 동시에 info의 값을 수정
	void OutInfo() const { puts(info); }

};
//객체의 현재 상태를 문자열로 출력하기 위해 info라는 문자열 버퍼를 멤버 변수로 선언했으며
//이 버퍼에 상태를 조립하는 MakeInfo와 OutInfo 함수를 선언했다.
//Position 클래스는 워낙 간단해서 상태를 조사하는 것이 아주 쉽지만 복잡한 클래스는 상태가 수시로 변하며
//특정 시점의 상태를 즉시 조사하기 힘든 경우도 있어 미리 조사해 두어야 한다.
//이때 info는 객체 자체의 상태가 아니라 속도 향상을 위한 임시적인 캐시 정보일 뿐이며 원한다면 언제든지 다시 조사할 수 있다.
//객체의 속성이 아닌 멤버에 대해 예외적으로 아무나 값을 변경할 수 있도록 하는 장치가 바로 mutable이다.
//위 예제에서 info가 mutable이 아니라면 MakeInfo는 상수 멤버 함수가 될 수 없으며 상수 객체에 대해서는 정보를 조사하거나 출력하는 것이 불가능해질 것이다.


int main()
{
	Some S;
	S.func();

	const Some T;
	T.func();


	const Position Here(11, 22, 'Z');

	Here.MakeInfo();

	Here.OutInfo();

	return 0;
}
