#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>		

using namespace std;

//IsMulti3 함수 객체는 정수값이 3의 배수인지를 조사하는데 임의 정수의 배수를 조사할 수 있도록 좀 더 일반화해 보자.

//IsMulti는 vector가 갖는 여러 요소를 b로 나누어 나머지가 0일때 true를 리턴하므로, a는 가변, b는 고정값이다,
//두번째 항을 고정값으로 바인드 하므로, 바인드 함수는 bind2nd를 사용한다.
struct IsMulti : public binary_function<int, int, bool> {
	bool operator()(int a, int b) const {
		return (a % b == 0);
	}
};
/*
두 개의 인수를 전달받음으로써 일반성을 확보한 것은 좋은데 이렇게 되면 단항 조건자를 요구하는 find_if와는 함께 사용할 수 없다. 
find_if는 컨테이너를 순회하면서 요소값 하나만 조건자의 인수로 전달하므로 인수 두 개를 받는 이항 조건자와는 타입이 맞지 않은 것이다. 
사용하고자 하는 함수 객체의 항이 요구되는 함수 객체와 다를 때 바인더 어댑터를 사용한다.

바인더는 이항 함수 객체의 나머지 한 인수를 특정한 값으로 고정하여 단항 함수 객체로 변환한다. 
find_if처럼 단항 조건자 객체를 요구하는 함수에게 이미 만들어 놓은 이항 함수 객체를 전달하려면 단항으로 변환해야 하는데 이때 바인더가 필요하다. 
바인더는 다음 두 가지 형식으로 사용한다.

		//bind1st(이항 객체, 고정값)		//ex binding :	bind1st(IsMulti,3)   => IsMulti(3고정,가변)
		//bind2nd(이항 객체, 고정값)		//				bind2nd(IsMulti,3)   => IsMulti(가변,3고정)

bind1st는 첫 번째 인수를 고정하며 bind2nd는 두 번째 인수를 고정한다. 
IsMulti이항 조건자와 bind2nd 어댑터를 사용하여 find_if를 호출해 보자.
*/




int main()
{
	IsMulti IM;
	if (IM(6, 3)) { cout << "6은 3의 배수이다." << endl; }
	if (IM(9, 2)) { cout << "9는 2의 배수이다." << endl; }
	int ari[] = { 1,2,3,4,5,6,7,8,9,10 };

	cout << "================================" << endl;
	cout << "========3의 배수 찾기============" << endl;
	vector<int> vi(&ari[0], &ari[10]);
	vector<int>::iterator it;
	for (it = vi.begin(); ; it++)
	{
		//find_if 첫번째 항을 vi.begin()으로 하면, 계속 처음부터 돌아,
		//3을 계속 찾으므로 무한 루프를 한다. 
		//첫번째 항은 it의 위치를 넣고, end()가 될때 break를 하도록하자.	
		it = find_if(it, vi.end(), bind2nd(IsMulti(),3));				//it = find_if(it, vi.end(), bind2nd(greater<int>(), 5));
																		//greater는 두 값을 비교하여 앞의 값이 뒤의 값보다 더 큰지를 조사하는 이항 조건자인데 bind2nd로 뒤의 인수를 5로 고정했으므로 
																		//전달된 인수가 5보다 큰지를 조사하는 단항 조건자가 된다. 
																		//it = find_if(it, vi.end(), bind2nd(less_equal<int>(), 5));
		if (it == vi.end())break;										//사용자 정이 함수객체 뿐만아니라, 미리정의된 함수객체도 사용 가능.
		cout << *it <<"가 있다"<< endl;
	}
	//bind2nd(IsMulti(),3)은 이항 조건자 IsMulti의 두 번째 인수를 3으로 고정하여 단항 조건자로 변환하며 그래서 이 조건자를 find_if와 함께 사용할 수 있다. 
	//IsMulti는 binary_function으로부터 상속받았으므로 어댑터블 함수 객체이다. 
	//사용자가 직접 만든 함수 객체 외에 미리 제공되는 함수 객체에도 어댑터를 적용할 수 있다.
	cout << "====================================" << endl;
	cout << "=========3의 배수아닌것===============" << endl;

	for (it = vi.begin(); ; it++)
	{
		it = find_if(it, vi.end(), not1(bind2nd(IsMulti(), 3)));	//다음 예는 부정자와 바인더를 동시에 적용하여 3의 배수가 아닌 요소들을 검색한다. 
		if (it == vi.end())break;									//IsMulti는 두 정수의 배수 관계를 조사하는데 bind2nd에 의해 나누는 수가 3으로 고정되고 
		cout << *it << "가 있다" << endl;							//not1에 의해 결과를 반대로 뒤집으므로 결국 3으로 나누어지지 않는 값을 찾게 되는 것이다.
	}																		//설명: find_if는 단항 함수객체를 받으므로 이항인 IsMulti를 단항으로 바인딩.
																			//바인딩하여 단항으로 바뀌니까 not1으로 단항 부정자를 사용한다.

	//bind1st는 이항 조건자의 첫 번째 인수를 고정하는데 bind2nd만큼 자주 사용되지는 않는다.
	//이 예제에서 bind2nd를 bind1st로 수정하면 나누어지는 수가 고정되고 나누는 수에 컨테이너의 요소들이 전달되므로 
	//고정된 인수의 !약수들이 조사될 것이다.
	cout << "====================================" << endl;
	cout << "==============6의 약수===============" << endl;
	for (it = vi.begin(); ; it++)
	{
		it = find_if(it, vi.end(), bind1st(IsMulti(), 6));// IsMulti의 첫번째 항이 6으로 고정되고, 두번째항에 vi안에 있는 1~10이 들어가므로 6의 약수가 나온다.
																		
		if (it == vi.end())break;										
		cout << *it << "이 있다" << endl;
	}
	return 0;
}


