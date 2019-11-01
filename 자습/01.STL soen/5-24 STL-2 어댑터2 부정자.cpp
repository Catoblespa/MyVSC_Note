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
부정자는 bool을 리턴하는 조건자 함수 객체의 평가 결과를 반대로 뒤집는 또 다른 함수 객체이다. 
변형하는 함수 객체의 형태에 따라 다음 두 개의 부정자가 정의되어 있다.


부정자	적용대상

not1	단항 조건자 함수 객체(UniPred)

not2	이항 조건자 함수 객체(BinPred)


*/

//이 함수객체는 단항함수객체 이며, int를인자로, bool을 리턴한다.
//unary_function : 단항 함수 <인수1, 리턴>
//unary_function을 상속하기 때문에 이 함수객 체는 어뎁터를 사용 할 수 있는 어뎁터블 객체가 된다.
// 3의 배수를 고르기 위한 함수 객체이다.   
struct IsMulti3 : public unary_function<int, bool> {
	bool operator()(int a) const {
		return (a % 3 == 0);
	}
};

//만약 어뎁터를 사용하지 않고 3의 배수가 아닌것을 뽑아 내기 위해서는 이런식으로 하겠죠
struct IsNotMulti3 : public unary_function<int, bool> {
	bool operator()(int a) const {
		return (a % 3 != 0);
	}
};



// compare는 이항 함수 객체 이므로 , 어뎁터블 함수 객체를 만들기 위해서는 binary_function를 상속 받아야한다.
//compare는 두개의 string 인수를 전달받고 bool값을 리턴하는 BinPred 함수객체이다.
struct compare : public binary_function<string, string, bool> {
	bool operator()(string a, string b) const {
		return _stricmp(a.c_str(), b.c_str()) < 0;
	}
};

