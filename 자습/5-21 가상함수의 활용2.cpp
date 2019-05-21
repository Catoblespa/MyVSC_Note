#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>

using namespace std;
/*
재정의 가능한 함수.     이하 내용과 관련이 깊음. 1번 읽어봄.
http://soen.kr/lecture/ccpp/cpp3/30-2-3.htm

가상함수는 언제 써야 하는가
http://soen.kr/lecture/ccpp/cpp3/30-2-5.png
*/

void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Point
{
protected:
	int x, y;
	char ch;

public:
	Point(int ax, int ay, char ach) { x = ax; y = ay; ch = ach; }

	virtual void Show() {gotoxy(x, y); _putch(ch);}			//show함수와 Hide함수는 Point를 부모로 받는 도형의 종류마다 다르므로 virtual이다.
	virtual void Hide() {	gotoxy(x, y); _putch(' ');}
    //만약 Point클래스의  Show 와 Hide에서  vritual을 풀게 되면 일어나는일 -
    //Circle클래스에서 Move함수는 재정의 되어 있지 않고 Point 클래스의 Move를 계승되어있음
    //C.Move를 사용하면 Move()에서 사용하는 Hide, Show는 Point클래스의 맴버 함수를 호출하게되어,
    //Circle은 정상적인 Move가 되지 않는다.


	void Move(int nx, int ny) {				// Move 함수는 모든 도형에 대해 똑같은 알고리즘을 갖으므로 , 가상함수일 필요가 없다.
		Hide();			//이 경우 Move에서 호출하는 Show, Hide는 포인터와 상관없이 그냥 단순히 멤버 함수를 호출하는 것처럼 보인다.
						//이런 의심이 가는 사람은 잠시 깜박한 것이 있는데 모든 멤버 함수들에게 숨겨진 this가 전달되고 
		x = nx;			//멤버 함수 내에서 멤버의 참조문앞에는 암시적으로 this->가 숨겨져 있다는 것을 상기해 보자. this는 분명히 호출 객체의 포인터이므로 
		y = ny;			//이 포인터로부터 호출되는 Show, Hide 가상 함수는 동적 결합되어야 마땅하다.
		Show();
	}

	//그렇다면 Move 함수를 가상으로 선언하는 것은 어떤 효과가 있을까? 직접 테스트해 보면 알겠지만 Move가 가상인 것은 문제 해결에 아무런 도움이 되지 않는다. 
	//Move의 코드는 어차피 같으므로 어떤 클래스의 멤버 함수가 결합되나 전혀 다르지 않다. 
	//중요한 것은 객체별로 달라야 하는 동작인 Show, Hide가 동적 결합을 하느냐 아니냐이다.

	//멤버 함수내에서 세부 구현을 위해 호출되어야 하는 또 다른 멤버 함수가 클래스별로 다르게 정의되어 있다면 이 함수도 가상 함수가 되어야 한다.
	//그래야 암시적으로 전달되는 this객체의 타입에 따라 정확한 함수가 호출된다.
};



class Circle : public Point
{
protected:
	int Rad;

public:
	Circle(int ax, int ay, char ach, int aRad) : Point(ax, ay, ach) { Rad = aRad; }

	virtual void Show() 
	{
		for (double a = 0; a < 360; a += 15) 
		{
			gotoxy(int(x + sin(a * 3.14 / 180) * Rad), int(y - cos(a * 3.14 / 180) * Rad));
			_putch(ch);
		}
	}

	virtual void Hide() 
	{
		for (double a = 0; a < 360; a += 15)
		{
			gotoxy(int(x + sin(a * 3.14 / 180) * Rad), int(y - cos(a * 3.14 / 180) * Rad));
			_putch(' ');
		}
	}
};



int main()
{
	Point P(1, 1, 'P');
	Circle C(10, 10, 'C', 5);


	P.Show();
	C.Show();

	//엔터 누르면 움직임.
	_getch();
	P.Move(40, 1);
	_getch();
	C.Move(40, 10);
	_getch();

	return 0;
}