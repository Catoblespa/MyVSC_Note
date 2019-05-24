#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>		

using namespace std;

/// Begin a new session.
/// defualt $orange   ^puple .yellow !red  %puple2  @white	 
// >asdasd asdasdm  'Effect'dndn

/*
어댑터(Adapter)란 이미 만들어진 컴포넌트의 구현은 그대로 활용하고 인터페이스만 조금 변경하여 컴포넌트를 일부 변형시키는 것이다.
어댑터는 컴포넌트를 조금씩 변형함으로써 활용도를 높인다.
새로 만들고자 하는 부품이 이미 만들어진 부품의 기능 중 일부만을 필요로 할 경우 처음부터 새로 만들 필요없이 기존 부품을 변형해서 사용하면 훨씬 더 빠르고 간편하다.
없는 기능을 만들 수는 없지만 있는 기능의 일부를 막아 버린다거나 고정하는 것은 가능하다.

비록 STL이 제공하는 컴포넌트의 수가 많고 일반화되어 있기는 하지만 그래도 특수한 프로그래밍 환경에 두로 사용되기에는 결코 충분하지 않다.
그렇다고 컴포넌트의 수를 무한정 늘리기만 할 수는 없으므로 기존 컴포넌트를 변형할 수 있는 어댑터라는 방법을 제공한다.
어댑터는 일반화된 컴포넌트의 용도를 더욱 확장하는 역할을 한다. 어댑터는 컴포넌트, 반복자, 함수 객체에 대해 적용되며 다음과 같이 분류할 수 있다.

					  / 스택
	  /-컴포넌트 어댑터-  큐
	 /				  \ 우선 순위 큐
	/
어댑터---반복자 어댑터 --역방향 반복자
	\
	 \				  / 부정자
	  \-함수 객체어댑터-  바인더
					  \함수 포인터 어댑터


여기서는 함수 객체에 대한 어댑터만 우선적으로 연구해 보자.

함수 객체의 기능을 조금이라도 변경하려면 어댑터를 적용할 수 있도록 만들어야 하는데 이런 함수 객체를 어댑터블(Adaptable) 함수 객체라고 한다.
기능을 변경하는 어댑터는 대상 함수 객체가 취하는 인수의 타입은 무엇인지, 리턴 타입은 무엇인지 등 함수 객체에 대한 충분한 정보를 얻을 수 있어야 한다.
만드는 방법은 아주 쉬운데 <functional> 헤더 파일에 정의되어 있는 다음 두 템플릿 클래스 중 하나를 상속받으면 된다.

	template<class Arg, class Result>
	struct unary_function {
		 typedef Arg argument_type;
		 typedef Result result_type;
	};

	template<class Arg1, class Arg2, class Result>
	struct binary_function {
		 typedef Arg1 first_argument_type;
		 typedef Arg2 second_argument_type;
		 typedef Result result_type;
	}

인수의 개수에 따라 단항 함수 객체는 unary_function을 상속받고 이항 함수 객체는 binary_function을 상속받는다.
이 클래스의 내용을 보면 멤버 변수나 멤버 함수는 전혀 없고 인수와 리턴값에 대한 타입 정의(typedef)만을 가진다.
클래스는 주로 멤버 변수나 멤버 함수들로 구성되지만 타입이나 상수, 내부 클래스, 가상 함수 테이블 등의 다른 여러 가지 것들도 같이 캡슐화된다는 것을 잊지 말자.

인수나 리턴 타입은 함수 객체와 관련이 있는 중요한 정보인데 이 정보들을 템플릿 인수로 전달받아 argument_type, result_type 등의 이름으로 획일화하여 타입 정의한다.
이항 함수 객체는 두 개의 인수를 가지므로 first, second 인수의 타입을 각각 따로 정의한다.
이 두 클래스로부터 상속받으면 타입들이 미리 약속된 이름으로 정의되므로 어댑터는 약속된 이름으로 해당 정보를 쉽게 얻을 수 있다.

어댑터들은 함수 객체의 기능을 변형하기 위해 이 정보들이 필요한데 함수 객체가 약속된 이름으로 직접 이 타입들을 정의해도 상관없다.
그러나 아무래도 직접 정의하는 것은 번거로우므로 상기 두 클래스로부터 상속을 받는 것이 편리하다.
 functor 예제의 print 함수 객체는 단독으로 사용되므로 이 타입들을 정의하지 않았는데 어댑터로 사용하려면 다음과 같이 정의하는 것이 원칙이다.

 

	EX)
	#include <functional>

	struct print : public unary_function<int,void> {
		 void operator()(int a) const {
			  printf("%d\n",a);
		 }
	};

unary_function으로부터 상속받되 인수는 int 타입이고 리턴 타입은 void임을 템플릿 인수로 지정했다.
이 상속에 의해 두 개의 타입이 약속된 이름으로 정의되며 print 함수 객체를 다음처럼 선언하는 것과 같다. 
argument_type은 int가 되고 result_type은 void가 된다.

	struct print {

		typedef int argument_type;
		typedef void result_type;
		 void operator()(int a) const {
			  printf("%d\n",a);
		 }
	};
	이렇게 타입을 직접 정의해도 마찬가지이지만 귀찮기도 하고 오타가 발생할 위험도 있으므로
	STL은 타입 정의를 도와주는 unary_function, binary_function 기반 클래스를 제공하는 것이다.
	어차피 이 클래스들은 크기가 0이므로 상속을 받는다 하여 용량상의 불이익이 발생하는 것도 아니다.
	///그래서 어댑터를 적용할 계획이든 아니든 함수 객체 클래스를 정의할 때는 일단 상속을 받는 것이 좋다. //*****
	plus, greater 등의 미리 제공되는 함수 객체들은 모두 이 클래스들로부터 상속받으므로 어댑터를 항상 적용할 수 있다.
*/

int main()
{
	return 0;
}