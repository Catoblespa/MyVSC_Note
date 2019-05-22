#include <iostream>
#include <Windows.h>
using namespace std;


/*

RTTI는 C++ 표준 중 비교적 최근에 채택된 것이라 아직까지도 이를 지원하지 않는 컴파일러들이 많이 있으며 
컴파일러뿐만 아니라 라이브러리들도 효율이나 기타 여러 가지 이유로 본격적으로 RTTI를 활용하지 않는 경우가 허다하다. 
컴파일러가 클래스의 타입 정보를 어떤 식으로 저장하는지를 안다면 
이 방식을 유사하게 흉내냄으로써 실행중에 타입 정보를 조사할 수 있는 클래스를 만들 수도 있다. 
*/
class Parent
{
protected:
	const char* Name;

public:
	virtual void PrintMe() { Name = "Parent"; printf("I am Parent\n"); }	//생성자에서 Name을 항상 동일하게 초기화
	virtual const char* GetName() { return Name; }
};



class Child : public Parent
{
private:
	int num;

public:
	Child(int anum = 1234) : num(anum) { Name = "Child"; }
	virtual void PrintMe() { printf("I am Child\n"); }
	void PrintNum() { printf("Hello Child=%d\n", num); }
};



void func(Parent* p)
{
	p->PrintMe();

	if (strcmp(p->GetName(), "Child") == 0) 
		((Child*)p)->PrintNum();
	else 
		puts("이 객체는 num을 가지고 있지 않습니다.");
	
}



void main()
{
	Parent p;
	Child c(5);

	func(&c);
	func(&p);
}


/*
이 예제에서 보다시피 RTTI는 그리 어려운 개념이 아니다. 
그러나 이 예제가 작성하는 타입 정보는 컴파일러가 직접 생성하는 type_info 클래스보다 효율적이지 못하며 빠르지도 않다. 
type_info는 vtable을 통해 각 클래스마다 하나씩 생성되는데 비해 
이 예제의 타입 정보는 객체마다 하나씩 생성되기 때문에 용량상의 낭비가 심한 편이다. 
정적 멤버를 사용하면 클래스마다 하나씩의 타입 정보를 생성할 수 있지만 
정적 멤버는 상속되지 않기 때문에 각 파생 클래스마다 고유의 멤버를 따로따로 만들어야 하는 번거로움이 있다. 
아무렴 직접 만든 코드가 컴파일러가 만든 것보다 효율이 좋을 수 있겠는가?
*/
