#include <iostream>
#include <Windows.h>

using namespace std;


void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

template <typename T>
class PosValue
{
private:
	int x, y;
	T value;

public:
	PosValue(int ax, int ay, T av) : x(ax), y(ay), value(av) { }
	void OutValue();

};

template <typename T>
void PosValue<T>::OutValue()
{
	gotoxy(x, y);
	cout << value << endl;
}


//명시적 구체화
//template class CLASS_NAME<TYPE>;
template class PosValue<int>;

struct tag_Friend {
	char Name[10];
	int Age;
	double Height;
};


//특수화
//template<> class CLASS_NAME<TYPE>  {...}
// tag_Friend 타입의 PosValue class 특수화.
// 탬플릿 클래스는 변수타입과 마찬가지로, 구조체나 클래스를 받을 수도 있다.
//tag_Friend 구조체 타입에 대한 PosValue 클래스를 작성하려면 이 타입에 대한 특수화된 버전을 만들고 OutValue 함수의 코드를 조금 다르게 작성할 필요가 있다.
//특수화를 할 때는 다음 형식으로 클래스를 정의한다.
template <> class PosValue<tag_Friend>
{
private:
	int x, y;
	tag_Friend value;

public:
	PosValue(int ax, int ay, tag_Friend av) : x(ax), y(ay), value(av) { }
	void OutValue();

};

void PosValue<tag_Friend>::OutValue()		// 바뀐 OutValue 함수.
{
	gotoxy(x, y);
	cout << "이름:" << value.Name << ", 나이:" << value.Age
		<< ", 키:" << value.Height << endl;
}



//특수화를 하면 특수화된 클래스는 객체를 선언하지 않더라도 자동으로 구체화된다.
//즉, 클래스 정의가 만들어지고 멤버 함수들은 컴파일되어 실행 파일에 포함된다.
//따라서 특수화된 클래스에 대한 정의는 일반적인 템플릿 클래스와는 달리 헤더 파일에 작성해서는 안되며 구현 파일에 작성해야 한다.

//이 예제에서는 구조체에 대해서도 PosValue 템플릿을 쓰기 위해 특수화를 사용했는데 사실 이보다 더 간단한 방법은
//tag_Friend 구조체가 << 연산자를 오버로딩해서 기존 템플릿의 본체 코드를 지원하는 것이다.


//부분 특수화(Partial Specialization)란 템플릿 인수가 여러 개 있을 때 그 중 하나에 대해서만 특수화를 하는 기법이다. 다음 템플릿을 보자.

 //		template <typename T1, typename T2> class SomeClass { ... }

//SomeClass 클래스 템플릿은 두 개의 인수를 가지므로 <int, int>, <int, double>, <short, unsigned> 등 두 타입의 조합을 마음대로 선택할 수 있다. 
//부분 특수화는 이 중 하나의 타입은 마음대로 선택하도록 그대로 두고 나머지 하나에 대해서만 타입을 강제로 지정하는 것이다. 
//T2가 double인 경우에 대해서만 특수화를 하고 싶다면 다음과 같이 한다.

//		template <typename T1> class SomeClass<T1, double> { ... }
 

int main()
{
	PosValue<int> iv(1, 1, 2);

	tag_Friend F = { "아무개",25,177.7 };

	PosValue<tag_Friend> fv(2, 2, F);

	iv.OutValue();

	fv.OutValue();
	return 0;
}

