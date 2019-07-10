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


int exSum = 0;


//람다식을 사용한 재귀
/*

람다는 함수객체를완전히 대체할 수 있는 물건이다.
람다식은 이름없는 함수를 선언 할수 있고, 함수객체를 사용하는 알고리즘에 조금더 직관성을 높여준다.
필요에 의하면 람다함수에 이름을 붙여 , 재사용 할 수도 있다.



람다식의 기본형
[captures](parameters) -> return type {body}
	* captures: comma(,)로 구분된 캡처들이 들어갑니다.		 캡처는 lambda에서 사용할 변수나 상수들을 미리 지정하여 찍어오는 것
	* parameters: 함수의 인자들이 들어갑니다.
	* return type: 함수의 반환형입니다.
	* body: 함수의 몸통입니다.


	lambda는 std::function에 대입이 가능합니다. auto 키워드로 타입 추정도 물론 가능합니다.
	// std::function<void (std::string)> 와 밑의 식은 같다.
	auto introduce =  [](string name)
	{
		cout << name << endl;
	}

	lambda를 std::function에 대입할 수 있다는 것은 그것을 함수의 파라미터로 전달할 수도 있다는 이야기입니다.
	하지만 전달되는 함수의 반환형과 그 파라미터의 타입이 항상 같지 않을 수 있으므로 주로 템플릿 함수의 파라미터로 전달됩니다.


람다식을 재귀함수로 쓰는법
function<리턴타입(매개변수)> 함수 이름 = [캡쳐](람다의 파라미터){
	함수 몸통
};
*/


//lambda는 std::function에 대입이 가능합니다. auto 키워드로 타입 추정도 물론 가능합니다.
auto introduce = [](string name)
{
	cout << name << endl;
};

//lambda를 함수의 파라미터로 사용하기 위해 만든 템플릿 함수.
//전달되는 함수의 반환형과 그 파라미터의 타입이 항상 같지 않을 수 있으므로 주로 템플릿 함수의 파라미터로 전달됩니다.
template<typename T>
void templateFunc(T func) {
	func();
}


//람다를 반환하는 함수.
std::function<void(void)> getLambda() {

	//return 으로 람다식 함수를 작성하여 넘겨주면 리턴받는 람다식에 복사됨.
	return []() { std::cout << "I am getLambda !" << std::endl; };
}

//캡쳐에 [&]를 쓰고 전역에 선언된 fectorial를 내부에서 쓸 수 있게되었다.
//fectorial을 재귀로 하하여 사용 가능!!
function<int(int n)> fectorial = [&](int n) {
	if (n == 1)
		return 1;
	return n * fectorial(n - 1);
};
//보통 lambda 함수를 대입시킬 변수의 타입을 tr1::function이 아닌 auto로 잡는다.
//헌데, lambda 함수를 recursive 함수로 작성할 땐 반드시 auto가 아닌 tr1::function 타입으로 잡아야 한다. 반드시!
// 왜냐하면 auto로 할경우 return 에서 타입을 추정한후 return 해야하는데, return으로 타입추정이전에 fectorial을 불러오기 때문.



//클래스 멤버 함수안에서 lambda를 정의하면 [this]로 현재 객체를 참조로 캡처할 수 있습니다. 
//이때class인 Person은  lambda를 friend 함수로 현재 객체의 private 멤버에도 접근할 수 있습니다.
class Person {
public:
	Person(std::string name) : name(name) {}
	void introduce() {
		[this]() { std::cout << "My name is " << name << std::endl; }();
	}
private:
	std::string name;
};
//클래스 멤버 함수안에서 정의되는 것뿐만 아니라 lambda 자체가 멤버로 선언될 수도 있습니다. 
//이럴 경우 기존 멤버 다루듯 하면 됩니다. [this]로 현재 객체를 참조로 캡처할 수 있는 것도 마찬가지입니다.








