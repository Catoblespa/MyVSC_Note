#include <iostream>
using namespace std;


/*
프렌드 클래스 지정은 특정 클래스의 모든 멤버 함수들이 자신의 숨겨진 멤버를 마음대로 읽도록 허락하는 것이다. 
멤버 함수의 수가 많을 경우 모든 멤버 함수들이 대상 클래스의 멤버를 액세스할 필요가 없음에도 불구하고 허용의 범위가 너무 넓어져 위험해진다. 
프렌드 멤버 함수는 특정 클래스의 특정 멤버 함수만 프렌드로 지정하는 것이며 꼭 필요한 함수에 대해서만 숨겨진 멤버를 액세스하도록 범위를 좁게 설정할 수 있는 장점이 있다.
*/

class Time;

class Date
{
private:
	int year, month, day;

public:
	// Date함수를 전역변수가 아닌 맴버 함수로 선언
	Date(int y, int m, int d) { year = y; month = m; day = d; }
	void OutToday(Time& t);

};



class Time
{
	//Date클래스의 OutToday 함수를 friend로 받아온다.
	//이렇게 하면 Date클래스의 OutToday는 Time의 맴버 변수를 사용할수 있게된다.
	//단, Time의 또 다른 맴버 함수에서는 사용할수 없다.
	//프랜드 클래스와 효과는 같지만, Time의 맴버변수를 하나의 프랜드 함수에서만 사용 가능 하게 하므로, Time의 맴버변수가 Date클래스에 의해 
	//  마구 쓰이지 않도록 제한 할 수있다.
	friend void Date::OutToday(Time& t);		//즉 이 구문은 : Date클래스의 OutToday에게 Time클래스의 맴버 변수 사용을 허락한다! 정도로 해석가능하다.	

private:
	int hour, min, sec;

public:
	Time(int h, int m, int s) { hour = h; min = m; sec = s; }

};



// Date의 맴버 함수이다.
void Date::OutToday(Time& t)
{

	printf("오늘은 %d년 %d월 %d일이며 지금 시간은 %d:%d:%d입니다.\n",
		year, month, day, t.hour, t.min, t.sec);
}



void main()
{
	Date D(2005, 01, 02);
	Time T(12, 34, 56);
	D.OutToday(T);
}