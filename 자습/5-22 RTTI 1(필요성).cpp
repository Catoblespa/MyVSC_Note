#include <iostream>
#include <Windows.h>
using namespace std;

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


																
															

void func(Parent* p)											//// if (strcmp(typeid(*p).name(), "class Child") == 0)
{																// 	((Child*)p)->PrintNum(); 
	p->PrintMe();												// else
	((Child*)p)->PrintNum();									// 	puts("이 객체는 num을 가지고 있지 않습니다.");
}	
//이 예제의 func 함수가 원래 의도했던 바는 Parent 파생 객체를 받아 이 객체로 어떤 일을 하되 
// 객체가 Child 타입인 경우만 PrintNum이라는 함수를 추가로 호출하고 싶었던 것이다.


//파생 객체를 모두 처리할 수 있어야 하므로 어쩔 수 없이 Parent * 타입의 인수를 받되 
//이 객체가 Child 타입인 조건이 만족될 때만 p를 강제 캐스팅해서 PrintNum을 부르도록 하고 싶다.
/*
void func(Parent *p)
{
	 p->PrintMe();
	 if (p가 Child 객체를 가리키면) 
		  ((Child *)p)->PrintNum();
} */
//이렇게 조건문을 작성하여 p가 Child 타입의 객체를 가리킬 때만 PrintNum을 호출하면 확실히 안전하다.
//그런데 포인터만 가지고 있는 상황에서 이 포인터가 Parent 객체를 가리키는지 Child객체를 가리키는지를 어떻게 알 수 있겠는가? 
//위 코드에서 말로 된 가상의 코드를 어떻게 구체적인 실제 코드를 바꿀 수 있을까?
//사실 Parent클래스에서 가상함수로 PrintNum()을 정의해두면 가능하나, 최근에 C++에 그러지 않아도 타입을 구분해주는 RTTI가 추가 되었으니

//이 다음 예제에서 마저 풀도록하자. 

int main()
{
	Parent p;
	Child c(5);

	func(&p);			//Parent 타입 p는 func함수에 의해 강제 캐스팅되서 PrintNum()의 실제 주소를 찾아 실행 할 수는 있지만,
						//parent 클래스이는 num이라는 맴버함수가 없기 때문에 쓰래기 값이 들어간다. 
	func(&c);


	return 0;
}
