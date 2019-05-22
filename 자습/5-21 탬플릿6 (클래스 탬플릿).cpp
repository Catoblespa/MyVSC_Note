#include <iostream>
#include <Windows.h>

using namespace std;

/*
http://soen.kr/lecture/ccpp/cpp3/31-2-2.htm
탬플릿 함수 , 클래스를 분할하여 작성할때 참고할것.
export에 대해서도 설명되어 있음.
*/

/*
클래스 템플릿은 함수 템플릿과 비슷하되 찍어내는 대상이 클래스라는 것만 다르다.

구조나 구현 알고리즘은 동일하되 멤버들의 타입만 다를 경우 클래스를 일일이 따로 만드는 대신 템플릿을 정의한 후 템플릿으로부터 클래스를 만들 수 있다.
 정보의 타입에 따라 값을 표현하는 멤버의 타입이 달라지므로 타입에 따라 클래스를 일일이 만들어야 한다.

클래스가 객체를 만드는 빵틀이라면, 템플릿 클래스는 클래스라는 빵틀을 만드는 기계와 같다.
*/

void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

template <typename T>			// 이렇게 정의된 클래스 타입의 객체를 생성할 때 클래스 이름 다음의 < > 괄호안에 원하는 타입을 밝혀야 한다. 
class PosValue					//템플릿 클래스의 타입명에는 < > 괄호가 항상 따라 다닌다.
{								// value가 int형인 클래스의 이름은 PosValue<int>이고 value가 char형인 클래스의 이름은 PosValue<char>이다.
private:
	int x, y;
	T value;

public:
	PosValue(int ax, int ay, T av) : x(ax), y(ay), value(av) { }		// 생성자는 <T>를 붙이지 않아도 된다. 일반적으로 안붙힘.
	void OutValue();

};

template class PosValue<int>;		 //명시적 클래스 구체화
									 //이순간부터 int를 갖는 탬플릿 클래스 PosValue가 정의 된것.
									//선언에 의해 컴파일러는 PosValue<int> 클래스를 미리 생성한다. 



//클래스 템플릿의 멤버 함수를 선언문 외부에서 작성할 때는 템플릿에 속한 멤버 함수임을 밝히기 위해 소속 클래스의 이름에도 <T>를 붙여야 하며
//T가 템플릿 인수임을 명시하기 위해 template <typename T>가 먼저 와야 한다
template <typename T>
void PosValue<T>::OutValue()
{
	gotoxy(x, y);
	cout << value << endl;		//value 변수가 T형이므로 template <typenameT T> 를 해야함.
}



//탬플릿 클래스가 아닐때, 탬플릿 함수를 맴버함수로 갖는경우
//클래스가 탬플릿일 경우와 
class Some
{
private:
	int mem;

public:
	Some(int m) : mem(m) { }

	template <typename T>
	void memfunc(T a) 
	{
		cout << "템플릿 인수 = " << a << ", mem = " << mem << endl;
	}

};


int main()
{
	PosValue<int> iv(1, 1, 2);		//템플릿 클래스로부터 객체를 선언할 때는 템플릿 이름 다음에 < >괄호를 쓰고 괄호안에 T로 전달될 타입의 이름을 명시해야 한다.
	PosValue<char> cv(5, 1, 'C');
	PosValue<double> dv(30, 2, 3.14);
	iv.OutValue();
	cv.OutValue();
	dv.OutValue();



	Some s(9999);

	s.memfunc(1234);
	s.memfunc(1.2345);
	s.memfunc("string");

	return 0;
}


/*
컴파일러는 객체 선언문에 있는 초기값의 타입으로부터 어떤 타입에 대한 클래스를 원하는지 알 수 있을 것도 같다. 
예를 들어 PosValue iv(1,1,2)라고 쓰면 제일 마지막 인수가 int형 상수이므로 PosValue<int> 타입이라고 유추 가능할 것이다. 
그러나 생성자가 오버로딩되어 있을 경우 이 정보만으로는 원하는 타입을 정확하게 판단하기 어렵다. 
또한 생성자를 호출하기 전에 객체를 위한 메모리를 할당해야 하는데 이 시점에서 생성할 객체의 크기를 먼저 계산할 수 있어야 하므로 클래스 이름에 타입이 명시되어야 한다.
*/