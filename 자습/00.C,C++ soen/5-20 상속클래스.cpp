#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>


using namespace std;

/*
액세스 지정자		클래스 외부		파생 클래스		설명

private			액세스 금지		액세스 금지		무조건 금지

protected		액세스 금지		액세스 허용		파생 클래스만 허용

public			액세스 허용		액세스 허용		무조건 허용

*/


void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


class Coord
{
protected:
	int x, y;

public:
	Coord(int ax, int ay) { puts("Coord 생성자"); x = ax; y = ay; }
	void GetXY(int& rx, int& ry) const { rx = x; ry = y; }
	void SetXY(int ax, int ay) { x = ax; y = ay; }
};


class Point : public Coord
{
protected:
	char ch;

public:
	Point(int ax, int ay, char ach) : Coord(ax, ay) {puts("Point 생성자");ch = ach;}
	//상속받은 멤버는 파생 클래스에서 직접 초기화할 수 없으며 기반 클래스에게 초기화를 부탁해야 한다.
	//파생 클래스는 기반 클래스의 모든 멤버를 상속받기는 하지만 이 멤버를 어떻게 초기화해야 하는지는 정확하게 알지 못한다. 
	//또한 상속받은 멤버 중 일부는 private 액세스 속성을 가질 수도 있으므로 파생 클래스가 이 멤버를 초기화할 권한이 없다.
	//생성자는 항상 public이므로 누구나 호출할 수 있다.
	
	void Show()
	{
		gotoxy(x, y); _putch(ch);
	}

	void Hide()
	{
		gotoxy(x, y); _putch(' ');
	}

};



class Circle : public Point
{

protected:
	int Rad;

public:

	Circle(int ax, int ay, char ach, int aRad) : Point(ax, ay, ach) {puts("Circle 생성자"); Rad = aRad; }
	//초기화 리스트를 통해 기반 클래스의 생성자를 연쇄적으로 호출하며 상속받지 않은 멤버는 자신이 직접 초기화한다. 
	//일반적으로 기반 클래스는 파생 클래스가 동작하기 위한 전제 조건이 되기 때문에 파생 클래스의 멤버보다 상속받은 멤버가 먼저 초기화되어야 한다. 
	//가령 파생 클래스의 생성자 본체에서부터 상속받은 멤버를 당장 참조할 수도 있으므로 생성자 본체보다도 기반 클래스의 초기화가 더 우선이다.
	// **  생성자 본체가 실행되기 전에 상속받은 멤버는 초기화되어야 하며 그러기 위해서는 초기화 리스트를 사용하는 방법밖에 없다. **

	/*
	Circle(int ax, int ay, char ach, int aRad)		 이 코드는 전혀 일반적이지 않다. 
	{												 왜냐하면 대입은 초기화와 여러 가지 면에서 다르며 상속받은 멤버를 파생 클래스가 항상 마음대로 액세스할 수 있는 것도 아니기 때문이다. 
     x=ax;y=ay;ch=ach;								 만약 Coord나 Point가 x, y, ch를 protected가 아닌 private로 정의하고 있다면 이 코드는 컴파일되지 않는다.
     Rad=aRad;
	}
	파생 클래스의 초기화 리스트에서 기반 클래스의 생성자를 호출하지 않으면 이때는 기반 클래스의 디폴트 생성자가 호출되는데
	만약 기반 클래스가 디폴트 생성자를 정의하지 않는다면 에러로 처리된다.
	*/
	void Show() 
	{
		for (double a = 0; a < 360; a += 10) 
		{
			gotoxy(int(x + sin(a * 3.14 / 180) * Rad), int(y - cos(a * 3.14 / 180) * Rad));
			_putch(ch);
		}
	}

	void Hide() 
	{
		for (double a = 0; a < 360; a += 10)
		{
			gotoxy(int(x + sin(a * 3.14 / 180) * Rad), int(y - cos(a * 3.14 / 180) * Rad));
			_putch(' ');
		}
	}
};



void main()
{
	//각 클래스의 생성자와 main 함수에 실행 순서 확인을 위한 문자열 메시지 출력문을 삽입해 놓았다. 
	//실행 결과는 다음과 같은데 각 객체 선언시마다 선조 클래스의 생성자들이 순서대로 호출된다는 것을 분명히 확인해 볼 수 있다
	Point P(10, 10, '@');
	P.Show();

	Circle C(40, 10, '*', 8);
	C.Show();

}