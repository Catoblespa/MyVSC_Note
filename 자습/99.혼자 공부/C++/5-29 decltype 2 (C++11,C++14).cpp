 #include <iostream>
#include <time.h>
#include <string>
#include <vector>		//STL Vector
#include <list>			//STL List
#include <algorithm>	//STL 알고리즘 헤더
#include <functional>	//STL 전역 함수 헤더	
#include <iterator>		//여러 종류의 반복자의 정의 담음.
#include <deque>		//STL deque 정의 헤더
#include <set>			//STL 연관컨테이너 set
#include <map>			//STL 연관컨테이너 map
#include <stack>		//STL 컨테이너 어댑터 stack
#include <queue>		////STL 컨테이너 어댑터 queue
#include <array>

#define randomize() srand((unsigned)time(NULL))     // srand 매크로
#define random(n) (rand() % (n))                    // rand 매크로.

using namespace std;


/*
C++11(VS2013)부터 auto 타입 반환이 가능해지고 trailing return type(후행 반환 형식)으로 decltype을 사용함으로써, 
템플릿 함수의 auto 반환이 상당히 유연해지고 자유로워졌다.


*/

// auto 반환함수와 후행 반환 형식으로 int 사용
//trailing return type(후행 반환 형식) 으로 반환 형식을 정해줄 수 있다.
auto add_function(int a, int b) -> int
{
	return a + b;
}

// auto 반환과 후행 반환 형식으로 decltype()을 사용
template <typename T, typename U>
auto add_template(T&& x, U&& y) -> decltype(std::forward<T>(x) + std::forward<U>(y))
{
	return std::forward<T>(x) + std::forward<U>(y);
}

// BUILDER의 makeObject() 반환 형식으로부터 자유로워짐
template <typename TBuilder>
auto MakeAndProcessObject(const TBuilder& builder) -> decltype(builder.makeObject())
{														//builder는 템플릿으로 받아온 클래스타입. 
	auto val = builder.makeObject();					//그 클래스타입의 맴버함수가 무얼 리턴하는지 이제는 알 수 있다!
	// process...
	return val;
}
/*
C++11에서 auto 반환 함수는 반드시 후행 반환 형식을 지정해 주어야 하며,
특히 템플릿 함수들의 경우 타입을 템플릿 인자들로부터 추론해야 하므로 decltype을 활용하지 않으면,
컴파일 단계에서 auto 반환 형식을 재대로 추론하지 못해 컴파일 에러가 발생하게 된다.

탬플릿함수에서 후행 반환 형식을 안쓸 경우의 에러
	error: 'add_template' function uses 'auto' type specifier without trailing return type
	auto add_template(T x, U y)// -> decltype(x + y)
*/






/*
C++14(VS2015)부터는 auto 반환시 후행 반환 형식을 지정해 주지 않아도 컴파일 에러없이 반환 타입을 추론해 준다.
즉, C++11에서 그랬듯 일일히 후행 반환 형식을 써주지 않아도 되는 것이다.

*/
//template <typename T, typename U>
//auto add_template2(T&& x, U&& y) // -> decltype(std::forward<T>(x) + std::forward<U>(y))
//{
//	return std::forward<T>(x) + std::forward<U>(y);
//}
//
//auto add_function2(int a, int b) // -> decltype(a+b)
//{
//	return a + b;
//}
//
//template <typename TBuilder>
//auto MakeAndProcessObject2(const TBuilder& builder)  // -> decltype(builder.makeObject())
//{
//	auto val = builder.makeObject();
//	// process...
//	return val;
//}
//
struct Builder
{
	static std::string makeObject() { return std::string("hello"); }
};


/*
위 예제들에서 반환되는 auto 타입은 템플릿 타입 추론에 의해 결정된다.
헌데 이 템플릿 타입 추론이라는 것이 다소 복잡하고, 참조 형태에 따라서 그 규칙이 모두 다르기 때문에, 
모든 규칙을 줄줄 외우고 있지 않는 이상 프로그래머가 직관적으로 의도한 것과 다른 반환 형식으로 결정될 수 있는 가능성이 낮지 않다.

이를 방지하려면, decltype으로 (auto)를 감싸주는 것이 필요하다.
*/

template <typename T, typename U>
decltype(auto) add_template2(T&& x, U&& y)
{
	return std::forward<T>(x) + std::forward<U>(y);
}

decltype(auto) add_function2(int a, int b)
{
	return a + b;
}

template <typename TBuilder>
decltype(auto) MakeAndProcessObject2(const TBuilder& builder)
{
	auto val = builder.makeObject();
	// process...
	return val;
}
/*
보기에 조금 어색할 수도 있으나 decltype(auto) 형태로 반환함으로써, 
C++11의 후행 반환 형식을 지정한 방식과 기능적으로도 완전히 같은 형태를 갖춘 셈이 되었다.

복잡하게 생각할 것 없이, 함수에서 auto 타입 반환을 하려거든 다음 둘 중 하나를 선택하면 된다.


C++11의 후행 반환 형식을 지정해 주던가
C++14의 decltype(auto)의 형태로 반환하던가

*/



int main()
{
	add_template2(1, 2);
	add_function2(1, 2);

	// a is std::string type
	Builder builder;
	auto a = MakeAndProcessObject2(builder);

	cout << a << endl;

	return 0;
}
