#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>


using namespace std;

class Date
{
protected:
	int year, month, day;

public:
	Date(int y, int m, int d) { year = y; month = m; day = d; }
	void OutDate() { printf("%d/%d/%d", year, month, day); }
};



class Time
{
protected:
	int hour, min, sec;

public:
	Time(int h, int m, int s) { hour = h; min = m; sec = s; }
	void OutTime() { printf("%d:%d:%d", hour, min, sec); }
};



class Now : public Date, public Time		//Date , Time 클래스를 다중 상속 받는다.
{
private:
	bool bEngMessage;		// 메시지를 출력할 언어를 지정하는 bEngMessage
	int milisec;			//1/100초 단위의 좀 더 정밀한 시간까지 표현하기 위한 milisec 멤버를 더 정의

public:
	Now(int y, int m, int d, int h, int min, int s, int ms, bool b = FALSE) : Date(y, m, d), Time(h, min, s) 
	{
		milisec = ms; bEngMessage = b;
	}
	// Now 클래스는 Date, Time 순으로 상속 받았으므로 Date -> TIme 순으로 초기화 리스트가 호출 된다.
	// 이 순서는 Now의 초기화 리스트 순서가 아니라 , Now 가 상속 받을때 왼쪽에서 오른쪽 순서로 받는 다는것을 유의해라.
	void OutNow()		
	{
		printf(bEngMessage ? "Now is " : "지금은 ");
		OutDate();		//Date에게 상속받은 함수

		_putch(' ');
		OutTime();		//Time에게 상속받은 함수

		printf(".%d", milisec);
		puts(bEngMessage ? "." : " 입니다.");
	}
};



void main()
{

	Now N(2005, 1, 2, 12, 30, 58, 99);
	N.OutNow();
}