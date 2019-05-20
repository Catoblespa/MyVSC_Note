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


class MathCalc
{
private:
	static const double pie;			//static const화 할경우, 한번 정해진 값은 변경 할수 없고, 모든 객체에서 공유하는 변수가 된다!
  //static const double pie = 3.1416;	//최근에 들어서 이렇게 초기화 하는것도 가능하지만, 이전 컴파일러에서는 지원 안할수도 있다.

public:
	MathCalc() { }
	void DoCalc(double r) 
	{
		printf("반지름 %.2f인 원의 둘레 = %.2f\n", r, r * 2 * pie);
	}

};

const double MathCalc::pie = 3.1416;
//정적 멤버는 클래스 외부에서 다시 한 번 더 정의해야 하며 이때 초기값을 주는데 일반 정적 멤버와는 달리 상수 멤버는 선언할 때 초기값을 반드시 지정해야 한다.


// 상수가 객체별로 다른 값을 가져야 한다면 이때 쓸 수 있는 유일한 방법은 생성자의 초기화 리스트뿐이다.
//Enemy 클래스는 게임의 적군을 표현하는 클래스인데 각 객체별로 고유한 속도를 가지되 한 번 정해진 속도가 객체 내에서 불변이라면 Speed라는 상수 멤버를 선언한다. 
//그리고 객체가 생성될 때 생성자를 통해 딱 한 번만 초기화한다.
class Enemy
{
private:
	const int Speed;

public:
	Enemy(int aSpeed) : Speed(aSpeed) { }
	void Move() 
	{

		printf("%d의 속도로 움직인다.\n", Speed);

	}

};




//----------------------------------------------------------------------------------------------------------------------------------------------
class Some
{

private:
	int Value;

public:
	int SetValue(int aValue);       // 비상수 멤버 함수
	int GetValue() const;           // 상수 멤버 함수
									//클래스 선언문의 함수 원형 뒤쪽에 const 키워드를 붙이면 상수 멤버 함수가 된다.
									//함수의 앞쪽에서는 리턴값의 타입을 지정하기 때문에 const를 함수 뒤에 붙이는 좀 별난 표기법을 사용한다.
	//이때 GetValue는 객체의 어떠한 멤버값도 변경하지 않으므로 상수 멤버 함수이며
	//이 함수 원형 뒤에 const를 붙여 GetValue는 값을 읽기만 한다는 것을 컴파일러에게 확실하게 알려 준다.
};


class Position
{
private:
	int x, y;
	char ch;

public:
	Position(int ax, int ay, char ach) { x = ax; y = ay; ch = ach; }
	void OutPosition() const { gotoxy(x, y); putch(ch); }				//단순히 값으 읽기만 하는 함수로, const화 한다.
	void MoveTo(int ax, int ay) { x = ax; y = ay; }						//x,y값을 변경하는 함수이기 떄문에 const화 하기 부적절한 함수
																		//맘ㄴ약 MoveTo 함수에서 값을 변경하려 하면 에러가 뜨게 된다.
	// ****멤버 함수라도 정적 멤버 변수의 값은 변경할 수 있는데 정적 멤버는 객체의 소속이 아니며 객체의 상태를 나타내지도 않기 때문이다.

	//비상수 멤버 함수가 받는 객체 포인터 this는 Position * const 형이며 this 자체는 상수이지만 this가 가리키는 대상은 상수가 아니다.
	//하지만 상수 멤버 함수가 받는 객체 포인터 this는 const Position * const 형이며 this도 상수이고 this가 가리키는 대상도 상수이다. 
	//결국 상수 멤버 함수의 제일 끝에 붙는 const는 이 함수로 전달되는 숨겨진 인수 this의 상수성을 지정한다.


};





int main()
{

	MathCalc M;
	M.DoCalc(5);


	Enemy E1(10), E2(20);
	E1.Move();
	E2.Move();


	//-------------------------------------



	Position Here(1, 2, 'A');
	Here.MoveTo(20, 5);
	Here.OutPosition();


	const Position There(3, 4, 'B');
	//There.MoveTo(40, 10);           // 에러 발생
	There.OutPosition();
	// 만약 OutPosition()에서 const를 제거하여 선언할 경우 There.OutPosition();가 에러 처리 된다.
	// 왜냐하면 OutPosition이 상수맴버 함수가 아닐 경우 상수 객체인 There의 변수를 변경할지도 모른다고 생각 하기 떄문이다.
	// 그러므로 어떤 멤버 함수가 값을 읽기만 하고 바꾸지는 않는다면 const를 붙이는 것이 원칙이며 이 원칙대로 클래스를 작성해야 한다.


	//*****
	//	void func(const Position * Pos);
	//	이 함수로 전달되는 Pos는 상수 지시 포인터이므로* Pos는 func 함수 안에서 상수 객체이다.
	//따라서 Pos 객체에 대해서는 상수 멤버 함수만 호출할 수 있다.
	//MoveTo로 위치를 옮길 수 없으며 OutPosition 이 상수 멤버 함수로 지정되어 있지 않다면 문자를 출력하는 것도 불가능해진다
	//.이런 경우에도 잘 동작하려면 원칙대로 멤버값을 바꾸지 않는 함수는 상수 멤버 함수로 지정해야 한다.


	return 0;
}
