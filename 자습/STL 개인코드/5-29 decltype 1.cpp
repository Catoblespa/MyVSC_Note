#include <iostream>
#include <time.h>


#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;


/*

decltype??


decltype은 declared type(선언된 형식)의 줄임말로써, 주어진 이름이나 표현식의 구체적인 타입을 알려주는 키워드이다.
TR1부터 도입된 decltype은 주로 주어진 템플릿 인자에 기반한 generic programming의 어려움을 해소하기 위해 도입되었다.
	//원형
	//decltype(expression)

auto가 값에 상응하는 타입을 추론시켜주는 키워드라면,
decaltype은 값으로부터 타입을 추출해 낼 수 있는 키워드라고 생각하면 된다.
(두 키워드 모두 전적으로 컴파일 타임 기능인 것은 말해 입 아프다)


*/

int main()
{
	// x의 타입은 int 이므로 아래 표현식은 int y = x와 같으며...
	// 이런 경우엔 그냥 auto y = x;가 훨씬 쓰기도 보기도 좋다
	int x = 3;
	decltype(x) y = x;

	struct A
	{
		double x;
	};

	const A* a = new A{ 0 };
	decltype(a->x) x3;				// 이 경우 a->x는 a의 멤버 엑세스로 처리되어, x3는 double 형식을 갖는다.

	decltype((a->x)) x4 = x3;
	// 내부괄호로 (a->x)를 묶으면, 멤버 엑세스가 아닌 표현식으로 평가한다.
	// 왼값 표현식일 경우 decltype은 늘 왼값 참조를 보고한다.
	// 이 경우 a가 const pointer이므로, (a->x)는 a의 const를 받고, 왼값 참조가 되어 const double& 형식  중요중요..


	//뭐 변수를 선언할 때야 auto를 쓰는 것이 훨씬 편하고, 
	//에지간히 복잡한 generic programming을 하지 않는 이상, 일반적으로 이 녀석을 사용해야 할 경우가 그리 많지 않긴 하다.

	return 0;
}