/*
bind 클래스 분석


두 바인더는 대체로 비슷하게 구현되어 있으므로 bind2nd만 분석해 보자.

		//template<class F, class T>
		//binder2nd<F> bind2nd(const F& func, const T& right)
		//{
		//	 typename F::second_argument_type val(right);
		//	 return (binder2nd<F>(func, val));			//const F& func 와 righte를 	binder2nd클래스로 랩핑하여 binder2nd<F>(func, val) 리턴 
		//}
not1과 마찬가지로 직접 함수 객체를 호출하는 것이 아니라 함수 객체를 래핑하는 binder2nd 클래스의 객체를 생성하여 리턴한다. 
binder2nd 클래스는 다소 복잡하게 선언되어 있다.
		binder2nd
		//template<class F> class binder2nd : public unary_function<typename F::first_argument_type, typename F::result_type>
		//{
		//public:
		//	 typedef unary_function<typename F::first_argument_type, typename F::result_type> base;
		//	 typedef typename base::argument_type argument_type;
		//	 typedef typename base::result_type result_type;
		//
		//	 binder2nd(const F& func, const typename F::second_argument_type& right)
		//		  : op(func), value(right) { }
		//	 result_type operator()(const argument_type& left) const { return (op(left, value)); }
		//	 result_type operator()(argument_type& left) const { return (op(left, value)); }
		//
		//protected:
		//	 F op;
		//	 typename F::second_argument_type value;
		//};

해석
binder2nd 클래스는 unary_function으로부터 상속받으므로 결국 단항 함수 객체이다.
내부에 이항 함수 객체 op와 고정된 두 번째 인수의 값 value를 멤버로 가지며 생성자에서 이 둘을 인수로 전달받아 초기화한다.
래핑한 이항 함수 객체를 호출할 수 있는 만반의 준비를 해 놓는 것이다.	

() 연산자 함수는 op 함수 객체를 호출하되 첫 번째 인수 left는 자신이 전달받은 인수를 그대로 넘기고 두 번째 인수는 생성자에서 미리 받아 놓은 value를 넘긴다. 
그래서 이 함수는 단항이며 호출할 때 left 인수 하나만 전달하면 된다. () 연산자는 첫 번째 인수에 대해 상수, 비상수 버전이 오버로딩되어 있다. 
bind1st도 비슷하게 분석되는데 binder1st 객체를 생성하며 binder1st는 첫 번째 인수를 미리 받아 놓았다가 호출할 때 고정된 인수를 전달할 것이다.
*/