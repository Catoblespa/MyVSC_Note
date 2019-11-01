#include <iostream>
#include <string.h>
using namespace std;

// 변환 생성자 -----------------------------------------------------------------------------------------------------------
class Time
{
private:
	int hour, min, sec;

public:
	Time() { }
	

	//변환 생성자
	//만약 변환 생성자가 있을경우 객체를 인수로 전달해야하는데, 잘못해서 정수를 넣을경우,
	// 컴파일에 문제가 없기때문에 나중에 찾아내기 어려운 버그임.
	//explicit 은 인수로 받는 int에 대해 암묵적 형변환을 막는다. , 단 명시적 형변환은 사용가능하다.
	explicit Time(int abssec)
	{
		hour = abssec / 3600;
		min = (abssec / 60) % 60;
		sec = abssec % 60;
	}
	//여러개의 변환 생성자 사용가능.
	explicit Time(double d)
	{
		hour = int(d) % 24;
		min = int((d - int(d)) * 100) % 60;
		sec = 0;
	}

    //만약 초단위로 받는게 아닌, 시 분 초를 따로 초기화 할경우
    Time(int h, int m, int s) { hour=h; min=m; sec=s; }
	//변환 함수 : 변환 생성자의 반대로, hour min sec을 모두 연선하여 총 sec를 반환시킨다.
	//변환 함수 또한, 변환 생성자 처럼 여러개 선언해도 된다.
	//Time 객체를 실수나 문자형으로도 변환하도록 하고 싶다면 operator double(), operator char() 함수를 더 정의하면 된다.
    //operator int()  // ****그러나 변환 함수 또한, 변환 생성자와 같이 암시적 형변환에 대해 위험성이 있다.
	//{				//그러나 explicit같은 보호 대책이 없음. 그러므로 변환 함수보단 아래와 같은 함수를 만들어 쓰도록 한다.
    //    return hour*3600+min*60+sec;
    //}


	// 명시적 변환 함수.
	int TimeToInt() 
	{
		return hour * 3600 + min * 60 + sec;
	}

	// 변환 생성자를 쓰는것도 좋지만, 이렇게 쓰는게 더 안전하다.
	void IntToTime(int abssec) 
	{
		hour = abssec / 3600;
		min = (abssec / 60) % 60;
		sec = abssec % 60;
	}

	void OutTime()
	{
		printf("현재 시간은 %d:%d:%d입니다.\n", hour, min, sec);
	}	
};

void main()
{
	Time Now(3723);		//직접 호출
	//Time Now2 = 3723;	//간접 호출	//변환 생성자일 경우 가능.  * explicit으로 암묵적 형변환을 금지할경우 아래와 같이 사용해야한다.
	Time Now2 = (Time)3723;	//explicit 사용할경우 간접호출.
						//int와 Time은 원래 호환되지 않지만 변환 생성자가 정의되어 있으면 컴파일러에 의해 자동 변환된다.
						//변환생성자가 있을 경우 처음 초기화 때 뿐만아니라, 언제든지 Time을 변경 할 수 있다. 
						
	Now.OutTime();
}