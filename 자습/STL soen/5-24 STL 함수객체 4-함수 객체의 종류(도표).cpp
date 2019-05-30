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
함수 객체가 하는 일은 비교, 대입, 합산 등 알고리즘 구현중에 필요한 연산을 처리하는 것이라고 할 수 있다.
취하는 피연산자 개수로 연산자를 분류하듯이 함수 객체도 필요한 인수의 개수로 분류할 수 있으며 리턴값의 타입도 중요한 분류 기준이다. 
STL은 인수와 리턴값, 즉 원형에 따라 함수 객체를 다음과 같이 분류하고 고유의 이름을 부여한다.

		인수의 개수		bool이 아닌 리턴값		bool 리턴
		--------------------------------------------------
		없음				Gen

		단항				UniOp					UniPred

		이항				BinOp					BinPred
		---------------------------------------------------
UniOp는 인수 하나를 취하는 단항 함수 객체이며 
Unipred는 인수 하나를 취하고 bool을 리턴하는 단항 함수 객체이다
binOp는 인수 둘을 취하는 단항 함수 객체이며
BinPred는 인수 둘을 취해 bool형을 리턴하는 조건자 함수 객체이다.

피연산자를 하나도 취하지 않는 함수 객체를 생성기(Generator)라고 하는데 입력없이 혼자 무엇인가를 만들어 내는 역할만 한다.
 대표적으로 난수를 생성하는 함수 객체가 생성기이다. 함수 객체를 칭하는 이 표기만 보면 필요한 함수의 원형을 쉽게 유추할 수 있다.

 알고리즘 함수들은 예외없이 템플릿 함수로 구현되어 있는데 함수 객체에 해당하는 템플릿 인수의 이름에 어떤 종류의 함수 객체가 요구되는지 표기된다.
 마치 함수의 형식 인수 이름에 의미있는 이름을 붙여 유용한 정보를 표기하는 것과 같다.
 앞에서 배운 몇 개의 알고리즘 함수 원형을 살펴보면 마지막 인수인 함수 객체에 이러한 정보가 포함되어 있다.

		// InIt find_if(InIt first, InIt last, UniPred F);		//여기 F는 단항,bool리턴 함수객체가 들어가야한다.	ex)  bool pred(T &val);
		//void sort(RanIt first, RanIt last, BinPred F);		//여기는 이항, bool리턴 함수객체가 들어가야한다.
		//T accumulate(InIt first, InIt last, T val, BinOp op); //여기는 이항,bool리턴이 아닌 함수 객체기 들어가야한다.




*/



/*

*/

struct print {
	void operator()(int a, int b) const {
		 printf("%d\n", a);
	}
};//for_each는 단항 함수 객체(UniOp)를 요구하는데 에러를 유발시키기 위해 일부러 두 개의 인수를 받도록 했다.


struct print2 {
	int operator()(int a) const {
		return printf("%d\n", a);
	}
};// for_each에서 작동하는지 시험하기 위해 리턴값을 int 로 해보았다.


struct compare {
	void operator()(int a, int b) const {
		 a < b;
	}
};	//sort객체는 리턴값이 필요하다, 만약 리턴을 하지 않을경우 ?

struct compare2 {
	bool operator()(int a, int b) const {
		return a < b;
	}
};	//compare 원본

int main()
{
	int ar[5] = { 1,5,3,4,8 };

	vector<int> vi(&ar[0], &ar[4]);
	//!for_each(vi.begin(), vi.end(), print()); //Error!! 현재 print 눈 UniOp 조건을 만족하지 못한다. 세번째 인수는 단항 함수객체여야 한다!


	for_each(vi.begin(), vi.end(), print2());
	//for_each는 함수 객체를 호출하기만 할 뿐 리턴값을 요구하지는 않는다. 
	//하지만 이렇게 수정해도 별 문제는 없다. 
	//리턴값을 넘기더라도 for_each에서 이 값을 무시할 수 있고 for_each 템플릿의 본체와 충돌하는 부분이 없기 때문이다. 
	//근데 신기하게도 이색기는 sort랑 달리 리턴값도 안보고, 인자 갯수도 안보고 심지어 함수포인터를넣어도 존내 잘 들어간다.
	//이 이유는 간단하다. for_each는 함수가 아니라 함수를 만들 수 있는 템플릿일 뿐이며 호출부에서 전달되는 타입에 맞게 매번 구체화된다. 
	//어떤 타입을 정해 놓고 받는게 아니라 들어오는대로 받아들여 구체화되는 것이다. 
	//물론 전달된 타입은 템플릿 본체의 코드를 100% 지원하는 타입이어야 한다.


	//만약 템플릿 본체에서 리턴값을 명시적으로 요구할 때는 리턴값 타입도 항상 정확해야 한다. 

	cout << "=====" << endl;
	//sort( vi.begin(), vi.end(), compare());  //Error!! sort는 반드시 bool형 리턴이 필요하다.  2항 bool이므로, BinPred
	cout << "=====" << endl;
	sort(vi.begin(), vi.end(), compare2());

	for_each(vi.begin(), vi.end(), print2());
	return 0;
}

