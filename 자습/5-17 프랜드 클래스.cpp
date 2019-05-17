#include <iostream>
using namespace std;

/*
두 클래스가 아주 밀접한 관련이 있고 서로 숨겨진 멤버를 자유롭게 읽어야 하는 상황이라면 클래스를 통째로 프렌드로 지정할 수 있다.
클래스 선언문내에 프렌드로 지정하고 싶은 클래스의 이름을 밝히면 된다.다음 예는 Any 클래스를 Some 클래스의 프렌드로 지정하는 것이다.
*/
class Time
{
	 friend class Date;
private:
	 int hour,min,sec;
public:
	 Time(int h,int m,int s) { hour = h; min = m; sec = s; }
};



class Date
{
private:
	int year, month, day;

public:
	Date(int y, int m, int d) { year = y; month = m; day = d; }

	void OutToday(Time& t)
	{
		printf("오늘은 %d년 %d월 %d일이며 지금 시간은 %d:%d:%d입니다.\n",
			year, month, day, t.hour, t.min, t.sec);

	}
};



void main()
{
	Date D(2005, 01, 02);
	Time T(12, 34, 56);
	D.OutToday(T);
}