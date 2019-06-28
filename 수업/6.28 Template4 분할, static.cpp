#include <iostream>
#include <typeinfo>


// #include "Test.h"
// #include "Test.cpp"	
// 클래스 템플릿은 분할해서 사용하지 말고, 헤더에 정의와 선언 모두 쓰자.

using namespace std;

template <typename T>
class CBase
{
public:
	static T m_static;

	void Func(T n)
	{
		m_static += n;
	}
};

template <typename T>
T CBase<T>::m_static = 0;



int main()
{
	//static 맴버는 타입이 같은 탬플릿 클래스 끼리만 공유한다.

	CBase<int> objl;
	CBase<int> obj2;
	CBase<int> obj3;

	objl.Func(10);
	obj2.Func(10);
	obj3.Func(10);

	cout << CBase<int>::m_static << endl;

	cout << "---------------------------------" << endl;

	CBase<float> objl;
	CBase<float> obj2;
	CBase<float> obj3;

	objl.Func(10.f);
	obj2.Func(10.f);
	obj3.Func(10.f);

	//둘다 30 나옴. 위와 아래의 클래스는 서로 다른것이다.
	cout << CBase<float>::m_static << endl;

	return 0;
}