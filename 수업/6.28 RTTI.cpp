#include <iostream>
#include <typeinfo>
using namespace std;



//#1. RTTI (RunTime Type Information)
//런타임 도중에 타입의 정보를 알아낼 수 있는 C++기법
//가상 함수 테이블에 현재 클래스 타입이 저장됨!
class CBase
{
public:
	virtual ~CBase() = default;
};


class CChild : public CBase
{
public:
	virtual void Func()
	{
		cout << "나 자식 함수야!" << endl;
	}
};



int main()
{

	//CBase* ptr = new CBase
	//비정상적인 다운캐스팅
	//Func은 virtaul 함수라서 CChild에 가상함수테이블을 만들어서 사용된다
	//하지만 CBase는 가상함수 테이블을 갖고 있지 않기 때문에 뻗어버린다.
	//virtual 을 안쓸경우 프로그램이 뻗진 않지만.. 당연히 그렇게 짜면 안되는거다.
	//static_cast<CChild*>(ptr)->Func();
	//delete ptr;
	
	//##2 typeid 연산자

	CBase* ptr1 = new CBase;
	CBase* ptr2 = new CChild;


	cout << typeid(ptr1).name() << endl;
	cout << typeid(ptr2).name() << endl;
	cout << "***********************" << endl;
	cout << typeid(*ptr1).name() << endl;
	cout << typeid(*ptr2).name() << endl;

	if (!strcmp("class CChild", typeid(*ptr2).name()))
	{
		cout << "다운 캐스팅 올바릅니당" << endl;
	}
	else
		cout << "다운 캐스팅이 올바르지 않습니다" << endl;


	//##4 결국 Dynamic_cast 는 RTTI 기반으로 작동한다.
	
	return 0;
}
