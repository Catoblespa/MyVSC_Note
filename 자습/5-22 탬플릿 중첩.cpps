#include <iostream>
#include <Windows.h>
#include "TDArray.h"
#include "TStack.h"
using namespace std;

/*


템플릿의 인수열에 들어갈 수 있는 타입에는 특별한 제한이 없다.
기본 타입은 물론이고 클래스 타입도 템플릿의 인수열에 넣을 수 있다.
그렇다면 템플릿으로 만든 클래스도 분명히 타입의 일종이므로 다른 템플릿의 인수가 될 수 있다는 얘기인데
즉, 템플릿끼리 중첩될 수 있다.


다음 예제는 PosValue 템플릿 클래스를 요소로 가지는 스택을 정의한다.
*/


template <typename T>
class PosValue
{
private:
	int x, y;
	T value;

public:
	PosValue() : x(0), y(0), value(0) { }
	PosValue(int ax, int ay, T av) : x(ax), y(ay), value(av) { }

	void OutValue()
	{
		gotoxy(x, y);
		cout << value << endl;
	}
};



int main()
{
	TStack<PosValue<int> > sPos(10);

	PosValue<int> p1(5, 5, 123);
	PosValue<int> p2;

	sPos.Push(p1);
	p2 = sPos.Pop();
	p2.OutValue();
	sPos.Pop();


	return 0;
}

