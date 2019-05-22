#include <iostream>
#include <Windows.h>
using namespace std;


/*
static_cast 연산자는 지정한 타입으로 변경하는데 무조건 변경하는 것이 아니라 논리적으로 변환 가능한 타입만 변환한다. 기본 문법은 다음과 같다.
static_cast<타입>(대상)


dynamic_cast															: http://soen.kr/lecture/ccpp/cpp3/33-2-3.htm
포인터끼리 또는 레퍼런스끼리 변환하는데 반드시 포인터는 포인터로 변환해야 하고 레퍼런스는 레퍼런스로 변환해야 한다.
포인터끼리 변환할 때도 반드시 상속 계층에 속한 클래스끼리만 변환할 수 있다
 int *를 char *로 변환하거나 Parent *를 int *로 변환하는 것은 안된다.

다이나믹 캐스트는 변환할 대상이 타입과 같은 타입일때 변환을 하고, 그렇지 않을때 NULL을 반환하여 오류를 방지한다.

const_cast																: http://soen.kr/lecture/ccpp/cpp3/33-2-4.htm
이 캐스트 연산자는 포인터의 상수성만 변경하고 싶을 때 사용한다.
이 연산자는 포인터의 const 속성을 넣거나 빼거나 할 수 있으며 잘 사용되지는 않지만 비슷한 성격의 지정자인 volatile 속성과 __unaligned 속성에 대해서도 변경할 수 있다.
이 캐스트 연산자 외의 다른 캐스트 연산자는 포인터의 상수성을 변경할 수 없다. 물론 C의 캐스트 연산자로는 마음대로 할 수 있지만 말이다.

reinterpret_cast														: http://soen.kr/lecture/ccpp/cpp3/33-2-5.htm
이 캐스트 연산자는 임의의 포인터 타입끼리 변환을 허용하는 상당히 위험한 캐스트 연산자이다. 
심지어 정수형과 포인터간의 변환도 허용한다. 정수형값을 포인터 타입으로 바꾸어 절대 번지를 가리키도록 한다거나 할 때 이 연산자를 사용한다.


 캐스트 연산자					변환형태
static_cast					상속 관계의 클래스 포인터 및 레퍼런스. 기본 타입. 타입 체크 안함

dynamic_cast				상속 관계의 클래스 포인터 및 레퍼런스. 타입 체크. RTTI 기능 필요

const_cast					const, volatile 등의 속성 변경

reinterpret_cast			포인터끼리, 포인터와 수치형간의 변환
*/



class Parent
{
public:
	virtual void PrintMe() { printf("I am Parent\n"); }
};



class Child : public Parent
{
private:
	int num;
public:
	Child(int anum = 1234) : num(anum) { }
	virtual void PrintMe() { printf("I am Child\n"); }
	void PrintNum() { printf("Hello Child=%d\n", num); }

};




void main()
{	
	//-----------------------static cast ---------------------
	//const char* str = "korea";
	//int* pi;
	//double d = 123.456;
	//int i;

	//i = static_cast<int>(d);                  // 가능
	////pi = static_cast<int*>(str);            // 에러
	//pi = (int*)str;                          // 가능


	//Parent P, * pP;
	//Child C, * pC;

	//pP = static_cast<Parent*>(&C);         // 가능
	//pC = static_cast<Child*>(&P);      // 가능하지만 위험
	////pP = static_cast<Parent*>(&i);     // 에러
	////pC = static_cast<Child*>(&i);       // 에러


	//-----------------------dynamic_cast ---------------------
	Parent P, * pP, * pP2;
	Child C, * pC, * pC2;
	pP = &P;
	pC = &C;

	pP2 = dynamic_cast<Parent*>(pC);       // 업 캐스팅-항상 안전하다.
	pC2 = dynamic_cast<Child*>(pP2);        // 다운 캐스팅-경우에 따라 다르다.	//여기서 pP2는 pC를 받고 있어, 실질적으로 Child를 가르키고 있으므로 성공
	printf("pC2 = %p\n", pC2);
	pC2 = dynamic_cast<Child*>(pP);         // pC2는 Child, pP는 Parent이므로 불가. dynamic_cast는 NULL을 반환한다.
	printf("pC2 = %p\n", pC2);


	//-----------------------const_cast ---------------------
	char str[] = "string";
	const char* c1 = str;
	char* c2;
	//c2 = c1;							//이렇게 대입받은 포인터를 다른 비상수 지시 포인터 c2에 대입하고자 할 때는 c2=c1으로 바로 대입할 수 없다. 
										//두 포인터의 상수성이 다르며 c1이 가리키는 읽기 전용 값을 c2로 부주의하게 바꿔 버릴 위험이 있기 때문이다. 
										 
	c2 = const_cast<char*>(c1);			//그러나 이 경우 c1이 가리키는 대상(최초 대입받은 str)이 변경 가능한 대상이라는 것을 확실히 알고 있으므로
	c2[0] = 'a';						//c1의 상수성만 잠시 무시하면 대입 가능하다. 이때 const_cast 연산자로 c1을 char *로 캐스팅할 수 있다.
	printf("%s\n", c2);
}

