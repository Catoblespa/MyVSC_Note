#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>		

using namespace std;
//ptr_fun은 일반 함수를 함수 객체로 만드는데 비해 mem_fun은 클래스의 멤버 함수를 함수 객체로 만든다. 
//멤버 함수는 반드시 this와 함께 호출되어야 한다는 점에서 함수 포인터와도 다른데 mem_fun은 이것을 가능하게 한다. 
//다음 예제를 보자.


class Natural
{
private:
	int num;

public:
	Natural(int anum) : num(anum) {
		SetNum(anum);
	}

	void SetNum(int anum) {
		if (anum >= 0) 
			num = anum;
	}

	int GetNum() { return num; }
	bool IsEven() { return num % 2 == 0; }
};

template <class T>
void delnatural(T* pn)
{
	delete pn;
}

int main()
{
	vector<Natural*> pVn;		//객체를 포인터로 저장하기 위한 vector

	pVn.push_back(new Natural(1));
	pVn.push_back(new Natural(2));
	pVn.push_back(new Natural(3));
	pVn.push_back(new Natural(4));

	vector<Natural*>::iterator it;

	for (it = pVn.begin();; it++) {
		it = find_if(it, pVn.end(),mem_fun(&Natural::IsEven));
		if (it == pVn.end()) break;
		cout << (*it)->GetNum() << "이(가) 있다" << endl;
	}

	for_each(pVn.begin(), pVn.end(), delnatural<Natural>);		//할당해제
	//Natural 클래스는 0 초과의 자연수를 표현하는데 짝수인지를 판별하는 IsEven 조건자가 클래스의 멤버 함수로 작성되어 있다. 
	//이 멤버 함수를 조건자 함수 객체로 만들기 위해 mem_fun 함수를 사용한다. 
	//mem_fun은 멤버 함수 포인터를 캡슐화하여 함수 객체로 만드는 객체를 생성하며 
	//이 객체의 () 연산자를 통해 컨테이너에 저장된 각 객체 포인터(this)와 함께 멤버 함수가 호출된다.

	//


	vector<Natural> vn;				//vector가 객체 그 자체를 저장할경우 

	vn.push_back(Natural(1));
	vn.push_back(Natural(2));
	vn.push_back(Natural(3));
	vn.push_back(Natural(4));

	vector<Natural>::iterator it2;
	for (it2 = vn.begin();; it2++) {
		it2 = find_if(it2, vn.end(), mem_fun_ref(&Natural::IsEven));		//mem_fun_ref
		if (it2 == vn.end()) break;
		cout << (*it2).GetNum() << "이(가) 있다" << endl;
	}
	// 객체의 포인터를 동적으로 생성한 것이 아니므로 delete는 할 필요없다.

	return 0;
}

/*
멤버 함수를 객체로 캡슐화하는 원리도 ptr_fun과 비슷하다. 
멤버 함수에 대한 래퍼는 인수를 취하지 않는 멤버 함수와 인수 하나를 취하는 멤버 함수에 대해 각각 작성되어 있으며 
이 객체를 만드는 mem_fun 함수는 두 객체에 대해 오버로딩되어 있다. 인수를 취하지 않는 버전에 대해서만 연구해 보자.

		//template<class Result, class T>
		//mem_fun_t<Result, T> mem_fun(Result (T::*Pm)())
		//{
		//	 return (mem_fun_t<Result, T>(Pm));
		//}

T 타입의 멤버 함수 Pm에 대한 멤버 함수 포인터를 받아 생성자로 이 함수 포인터를 넘겨 mem_fun_t 객체를 생성하여 그 객체를 리턴한다. mem_fun_t 클래스는 다음과 같이 선언되어 있다.

		//template<class Result,class T>
		//class mem_fun_t : public unary_function<T *, Result>
		//{
		//public:
		//	 explicit mem_fun_t(Result (T::*Pm)()) : Pmemfun(Pm) {}
		//	 Result operator()(T *pObj) const {
		//		  return ((pObj->*Pmemfun)());
		//	 }
		//private:
		//	 Result (T::*Pmemfun)();
		//};

리턴 타입과 클래스 타입을 인수로 전달받으며 내부에 인수를 취하지 않는 멤버 함수 포인터를 Pmemfun이라는 이름의 멤버 변수로 선언해 두었다. 
생성자에서는 이 멤버 함수의 포인터를 전달받아 Pmemfun 멤버에 대입해 둔다. 
그리고 () 연산자는 인수로 전달된 *pObj 객체 포인터에 대해 멤버 함수를 호출한다. 
컨테이너에 저장된 요소가 객체의 포인터이므로 find_if에 의해 각 객체의 멤버 함수들이 호출될 것이다.

만약 컨테이너가 객체의 포인터가 아니라 객체 그 자체를 저장하고 있다면 이때는 mem_fun_ref를 사용한다. 
위 예제를 다음과 같이 변형해도 동일하게 동작한다. 객체의 포인터를 동적으로 생성한 것이 아니므로 delete는 할 필요없다.

	//vector<Natural> vn;
	//vn.push_back(Natural(1));
	//vn.push_back(Natural(2));
	//vn.push_back(Natural(3));
	//vn.push_back(Natural(4));

	//vector<Natural>::iterator it;
	//for (it=vn.begin();;it++) {
	//		it=find_if(it, vn.end(), mem_fun_ref(&Natural::IsEven));
	//		if (it==vn.end()) break;
	//		cout << (*it).GetNum() << "이(가) 있다" << endl;

mem_fun_ref는 mem_fun_ref_t 객체를 생성하는데 이 객체는 멤버의 참조로부터 멤버 함수를 호출한다. 
mem_fun과 mem_fun_ref는 이 외에 인수 하나를 취하는 멤버 함수에 대한 레퍼도 생성하며 각각에 대해 상수 멤버 함수 버전도 준비되어 있다. 
그러나 인수가 둘 이상인 멤버 함수에 대해서는 별도의 래퍼를 제공하지 않는다.


*/