int main()
{

	int ari[] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> vi(&ari[0], &ari[10]);


	vector<int>::iterator it;

	for (it = vi.begin();; it++) {
		//it = find_if(it, vi.end(), IsMulti3());
		it = find_if(it, vi.end(), IsNotMulti3());			//3의 배수가 아닌것을 찾기위해 IsMulti3의 알고리즘을 약간 수정하여
		if (it == vi.end()) break;							//새로운 IsNotMulti3 함수객체를 선언했다.
		cout << *it << "이(가) 있다" << endl;				//그러나 알고리즘은 거의 비슷한데 함수객체를 두개나 만든게 마음에 좀 걸린다.
	}														//이런 식으로 조건이 필요할 때마다 함수 객체를 매번 만들어야 한다면 그 수가 엄청날 것이다. 
															//이럴 때 부정자를 사용하면 이미 만들어져 있는 함수 객체를 조금만 변형하여 반대의 평가를 하도록 할 수 있다. 


	for (it = vi.begin();; it++) {
		//it = find_if(it, vi.end(), IsMulti3());
		//it = find_if(it, vi.end(), IsNotMulti3());
		it = find_if(it, vi.end(), not1(IsMulti3()));		//부정자 not1을 사용하여 IsMuli3의 not을 구할 수있다.
		if (it == vi.end()) break;
		cout << *it << "이(가) 있다" << endl;
	}
	/*
	사용만을 목적으로 한다면 부정자의 동작과 사용법만 익혀 두면 충분하다. 
	반대로 만들고 싶은 조건자를 not1()로 감싸기만 하면 되므로 사용법은 지극히 쉬운 편이다.
	그러나 not1이 어떻게 함수 객체의 평가 결과를 반대로 만드는지 지적 호기심이 생기고 원리까지 알고 싶다면 헤더 파일 내부를 들여다 보지 않을 수 없다.
	내부를 분석해 보지 않으면 도대체 not1이 함수인지, 객체인지, 매크로인지조차도 파악하기 힘들고 STL이 뭔가 마술같은 사기를 치는 것 같아 기분이 그다지 상쾌하지 못하다. 
	not1은 functional 헤더 파일에 다음과 같이 정의되어 있는 함수 템플릿이다.
		//template<class F>
		//unary_negate<F> not1(const F & func)
		//{
		//	return (unary_negate<F>(func));
		//}
	F 타입의 함수 객체 func를 인수로 전달받아 unary_negate<F> 클래스의 객체를 생성하되 생성자의 인수로 func가 전달된다. 
	unary_negate는 다음과 같이 정의된 클래스 템플릿이며 인수로 함수 객체의 타입 F를 전달받는다.
	template<class F>

		//class unary_negate : public unary_function<typename F::argument_type, bool>
		//{
		//protected:
		//	 F functor;
		//public:
		//	 explicit unary_negate(const F& func) : functor(func) { }
		//	 bool operator()(const typename F::argument_type& left) const {
		//		  return (!functor(left));
		//	 }
		//};
	functor가 함수 객체 타입의 멤버 변수이므로 결국 unary_negate는 함수 객체 하나를 캡슐화한다고 할 수 있다.
	() 연산자 함수는 functor 함수를 호출하되 ! 연산자를 적용하여 평가 결과를 반대로 만들어 리턴한다.
	그래서 func가 3의 배수를 검색한다면 unary_negate는 !func 즉 3의 배수가 아닌 수를 검색하는 것이다.
	즉 find_if로 IsMulti3를 캡슐화한 unary_negate 객체 하나를 만들어서 던져 주면 원하는 목적을 달성할 수 있을 것이다.
			//it=find_if(it, vi.end(), unary_negate<IsMulti3>(IsMulti3()));			//IsMulti3 I;
																					//unary_negate<IsMulti3> N(I);
																					//it=find_if(it, vi.end(), N);

	//어뎁터블 함수 객체 란 ?
	어댑터를 적용할 수 있으려면 함수 객체는 어댑터가 요구하는 타입 정보를 제공해야 한다. 
	타입 정보를 제공하지 않는 함수 객체는 단독으로는 사용될 수 있지만 어댑터와 함께는 사용할 수 없다. 
	어댑터 적용을 위해 타입을 공개하는 함수 객체를 어댑터블 함수 객체라고 한다.

	unary_negate 클래스의 () 연산자 정의문을 보면 호출원으로부터 전달되는 left를 인수로 받아 functor에게 중계하고 있다. 
	이 함수 정의문이 작성되려면 left의 타입이 무엇인지를 알아야 하는데 이 left는 구체적으로 find_if가 순회중의 반복자에 * 연산자를 적용하여 읽어내는 요소의 타입과 같고
	이 타입은 곧 함수 객체가 받아들이는 인수의 타입이 된다. 
	그래서 unary_negate의 () 연산자가 정의되려면 함수 객체의 인수 타입인 argument_type을 정확하게 알고 있어야 하며
	이 타입을 정의하는 역할을 unary_function 기반 클래스가 대신하는 것이다.

	즉 unary_function에서 상속받는 typedef Arg argument_type;	 typedef Result result_type; 이것들은 어뎁터에게 함수객체의 타입과 리턴형을 알려주기 위해 있는거다.
	그니까 어뎁터를 쓰려면 함수 객체는 unary_function을 상속 받아 어댑터블 함수객체로 만들어야하며,  argument_type와 result_type에 함수객체에 대한 정보를
	올바르게 넣어 전달해야한다.

	*/

	//no2()부정자
	//ot2 부정자는 이항 조건자의 평가 결과를 반대로 뒤집는다. 
	//sortfunctor 예제의 compare 함수 객체는 대소 구분없이 문자열을 비교하여 오름차순으로 정렬하도록 한다. 
	//대소구분없이 내림차순으로 정렬하려면 다음 함수 객체를 만들어야 할 것이다.

	string names[] = { "STL","MFC","owl","html","pascal","Ada"
	  "Delphi","C/C++","Python","basic" };
	vector<string> vs(&names[0], &names[10]);

	sort(vs.begin(), vs.end(), not2(compare()));

	vector<string>::iterator it2;

	return 0;
}