#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>


using namespace std;

/*
한 클래스를 간접적으로 두 번 상속받을 경우 이 클래스의 멤버가 중복되어 메모리가 낭비되고 어떤 멤버를 칭하는지 알 수 없는 모호함이 발생한다는 것이다. 
이 문제를 해결하려면 한 클래스를 두 번 상속받더라도 이 클래스의 멤버들은 한 번만 상속하도록 하면 된다.

이런 클래스를 가상 기반 클래스(Virtual Base Class)라고 하는데 이렇게 지정된 클래스는 간접적으로 두 번 상속되더라도 결과 클래스에는 자신의 멤버를 한 번만 상속시킨다.
가상 기반 클래스를 지정할 때는 상속문의 기반 클래스앞에 virtual이라는 키워드를 쓴다. 
virtual 키워드와 상속 액세스 지정자의 순서는 무관하되 virtual을 먼저 지정하는 것이 보통이다.
*/


void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


class A
{
protected:
	 int a;

public:
	 A(int aa) { a = aa; }
	 A();
};

class B : virtual public A					//B와 C를 A로부터 파생시킬 때 A를 가상 기반 클래스로 지정했다
{											//양쪽 다 virtual 상속을 해야 하며 한쪽만 virtual 상속하면 효과가 없다. 
protected:									//이 상태에서 B와 C로부터 다중 상속을 받으면 A의 멤버가 한 번만 나타나며 결과 클래스인 D에 a 멤버는 하나만 존재한다.
	int b;									//A가 다중상속 중 중첩 상속되는 클래스 일경우 A를 직접적으로 상속 받는 클래스들은 A를 Virtual로 받아야한다.
											//
public:
	B(int aa, int ab) : A(aa) { b = ab; }

};

class C : virtual public A				//B와 C클래스는 직접적으로 A를 상속 받으로 virtual 로 받는다.
{
protected:
	int c;

public:
	C(int aa, int ac) : A(aa) { c = ac; }

};


class D : public B, public C
{
protected:
	int d;

public:
	//D(int aa, int ab, int ac, int ad) : B(aa, ab), C(aa, ac) { d = ad; }	
	D(int aa, int ab, int ac, int ad) : A(aa), B(aa, ab), C(aa, ac) { d = ad; }
	// A클래스를 간접적으로 중복하여 상속 받을경우 A의 초기화 리스트를 추가해야한다.

	void fD() 
	{
		b = 1;
		c = 2;
		a = 3;         // 가상기반클래스를 사용하지 않을 경우 여기서 문제 발생!
					   // => B클래스와 C클래스 모두에 a가 작성되어 있으므로 모호함이 발생한다.
	}

};





//=================================================================================================================










// CirMessage 의 상속 테이블
/*
	Coord
   /    \
Point    \
 ㅣ       \
Circle	Message
  \       /
   \     /
  CirMessage
*/



class Coord
{
protected:
	int x, y;

public:

	Coord(int ax, int ay) { x = ax; y = ay; }
	void GetXY(int& rx, int& ry) const { rx = x; ry = y; }
	void SetXY(int ax, int ay) { x = ax; y = ay; }

};



class Point : virtual  public Coord
{
protected:
	char ch;

public:
	Point(int ax, int ay, char ach) : Coord(ax, ay) { ch = ach; }
	void Show() {gotoxy(x, y); _putch(ch);}
	void Hide() {gotoxy(x, y); _putch(' ');}
};



class Circle : public Point
{
protected:
	int Rad;

public:
	Circle(int ax, int ay, char ach, int aRad) : Coord(ax, ay), Point(ax, ay, ach) { Rad = aRad; }
	//

	void Show() 
	{
		for (double a = 0; a < 360; a += 15) 
		{
			gotoxy(int(x + sin(a * 3.14 / 180) * Rad), int(y - cos(a * 3.14 / 180) * Rad));
			_putch(ch);
		}
	}

	void Hide() 
	{
		for (double a = 0; a < 360; a += 15)
		{
			gotoxy(int(x + sin(a * 3.14 / 180) * Rad), int(y - cos(a * 3.14 / 180) * Rad));
			_putch(' ');
		}
	}
};



class Message :virtual public Coord
{
private:
	char Mes[128];

public:
	Message(int ax, int ay,const char* M) : Coord(ax, ay) 
	{
		strcpy_s(Mes,sizeof(Mes), M);
	}

	void Show() 
	{
		gotoxy(x - strlen(Mes) / 2, y);
		puts(Mes);
	}
};



class CirMessage : public Circle, public Message
{
public:
	CirMessage(int ax, int ay, char ach, int aRad, int mx, int my,const char* M) :Coord(ax, ay), Circle(ax, ay, ach, aRad), Message(mx, my, M) { }

	//Coord를 직접 상속받는 Point, Message 클래스의 선언문에 virtual 키워드를 삽입하고 
	//간접적으로 상속받는 Circle, CirMessage 클래스의 생성자에서는 Coord의 생성자를 명시적으로 호출해야 한다. 
	//이렇게 하면 CirMessage는 Coord를 한 번만 상속받게 되며 이 클래스의 멤버 함수는 별다른 지정없이 x, y 멤버를 바로 액세스할 수 있다.
public:
	void Show() 
	{
		Circle::Show();
		Message::Show();
	}
};

// CirMessage 의 상속 테이블
/*
    Coord
   /    \
Point    \
 ㅣ       \
Circle	Message
  \       /
   \     /
  CirMessage
*/


int main()
{

	D d(1, 2, 3, 4);

	CirMessage CM(10, 10, '.', 8, 40, 15, "테스트");

	CM.Show();

	return 0;
}