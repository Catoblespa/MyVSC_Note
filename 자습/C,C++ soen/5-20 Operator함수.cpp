#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>


using namespace std;

/*
http://soen.kr/lecture/ccpp/cpp3/28-1-3.htm
http://soen.kr/lecture/ccpp/cpp3/28-2-3.htm     // 연산자 오버로딩의 규칙   

① 클래스의 멤버 함수로 작성한다.
② 전역 함수로 작성한다.

우선 상대적으로 좀 더 간단한 멤버 연산자 함수를 작성하는 형식부터 알아보자. 
전역 함수로 작성하는 방법에 대해서는 다음 절에서 상세하게 알아볼 것이다. 
멤버 연산자 함수의 기본 형식은 다음과 같다.



리턴타입 Class::operator 연산자(인수 목록)
{
		  함수 본체;
}


*/

class Time
{
private:
	int hour, min, sec;

public:

	Time() { }

	Time(int h, int m, int s) { hour = h; min = m; sec = s; }

	void OutTime() 
	{
		printf("%d:%d:%d\n", hour, min, sec);
	}

	//const Time : 리턴 타입
	//operator + : 함수 이름
	//const Time& T : 피연산자(인수)
	//const : 상수 함수.
	const Time operator +(const Time& T) const		//외부에서 정의 할경우 Complex::operator + 등으로 소속 클래스 이름도 밝혀야 한다.
	{												//+연산을 할떄 +의 좌측이 함수를 호출하는 객체, 우변이 연산자 함수로 전달되는 객체이다.
					//객체는 값으로 넘길 수도 있지만 아무래도 기본형보다는 덩치가 크기 때문에 값으로 넘기면 비효율적이므로 레퍼런스로 넘기는 것이 유리하다.
		Time R;									//포인터로 넘겨도 가능하다  그러나 연산자 함수가 포인터를 받아들이면 이 함수를 호출할 때 피연산자의 
												//주소를 넘겨야 하므로 호출부의 모양이 C3=C1.operator +(&C2);가 될 것이고
												//이를 연산식으로 표현하면 C3=C1+&C2; 가 되는데 이런 형식은 연산문의 일반적인 표기법에 어긋나며 
												//전혀 직관적이지 못하다.
		R.sec = sec + T.sec;
		R.min = min + T.min;					//해당 operator함수는 this의 값을 참조만 할뿐, 변경하지 않으므로, 상수맴버 함수로 정의하는게 좋다.
		R.hour = hour + T.hour;					// 반환도 값또한 상수로 넘겨준다.



		R.min += R.sec / 60;
		R.sec %= 60;
		R.hour += R.min / 60;
		R.min %= 60;
		return R;
	}

    
};



void main()
{

	Time A(1, 30, 41);

	Time B(5, 31, 10);

	Time C;



	A.OutTime();

	B.OutTime();

	C = A+B;

	C.OutTime();
}

/*
//===========================================상수 오퍼레이터========================================================================
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>


using namespace std;



class Time
{
	friend	const Time operator +(int s, const Time& T);

private:

	int hour, min, sec;



public:

	Time() { }

	Time(int h, int m, int s) { hour = h; min = m; sec = s; }

	void OutTime() 
	{
		printf("%d:%d:%d\n", hour, min, sec);
	}

	const Time operator +(int s) const
	{

		Time R = *this;

		R.sec += s;

		R.min += R.sec / 60;
		R.sec %= 60;
		R.hour += R.min / 60;
		R.min %= 60;
		return R;

	}




};

const Time operator +(int s, const Time& T)
{
	//Time R = T;
	//R.sec = T.sec + s;
	//R.min += R.sec / 60;
	//R.sec %= 60;
	//R.hour += R.min / 60;
	//R.min %= 60;

	//return R;

	//인수로 전달받은 s, T의 순서를 바꿔 T+s 연산문을 리턴하면 멤버 연산자 함수가 이 연산을 대신 처리할 것이다. 
	//이 경우 전역 연산자 함수는 인수의 순서를 바꿔 멤버 연산자 함수를 호출하는 중계 역할만 하며 아주 정상적으로 잘 실행된다. 
	//이렇게 되면 전역 연산자 함수가 Time의 멤버를 직접 액세스하지 않으므로 이 함수에 대한 프렌드 지정은 생략할 수 있다. 
	//하지만 이 함수는 여전히 Time과 관련된 함수이므로 프렌드 지정을 유지하는 것도 별 문제는 없다.
	//전역 연산자 함수가 중계를 하는 방법 대신 멤버 연산자 함수가 중계를 할 수도 있다

	return T + s;
}

void main()

{

	Time A(1, 2, 3);



	A.OutTime();

	A = 5 + A;

	A.OutTime();
}
*/