/*람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다
람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다
람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다람다*/
int main()
{
	//==================================================================================================================
	// std::function<void (void)>
	// 람다식에 foo라는 이름을 만들었다.
	auto foo = []() { std::cout << "Hello lambda! foo!" << std::endl; };

	foo();				//foo 라는 람다 함수를 콜.
	templateFunc(foo);	// templateFunc에 인자로 foo를 넘겨주고, 내부에서 foo를 콜
	cout << endl;


	//==================================================================================================================
	//getLambda() 함수는 람다식을 반환하고 있다. auto는 class std::function<void()>형으로 변환되고, foo는 람다를 대입받은 std::function이 된다.
	auto foo2 = getLambda();
	foo2();


	//==================================================================================================================
	//vector에 람다함수를 저장 할 수도 있다.
	//vector의 타입은 function<>이여야 하며.  function의 타입은 람다와 일치 해야한다.
	vector < function<void(int, char)> >funcs;		//std::function
	funcs.push_back([](int num, char ch) {cout << "Hello " << ch << endl; });

	vector < function<void(void)> >funcs2;		//std::function
	funcs2.push_back([]() {cout << "Lambda" << endl; });

	vector < function<void(int, char)>>::iterator a;
	a = funcs.begin();

	for (auto& func : funcs)
	{
		func(1, '2');
	}
	for (auto& func : funcs2)
	{
		func();
	}
	//==================================================================================================================
	//lambda는 값을 반환할 수 있고 그 반환형을 명시할 수 있습니다. 
	//C++0x부터 등장한 후행 반환형(trailing return type)을 사용합니다. 
	//또한 함수 포인터나 함수 객체와 다르게 반환형의 추론도 가능합니다.

	auto foo3 = [] { return 3.14; };

	// explicit return type
	auto bar = []() -> float { return 3.14f; };

	// warning. double에서 float으로 암시적 형변환.
	float x = foo3();

	// OK
	float y = bar();

	//==================================================================================================================
	//==================================================================================================================
	//lambda 외부에 정의되어 있는 변수나 상수를 lambda 내부에서 사용하기 위해서 캡처를 사용합니다. 
	//참조(reference)와 복사(copy) 두 방식을 사용할 수 있고, 참조는 &var로 복사는 var로 합니다. 
	//그리고 캡처는 처음에 보았듯이 문법 요소 중 가장 처음에 나오는 []에 기술합니다.

	array<int, 5> numbers = { 1, 2, 3, 4, 5 };
	int sum = 0;

	// sum을 참조로 캡처
	for_each(numbers.begin(), numbers.end(), [&sum](int& number) {
		sum += number;
		});

	// name을 복사로 캡처
	std::string name = "Seok hyeon";
	[name]() {
		std::cout << "My name is " << name << std::endl;
	}();

	//std::for_each(numbers.begin(), numbers.end(), [sum](int& number) {
	//	// 'sum': 변경 불가능한 람다에서 복사 방식 캡처를 수정할 수 없습니다.
	//	//sum += number;   에러!!!
	//	});


	//lambda의 문법 요소 중 지정자(specifier)라는 것이 있는데 이건 선택 사항입니다. 
	//이 지정자를 이용해서 캡처된 변수를 몸통안에서 어떻게 쓸 것인지 지정할 수 있습니다. 
	//대표적으로 mutable과 constexpr이 있는데, mutable은 복사로 캡처된 변수를 몸통안에서 수정될 수 있도록 허용하는 지정자이고 
	//constexpr은 함수 호출 연산자(function call operator)가 상수 식인 것을 명시하는 지정자입니다.
	//정자에 아무 것도 기술하지 않으면 constexpr이 기본값으로 들어갑니다.

		// sum을 복사로 캡처. mutable 지정자
	for_each(numbers.begin(), numbers.end(), [sum](int& number) mutable {
		// OK
		sum += number;
		});
	//==================================================================================================================
	//==================================================================================================================
	//여러개의 변수나 상수를 한번에 캡처할 수 있습니다. []안에 여러 캡처들을 comma(,)로 구분하여 기술하면 됩니다.

	int x1 = 0;
	char y1 = 'J';
	double z1 = 3.14;
	std::string w1 = "Jinsoo Heo";

	// x, y는 참조로, z, w는 복사로 캡처.
	auto foo4 = [&x1, &y1, z1, w1]() {};
	/*
	[a,&b] a를 복사로 캡처, b를 참조로 캡처.
	[this] 현재 객체를 참조로 캡처.
	[&] 몸통에서 쓰이는 모든 변수나 상수를 참조로 캡처하고 현재 객체를 참조로 캡처.
	[=] 몸통에서 쓰이는 모든 변수나 상수를 복사로 캡처하고 현재 객체를 참조로 캡처.
	[] 아무것도 캡처하지 않음.	*/
	//[&]나 [=]는 lambda가 정의되어있는 함수를 넘어서서 전역(global) 범위까지가 그 캡처 범위입니다.
	//[&, a] 이렇게 하면 모든 변수나 상수를 캡처하고 a만 예외적으로 복사로 캡처하는 것입니다.
	//[=, &b]도 마찬가지로 모든 변수나 상수를 캡처하고 b만 예외적으로 참조로 캡처하는 것이구요.
	//[&, &a] 이렇게 쓰는 건 안됩니다. a를 같은 방식으로 2번 캡처하는 것이기 때문이죠.

	int a1, b1, c1;
	// OK
	[&, a1, b1]() {}();
	// OK
	[=, &c1]() {}();
	// 기본 캡처 모드가 참조 방식인 경우 '&a'을(를) 사용할 수 없습니다.
	//[&, &a]() {}();
	// 기본 캡처 모드가 값 방식인 경우 '&b'이(가) 필요합니다.
	//[=, b]() {}();


	//==================================================================================================================
	//==================================================================================================================

	/* 전역 변수 sum을 참조로 캡처*/
	//전역 변수를 캡처하기 위해서는 기본 캡처 모드(capture-default)를 사용해야 합니다.
	for_each(numbers.begin(), numbers.end(), [&](int& number) {
		exSum += number;
		});


	//인수 타입을 auto를 사용할 수 있다.   	템플릿 인수와 같이 형 추론된다.
	//auto은 사양 및 구현에서 필수는 아니다. 다만 가독성을 위해서 붙이는 것으로 되었다.
	auto _a = [](const auto & x, auto & y) { return x + y; };
	auto _Sum = [](auto a, decltype(a) b) { return a + b; };

	int iA = _Sum(3, 4);
	double dA = _Sum(3.14, 2.77); // 십 가능.

	// 캡쳐하지 않은 람다는 함수 포인터로 형 변환 가능
	auto L = [](auto a, decltype(a) b) { return a + b; };
	int (*fp)(int, int) = L;



	cout << fectorial(3) << endl;	//재귀 람다 함수.

    
	return 0;
}



/*
정리
lambda는 익명 함수(anonymous function)이고 함수 객체를 생성한다.
lambda는 함수 포인터와 함수 객체의 장점을 모두 가지고 있다.
기본 캡처 모드(capture-default), 복사, 참조를 통해 변수나 상수를 캡처할 수 있다.
함수에서 반환할 수도 있고 함수의 파라미터로 전달할 수도 있다.
클래스 멤버 함수안에서 정의되는 lambda는 [this]로 현재 객체를 참조로 캡처할 수 있다.
재귀 호출이 가능하다.


추가



*/