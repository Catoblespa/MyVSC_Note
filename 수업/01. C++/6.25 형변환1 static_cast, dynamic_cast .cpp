#include <iostream>
using namespace std;


/*
	C++ 형변환(캐스팅) 연산자
	static_cast
	dynamic_cast
	const_cast
	reinterpret_cast
*/

class CBase
{
public:
	virtual ~CBase() {}
};
class CChild : public CBase
{
public :
	virtual void Func()
	{
		cout << "Child 맴버 함수 " << endl;
	}
};


int main()
{
	//##2 static_cast(정적 캐스팅)
	//형변환 시점 : 컴파일 시점.
	//논리적 형변환이라고도 한다.
	//
	//int a = (int)3.14f;					//C 스타일 명시적 형변환
	//int b = static_cast<int>(3.14f);	//C++ 스타일 명시적 형변환

	//int c = 100;
	//double* ptr = (double*)&c;		//원래 해서는 안될 캐스팅을 C스타일에서는 강제적으로 형변환을 허용한다.
									//double * 에 넣어두면 참조할때 8바이트를 읽어버리는데 int c는 4바이트다.
									//이러면 당연히 문제 생기지 ?  근데 강제형변환이라 에러를 못찾음. 이러면 런타임에서 난장판됨

	//double* ptr2 = static_cast(double*)(&c);	//Error //static_cast는 위에서 발생할 문제를 컴파일 시점에서 오류를 뿜어준다.
												//C스타일 캐스팅보다 안전하다!

	//## static_cast의 문제점
	//CBase* ptr2 = new CChild;

	////static_cast는 해당 다운 캐스팅이 올바른 것인지 잘못된 것인지 파악 못함
	////ptr2은 CBase타입인데 자식 클래스인 CChild의 맴버함수 Func()를 호출한다. 이러면 안데!
	//static_cast<CChild*>(ptr2)->Func();			//잘못된 캐스팅! 근데 실행은됨. 그래도 이렇게 쓰지마셈


	//delete ptr;
	//cout << "========================" << endl;


	//##2	dynamic_cast 
	//형변환 시점	: 런타임
	//사용 조건		: 대상이 virtual 키워드를 무조건 갖고 있어야한다.
	CBase* ptr = new CBase;
	CChild* ptr2 = dynamic_cast<CChild*>(ptr);

	if (ptr2 == nullptr)			//dynamic_cast는 잘못된 다운 캐스팅을 할경우 nullptr을 반환한다.
		cout << "잘못된 다운 캐스팅입니다" << endl;			//업캐스팅은 별도 연산자 없으 쓰던대로 쓰면됨.


	return 0;
}