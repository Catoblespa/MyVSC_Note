#include <iostream>
#include <Windows.h>
using namespace std;

//RTTI 기능은 typeid 연산자로 사용한다. 이 연산자는 클래스의 이름이나 객체 또는 객체를 가리키는 포인터를 피연산자로 취하며 피연산자의 타입을 조사한다. 
//typeid 연산자의 리턴 타입은 const type_info & 이며 type_info는 클래스의 타입에 대한 정보를 가지는 또 다른 클래스이다. 
// 클래스는 컴파일러 제작사마다 조금씩 다르게 정의하는데 비주얼 C++의 경우 typeinfo 헤더 파일에 다음과 같이 선언되어 있다.
/*
class type_info {
public:
	 virtual ~type_info();
	int operator==(const type_info& rhs) const;
	 int operator!=(const type_info& rhs) const;
	 int before(const type_info& rhs) const;
	 const char* name() const;				//name 멤버 함수는 문자열로 된 타입의 이름을 조사하는데 클래스 이름이라고 보면 된다.
	 const char* raw_name() const;			//raw_name은 장식명을 조사하는데 사람이 읽을 수 없는 문자열이므로 비교에만 사용할 수 있다.
											//이 외에도 type_info 객체가 같은지, 다른지를 조사하는 ==, != 연산자가 오버로딩되어 있는데 통상 == 연산자만 사용해도
												//원하는 타입인지 아닌지를 알 수 있다.
private:
	void *_m_data;
	char _m_d_name[1];
	type_info(const type_info& rhs);
	type_info& operator=(const type_info& rhs);
};
*/
//만약 typeid의 피연산자가 NULL 포인터로부터 읽은 값일 경우 bad_typeid 예외를 발생시킨다.
//예를 들어 p가 NULL일 때 typeid(*p) 연산식은 예외로 처리된다
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

void func(Parent* p)
{
	p->PrintMe();

	if (typeid(*p) == typeid(Child))			//*p가  Child클래스인지 비교
		((Child*)p)->PrintNum();
	else
		puts("이 객체는 num을 가지고 있지 않습니다.");

}

int main()
{
	Parent P, * pP;
	Child C, * pC;

	pP = &P;
	pC = &C;


	printf("P=%s, pP=%s, *pP=%s\n",
		typeid(P).name(), typeid(pP).name(), typeid(*pP).name());

	printf("C=%s, pC=%s, *pC=%s\n",
		typeid(C).name(), typeid(pC).name(), typeid(*pC).name());

	pP = &C;
	printf("pP=%s, *pP=%s\n",
		typeid(pP).name(), typeid(*pP).name());


	return 0;
}


