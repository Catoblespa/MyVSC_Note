#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>

using namespace std;

/*
Human H("이놈");
Student S("저놈",9900990);

H=S;        // 가능
S=H;        // 에러

부모 클래스의 객체인 H가 자식 클래스의 객체인 S를 대입받는 것은 논리적으로 가능하다.왜냐하면 H가 대입받을 모든 멤버가 S에도 있기 때문이다. 
좀 유식하게 표현하면 학생은 일종의 사람이며 IS A관계가 성립하므로 학생이 사람이 될 수 있다. 
S와 H에 동시에 존재하는 모든 멤버가 H로 대입되며 S에는 있지만 H에는 없는 멤버는 대입에서 제외된다.

Student = Human에서 에러가 발생하는 이유는 Student에 Human을 대입하여 Student의 맴버를 모두 온전히 초기화 하기 어렵기 때문이다.
보통 자식클래스는 부모클래스보다 더 많은 맴버 변수를 갖고, 그럴 경우 S = H는 S를 완벽히 초기화하지 못하고, 엉뚱한 자료를 갖게되는 객체가 되어버린다.
만약 초기화 되지 않은 변수가 S에서 반드시 값을가져야 할 경우의 변수일 경우를 컴파일러에서 걸러주는 것.
하지만 Student클래스에서 Human 클래스에 대해 대입연산자가 정의되어 있고,
이 함수가 Human에 없는 멤버에 대해 무난한 디폴트를 취한다면 역방향의 대입이 문법적으로 가능해진다. 
하지만 이 방법은 일반적이지 않다.
*/

class Human
{
protected:
	char Name[16];

public:
	Human(const char* aName) { strcpy_s(Name, sizeof(Name), aName); }
	void Intro() { printf("이름:%s", Name); }
	void Think() { puts("오늘 점심은 뭘 먹을까?"); }
};



class Student : public Human
{
private:
	int StNum;

public:
	Student(const char* aName, int aStNum) : Human(aName) { StNum = aStNum; }
	void Intro() { Human::Intro(); printf(",학번:%d", StNum); }
	void Think() { puts("이번 기말 고사 잘 쳐야 할텐데 ^_^"); }
	void Study() { puts("하늘 천 따지 검을 현 누를 황..."); }
};



void main()
{
	Human H("김사람");
	Student S("이학생", 1234567);
	Human* pH;
	Student* pS;



	pH = &H;         // 당연히 가능

	pS = &S;         // 당연히 가능

	pH = &S;         // 가능
	//이렇게 대입된 포인터 pH로는 Human에 있는 멤버만 참조할 수 있으며 Human의 모든 멤버를 Student객체인 S도 가지고 있다. 
	//그러므로 pH->Think()를 호출하든 pH->Intro()를 호출하든 전혀 이상이 없는 것이다. 
	//학생은 사람이므로(Student is a Human) 사람의 모든 속성을 가지며 사람이 할 수 있는 모든 행동을 할 수 있다.

//  pS=&H;         // 에러


	pS = (Student*)& H;
	//강제로 캐스팅 하여 대입

	pS->Intro();
	// pS가 가리키고 있는 H 객체 Student로 강제로 캐스팅되어서 이름은 가지고 있지만 학번은 가지고 있지 않으므로 엉뚱한 쓰레기값이 출력될 것이다.

	//포인터는 두 가지 종류의 타입을 가진다. 정적 타입(Static Type)이란 포인터가 선언될 때의 타입, 즉 포인터 자체의 타입을 의미하며 
	//동적 타입(Dynamic Type)이란 포인터가 실행중에 가리키고 있는 대상체의 타입, 즉 대상체의 타입을 의미한다. 
	//대개의 경우 정적, 동적 타입이 일치하지만 위 예의 pH=&S 대입처럼 두 타입이 틀려지는 경우도 있다. 
	//pH의 정적 타입은 Human *형이지만 Student형 객체의 번지를 가리키고 있으므로 동적 타입은 Student *형이다.
	//pH = &H;  =>정적, 동적 타입 일치
	//pH = &S;  =>정적, 동적 타입 불일치.

	// 여기서 가장 중요한 개념은 *****부모는 자식을 가리킬 수 있다.****** 이다. 단, 다중상속의 경우는 안된다.
}