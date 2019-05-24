#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>		

using namespace std;

/*
함수 포인터 어댑터는 일반 함수의 번지인 함수 포인터를 함수 객체처럼 포장한다. 
함수 포인터도 어차피 () 연산자로 호출할 수 있으므로 굳이 함수 객체로 만들지 않아도 알고리즘 함수와 함께 사용할 수 있다. 
그러나 함수 포인터는 객체가 아니므로 어댑터는 적용할 수 없다.

함수 포인터에 어댑터를 쓰고 싶다면 이 포인터를 래핑해야 하며 이때 함수 포인터 어댑터를 사용한다.
앞 예제의 IsMulti 함수 객체를 일반 함수로 만든 후 이 함수를 바인더로 묶어서 find_if에 사용해 보자.
*/

bool IsMultiFunc(int a, int b)
{
	return (a % b == 0);
}


int main()
{

	int ari[] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> vi(&ari[0], &ari[10]);
	vector<int>::iterator it;

	for (it = vi.begin();; it++) {
		it = find_if(it, vi.end(), bind2nd(ptr_fun(IsMultiFunc), 3));
		//bind2nd 어댑터가 요구하는 것은 함수 객체와 고정된 2번째 인수인데 함수 포인터를 곧바로 쓸 수는 없다.
		//함수 포인터는 함수의 시작 번지를 가리키는 단순한 상수일 뿐이므로 템플릿의 인수가 될 수 없기 때문이다.
		//.ptr_fun 함수 포인터 어댑터가 이 함수 포인터를 함수 객체로 포장하며 이렇게 포장되면 바인더, 부정자 등의 어댑터를 적용할 수 있다.
		if (it == vi.end()) break;
		cout << *it << "이(가) 있다" << endl;
	}

	return 0;
}

/*
ptr_fun의 동작을 이해하려면 헤더 파일을 분석해 보는 것이 가장 빠르고 확실하다. 
단항 함수와 이항 함수에 대해 오버로딩되어 있는데 원리는 비슷하므로 단항 함수 버전만 분석해 보자.
		//template<class Arg, class Result>
		//pointer_to_unary_function<Arg, Result> ptr_fun(Result (*pfunc)(Arg))
		//{
		//	 return (pointer_to_unary_function<Arg, Result>(pfunc));
		//}
pointer_to_unary_function이라는 클래스의 객체를 만들어 리턴하는 역할을 한다. 
이 클래스(pointer_to_unary_function)는 이름이 의미하는 바대로 단항 함수 포인터를 단항 함수 객체로 만든다. 
헤더 파일에 다음과 같이 정의되어 있는데 이해하기 그리 어렵지 않은 클래스이다.

		//template<class Arg,class Result>
		//class pointer_to_unary_function : public unary_function<Arg, Result>
		//{
		//public:
		//	 explicit pointer_to_unary_function(Result (*pfunc)(Arg)) : pFun(pfunc) { }
		//	 Result operator()(Arg left) const { return (pFun(left)); }
		//
		//protected:
		//	 Result (pFun*)(Arg);
		//};

Arg 타입을 인수로 취하고 Result 타입을 리턴하는 함수 포인터 pFun을 멤버 변수로 가지며 생성자로 전달된 함수 포인터를 이 멤버에 저장해 놓는다.
그리고 () 연산자 함수는 전달된 인수 left로 pFun 함수를 호출하도록 되어 있다. 결국 이 클래스는 함수 포인터를 래핑하고 있으며 () 연산자가 함수 포인터를 대신 호출한다.
래핑보다 더 중요한 역할은 이 함수 포인터의 인수와 리턴 타입을 정의하기 위해 unary_function으로부터 상속을 받는다는 점이며 따라서 이 클래스의 객체는 어댑터블하다.

예제에서는 IsMultiFunc 함수를 ptr_fun으로 어댑터블 함수 객체로 만든 후 bind2nd 어댑터로 두 번째 인수를 3으로 고정했다. 
다음 구문은 여기에 not1 어댑터까지 사용해서 3의 배수가 아닌 것을 찾는데 세 가지 어댑터를 동시에 사용해 봤다.
			//it=find_if(it, vi.end(), not1(bind2nd(ptr_fun(IsMultiFunc),3)));
이 함수 객체가 구현되는 과정은 굉장히 복잡하다. 
함수 포인터를 래핑하여 어댑터블 함수 객체를 만들고 이 함수 객체를 래핑하여 2번째 피연산자가 고정된 또 다른 함수 객체를 만들고 
이 객체를 다시 래핑하여 평가 결과를 반대로 만드는 객체가 또 생성된다.

중간에서 이름도 없는 임시 객체들이 잠시 생성되고 함수가 함수를 호출하는 과정이 연속되지만 속도나 용량에 별로 불리한 점은 없다. 
왜냐하면 이 객체들은 멤버 변수를 가지지 않으며 함수 호출은 모두 인라인화되기 때문이다. 
실행 과정이 대충 상상은 가지만 복잡하기는 과연 복잡하다. 익숙해지면 이런 내부 동작에 대해 의심없이 그러려니 하고 쓰게 될 것이다.


*/