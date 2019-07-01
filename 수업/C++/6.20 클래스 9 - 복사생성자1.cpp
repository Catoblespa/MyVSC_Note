#include <iostream>

using namespace std;

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.
/*

##1 복사 생성자
	1. 객체 생성시 복사가 이루어 질때 호출
	2. 함수의 인자로 객체가 전달(Call by Value) 될때  호출
	3. 함수의 반환값으로 객체를 반환(Call by Value) 할때 호출
	4.

	사용자가 복사생성자를 정의하지 않으면 컴파일러가 디폴트 복사생성자를 만들어준다.
*/



class CTest {

public:
	CTest() = default;	// 디폴트 생성자가 정의된 것과 같은 문법! 소멸자에서도 사용할수있음! 
	//단 컴파일러가 자동으로 만들 수있는 디폴트 생성자, 디폴트 소멸자, 디폴트 복사생성자만 가능한듯?!
	CTest(int a, int b) : m_iValueA(a), m_iValueB(b)
	{

	}
	//복사생성자의 원형
	CTest(const CTest& _Obj)
	{
		m_iValueA = _Obj.m_iValueA;
		m_iValueB = _Obj.m_iValueB;
		cout << "복사 생성자 호출" << endl;
	}

	/*delete키워드와 복사 생성자*/
	//CTest(const CTest& _Obj) = delete     // 해당 클래스에 대한 복사생성을 금지

public:
	void PrintMember()
	{
		cout << "m_iValueA : " << m_iValueA << endl;
		cout << "m_iValueB : " << m_iValueB << endl;
	}
private:
	int m_iValueA;
	int m_iValueB;
};

// 함수의 인자(Call by Value)로 객체를 전달 받을때 복사생성자 호출
void Func(CTest Obj)
{
}

// 함수의 반환 값(Call by Value)으로 복사생성자 호출
CTest Foo()
{
	CTest obj;
	return obj;
}

int main()
{
	CTest ObjA(100, 200);

	/*객체 생성시 복사 생성자를 사용할 경우*/
//	CTest ObjB = ObjA;	//복사생성자 호출
	CTest ObjB(ObjA);	//복사생성자 호출

	ObjB.PrintMember();

	/*함수의 인자로 객체를 전달 받았을때 (Call by Value로 받을때) 복사생성자 호출*/
	Func(ObjB);

}
