#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>

using namespace std;
/*
가상함수의 자세한 동작원리
http://soen.kr/lecture/ccpp/cpp3/30-1-3.htm

가상 함수 테이블이란 ?
http://soen.kr/lecture/ccpp/cpp3/30-1-4.png

만약 누군가가 여러분에게 가상 함수란 무엇인가라는 질문을 한다면 어떻게 대답할 수 있겠는가? 
이 질문에 대한 가장 짧고도 정확한 대답은 "동적 결합을 하는 함수"일 것이다.
*/
class Base
{
public:
	virtual  void OutMessage() { printf("Base Class\n"); }	// = > virtual 화 시켜줌으로써 pB=&D 일때 pB->OutMessage()는 D객체의 맴버 함수를 불러온다.
	//부모의 멤버 함수가 가상 함수이면 자식의 멤버 함수도 자동으로 가상 함수가 되므로 Derived의 OutMessage에는 굳이 virtual 키워드를 쓰지 않아도 되지만 
	//이 함수가 가상 함수라는 것을 분명히 표시하기 위해 양쪽에 모두 붙이는 것이 더 좋다. 
	//virtual 키워드는 클래스 선언문 내에서만 쓸 수 있으며 함수 정의부에서는 쓸 수 없다. 
	//정의부에 virtual을 쓰면 에러 처리되므로 함수를 외부 정의할 때는 virtual 키워드없이 함수의 본체만 기술해야 한다.
};



class Derived : public Base
{
public:
	virtual  void OutMessage() { printf("Derived Class\n"); }	//OutMessage 함수가 가상으로 선언되었으므로 
																//pB가 가리키는 객체의 타입에 따라 누구의 멤버 함수를 호출할 것인가가 결정된다.

};


void Message(Base* pB)
{

	pB->OutMessage();

}


void main()
{
	Base B, * pB;
	Derived D;

	pB = &B;
	pB->OutMessage();

	pB = &D;
	pB->OutMessage();
	//pB가 B를 가리키는 상황에서 pB->OutMessage는 Base의 OutMessage를 호출할 것이다. 
	//그렇다면 pB가 D를 가리킬 때는 Derived의 OutMessage를 호출할 것처럼 보인다. 이 예제를 만든 사람의 의도는 바로 이런 동작이었다. 
	//그러나 실행해 보면 예상과는 다른 결과가 나온다.
	// 출력 결과
	//Base Class
	//Base Class
	//
	//두번째 라인이 Base Class의 OutMessage() 가 호출 되는 이유는
	//컴파일러가	포인터의 정적타입을 보고 그 타입에 맞는 맴버 함수를 호출 하기 때문이다.  pB가 Base * 타입으로 선언되어 있이므로 Base의 멤버 함수를 호출하는 것이다.

	//이 예제가 의도하는 바는 pB가 선언된 포인터 타입(정적 타입)에 따라 멤버 함수를 선택하는 것이 아니라 
	//pB가 가리키고 있는 객체의 타입(동적 타입)에 따라 멤버 함수가 선택되도록 하는 것이다. 

	//가상 함수 적용 후 
	//Base Class
	//Derived Class


	//그러나 객체를 함수의 인수로 전달하거나 객체의 배열을 작성할 때는 사정이 다르다. 
	//객체는 덩치가 커서 통상 포인터로 전달하므로 객체 포인터로 멤버 함수를 호출하는 경우가 오히려 더 흔하다고 할 수 있다. 
	//다음은 예제의 모양을 조금 변경하여 클래스 타입의 포인터를 받아들이는 함수를 작성해 보자.

	Message(&B);
	Message(&D);
	//만약 Virtual 함수를 사용하지 않을경우  Message의 pB->OutMessage();는 항상 Base의 맴버 함수만을 불러올것이다.
}