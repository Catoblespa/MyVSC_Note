#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>


using namespace std;

/*
	연산자 함수를 전역으로 정의하는 법.

*/

class Time
{

	friend const Time operator+(const Time& T1, const Time& T2);
	// 전역에 있는 operator+ 함수에 friend를 걸어 operator가 private 맴버에 접근 할 수 있게 한다.
private:

	int hour, min, sec;



public:

	Time() { }

	Time(int h, int m, int s) { hour = h; min = m; sec = s; }

	void OutTime() {

		printf("%d:%d:%d\n", hour, min, sec);

	}

};



const Time operator+(const Time& T1, const Time& T2)
{
	Time R;

	R.sec = T1.sec + T2.sec;
	R.min = T1.min + T2.min;
	R.hour = T1.hour + T2.hour;

	R.min += R.sec / 60;
	R.sec %= 60;
	R.hour += R.min / 60;
	R.min %= 60;

	return R;

}


enum origin { EAST, WEST, SOUTH, NORTH };
origin& operator++(origin& o)
{
	if (o == NORTH) 
	{
		o = EAST;
	}
	else 
	{
		o = origin(o + 1);
	}

	return o;
}

void main()
{
	Time A(1, 1, 1);
	Time B(2, 2, 2);
	Time C;



	A.OutTime();
	B.OutTime();
	C = A + B;
	C.OutTime();



	origin mark = WEST;

	int i;

	for (i = 0; i < 7; i++) 
	{
		printf("%d\n", ++mark);
	}
	//	예제의 ++ 연산자는 origin형의 열거 변수를 다음값으로 증가시키되 마지막 열거값 다음을 선두의 열거값과 연결하여 순환하도록 한다.
	// 이 연산자가 정의되어 있지 않으면 열거형에 대해서는 ++연산을 적용할 수 없다.루프를 7번 실행했는데 NORTH 다음 값이 EAST가 될 것이다.

}