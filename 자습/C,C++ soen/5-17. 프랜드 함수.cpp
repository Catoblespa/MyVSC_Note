#include <iostream>
using namespace std;

/*
 프렌드 지정을 하는 대신 각 클래스에 숨겨진 멤버를 대신 읽어주는 Get, Set 액세스 함수를 공개 영역에 작성하고 OutToday는 액세스 함수들로 값을 읽을 수도 있다. 
 하지만 이런 방법이 번거롭고 귀찮기 때문에 프렌드 지정이라는 좀 더 간편한 방법을 사용하는 것이다.
*/


class Date;		// OutToday함수는 Date클래스와 Time 클래스를 모두 인자로 받는다.
				// Time 클래스가 Date 클래스위 위에 선언 되어 있는데, Time클래스에서 OutTodat를 프랜드화 하기위해서
				//Date가 밑에 정의 되어 있다는 것을 알리기 위해 Date 클래스를 전방선언 했다.
class Time
{
	//클래스엣 friend 함수를 선언! 정의는 class 내부에 되어 있지만, 사실상 전역함수 OutToday에서는 private변수를 사용 할 수 있게 해주는 문구이다.
	friend void OutToday(Date&, Time&);
private:
	int hour, min, sec;

public:
	Time(int h, int m, int s) { hour = h; min = m; sec = s; }

};



class Date
{
	friend void OutToday(Date&, Time&);
private:
	int year, month, day;

public:
	Date(int y, int m, int d) { year = y; month = m; day = d; }

};


// :: 지정자 없이 정의한다.  프랜드 변수는 맴버 함수가 아니라, 단순 전역함수이다.
// OutToday 함수는 Date클래스와 Time 클래스 모두의 private에 접근해야 하기 때문에, 양 클래스 모두 friend화 해주었다.
void OutToday(Date& d, Time& t)
{
	printf("오늘은 %d년 %d월 %d일이며 지금 시간은 %d:%d:%d입니다.\n",
		d.year, d.month, d.day, t.hour, t.min, t.sec);
}

void main()
{
	Date D(2005, 01, 02);
	Time T(12, 34, 56);
	OutToday(D, T);
}